#pragma once
#include <hwlib.hpp>

namespace r2d2::teabot {

    class motor_controller_c {
        /**
         * Motor controller class specifically designed for use with the DRV8825
         * motor driver and the NEMA17 stepper motor, with the motor driver set
         * to full step mode thus needing roughly 210 steps for a full
         * revolution. If a different mode is selected the steps parameter
         * should be adjusted.
         */

    private:
        hwlib::pin_out &direction;
        hwlib::pin_out &steps;

        constexpr static uint16_t move_steps = 30;

    public:
        /**
         * Constructor for motor controller
         * takes comm and two pin out arguments
         * to control the motor (driver)
         */
        motor_controller_c(hwlib::pin_out &direction, hwlib::pin_out &steps);

        /**
         * @brief
         * function that takes a string for direction, setting the direction pin
         * high high to move the arm down, or the pin low to move it up,
         * revolving the amount of steps as set in move_steps
         * @param
         * direction : hwlib::string containing directional input
         */
        void move_arm(int direction);
    };
} // namespace r2d2::teabot