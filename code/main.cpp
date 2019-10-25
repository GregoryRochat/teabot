#include <hwlib.hpp>

#include <comm.hpp>
#include <motor_controller.hpp>
#include <teabot_controller.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);
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
    teabot_controller.process();
}