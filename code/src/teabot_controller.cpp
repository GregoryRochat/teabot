#include <teabot_controller.hpp>

namespace r2d2::teabot {
    teabot_controller_c::teabot_controller_c(
        base_comm_c &comm, motor_controller_c &motor_controller,
        hwlib::pin_out &led_green, hwlib::pin_out &led_red,
        hwlib::pin_out &led_yellow, hwlib::pin_in &button1,
        hwlib::pin_in &button2)
        : base_module_c(comm),
          motor_controller(motor_controller),
          led_green(led_green),
          led_red(led_red),
          led_yellow(led_yellow),
          button1(button1),
          button2(button2) {
        teabot_controller_c::cur_state = teabot_state::WAITING;
        teabot_controller_c::cur_tea_time = 240000000;
    }

    void teabot_controller_c::process() {
        // infinite loop to keep teabot running
        for (;;) {
            if (teabot_controller_c::tea_mode == tea::BLACK) {
                teabot_controller_c::tea_mode = tea::GREEN;
                teabot_controller_c::led_yellow.write(1);
                teabot_controller_c::cur_tea_time =
                    teabot_controller_c::t_green;
            } else {
                teabot_controller_c::tea_mode = tea::BLACK;
                teabot_controller_c::led_yellow.write(0);
                teabot_controller_c::cur_tea_time =
                    teabot_controller_c::t_black;
            }
            // take button inputs
            auto steep_tea = teabot_controller_c::button1.read();
            auto change_tea = teabot_controller_c::button2.read();
            // change tea mode is button is pressed
            // currently can choose only green or black
            if (change_tea) {
                switch (teabot_controller_c::tea_mode) {
                case tea::BLACK:
                    teabot_controller_c::led_yellow.write(1);
                    teabot_controller_c::tea_mode = tea::GREEN;
                case tea::GREEN:
                    teabot_controller_c::led_yellow.write(0);
                    teabot_controller_c::tea_mode = tea::BLACK;
                }
            }
            switch (cur_state) {
            case teabot_state::WAITING:
                if (steep_tea) {
                    teabot_controller_c::cur_state = teabot_state::MOVING;
                    teabot_controller_c::prev_state = teabot_state::WAITING;
                    teabot_controller_c::update_leds();
                }
            case teabot_state::MOVING:
                if (teabot_controller_c::prev_state == teabot_state::WAITING) {
                    teabot_controller_c::motor_controller.move_arm(1);
                    teabot_controller_c::time = hwlib::now_us();
                    teabot_controller_c::cur_state = teabot_state::STEEPING;
                    teabot_controller_c::prev_state = teabot_state::MOVING;
                } else {
                    teabot_controller_c::motor_controller.move_arm(0);
                    teabot_controller_c::cur_state = teabot_state::WAITING;
                    teabot_controller_c::prev_state = teabot_state::MOVING;
                }
            case teabot_state::STEEPING:
                uint_fast64_t curtime = hwlib::now_us();
                if (curtime - teabot_controller_c::time > cur_tea_time) {
                    teabot_controller_c::cur_state = teabot_state::MOVING;
                    teabot_controller_c::prev_state = teabot_state::STEEPING;
                    teabot_controller_c::update_leds();
                }
            }
        }
    }

    void teabot_controller_c::update_leds() {
        if (teabot_controller_c::prev_state == teabot_state::WAITING) {
            teabot_controller_c::led_red.write(1);
            teabot_controller_c::led_green.write(0);
        } else {
            teabot_controller_c::led_red.write(0);
            teabot_controller_c::led_green.write(1);
        }
    }

} // namespace r2d2::teabot