#include <motor_controller.hpp>

namespace r2d2::teabot {
    motor_controller_c::motor_controller_c(hwlib::pin_out &direction,
                                           hwlib::pin_out &steps)
        : direction(direction), steps(steps) {
    }

    void motor_controller_c::move_arm(int direction) {
        if (direction == 0) {
            // set direction clockwise
            motor_controller_c::direction.write(1);
            for (int i = 0; i < motor_controller_c::move_steps; i++) {
                // move one step
                motor_controller_c::steps.write(1);
                hwlib::wait_ms(250);
                motor_controller_c::steps.write(0);
                hwlib::wait_ms(250);
            }
        } else if (direction == 1) {
            // set direction counter clockwise
            motor_controller_c::direction.write(0);
            for (int i = 0; i < motor_controller_c::move_steps; i++) {
                // move one step
                motor_controller_c::steps.write(1);
                hwlib::wait_ms(250);
                motor_controller_c::steps.write(0);
                hwlib::wait_ms(250);
            }
        }
    }
} // namespace r2d2::teabot