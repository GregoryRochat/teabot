# teabot

## Introduction

This is a 0.1 version of a teabot. It works by having a small stick with a hook attached to the stepper motor which is hanged sideways suspended above ground. Attaching a teabag to the hook, placing a cup with hot water, selecting a mode and starting the bot will then lower the tea bag into the cup and after the time related to the chosen tea mode has elapsed the bot will take out the teabag and return to a waiting state.

## Equipment

For this project an Arduino Due was used, with a DRV8825 motor driver and a NEMA 17 stepper motor. Below is the setup.

## Tests
Hardware tests were run to determine the steps per revolutions and steps per angle relative to that, where 210 steps and 30 came out in this setup, though different motors and voltages may require retesting. Important to note: M0, M1 and M2 were left empty to keep the driver in full step mode, changing this allows for more precise finetuning but also requires a recalculation of original values.

## Change tea times
To change the preset tea times to a new preferred option, simply change the teabot_controller header file, specifically the t_black, t_green, etc private values. Time is calculated in microseconds, so x minutes would become x * 60 * 1.000.000


## Schematic for teabot

![teabot_schematicv2](https://user-images.githubusercontent.com/47680833/67609255-1a493c00-f78c-11e9-97a2-de672e660374.png)
