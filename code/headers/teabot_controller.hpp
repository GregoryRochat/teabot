#pragma once
#include <base_module.hpp>
#include <hwlib.hpp>
#include <motor_controller.hpp>

namespace r2d2::teabot {
    enum class teabot_state { WAITING, STEEPING, MOVING };

    enum class tea { BLACK, GREEN };

    class teabot_controller_c : public base_module_c {

    private:
        teabot_state cur_state;
        teabot_state prev_state;

        tea tea_mode = tea::BLACK;

        /**
         * Time for each tea to steep
         * time is in micro seconds. 1 second = 1.000.000 microseonds
         * 1 minute = 60 seconds, so to set tea for 4 minutes:
         * 4 * 60 * 1.000.000 = 240.000.000
         */
        constexpr static uint_fast64_t t_black = 240000000;
        constexpr static uint_fast64_t t_green = 120000000;
        constexpr static uint_fast64_t t_white = 120000000;
        constexpr static uint_fast64_t t_herbal = 300000000;
        uint_fast64_t cur_tea_time;
        uint8_t time;

        motor_controller_c &motor_controller;

        hwlib::pin_out &led_green;
        hwlib::pin_out &led_red;
        hwlib::pin_out &led_yellow;

        // button1 is to start steeping
        // button2 is for changing tea mode
        hwlib::pin_in &button1;
        hwlib::pin_in &button2;

    public:
        /**
         * @brief
         * Constructor for teabot_controller_c
         */
        teabot_controller_c(base_comm_c &comm,
                            motor_controller_c &motor_controller,
                            hwlib::pin_out &led_green, hwlib::pin_out &led_red,
                            hwlib::pin_out &led_yellow, hwlib::pin_in &button1,
                            hwlib::pin_in &button2);

        /**
         * @brief
         * main function of teabot_controller, runs a statemachine
         */
        void process() override;

        /**
         * @brief
         * Function that switches the current state leds
         * turning green on for waiting and red for steeping
         */
        int update_leds();

        /**
         * @brief
         * function that moves arm up or down depending on previous state
         */
        int move_arm();

        /**
         * @brief
         * function that use hwlib time now_us() function to evaluate
         * if required time for steeping the tea has passed
         */
        int steeping();
    };
} // namespace r2d2::teabot