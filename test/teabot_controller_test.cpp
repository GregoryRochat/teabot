#include <ostream>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("testing pins") {
    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d2);
    auto button2 = hwlib::target::pin_in(hwlib::target::pins::d3);
    auto led_green = hwlib::target::pin_out(hwlib::target::pins::d5);
    auto led_red = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto led_yellow = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto direction = hwlib::target::pin_out(hwlib::target::pins::d8);
    auto steps = hwlib::target::pin_out(hwlib::target::pins::d9);

    r2d2::comm_c comm;
    auto motor_controller = r2d2::teabot::motor_controller_c(direction, steps);
    auto teabot_controller = r2d2::teabot::teabot_controller_c(
        comm, motor_controller, led_green, led_red, led_yellow, button1,
        button2);
    CHECK(teabot_controller.update() == 1);
    CHECK(motor_controller.move_arm(0)) == 1);
    CHECK(motor_controller.move_arm(1)) == 1);
    CHECK(motor_controller.move_arm(2)) == 0);
}