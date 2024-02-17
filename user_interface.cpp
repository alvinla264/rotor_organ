#include "user_interface.h"

UserInterface::UserInterface(int slider_pin_start, int motor_pin_start){
    for(int i = 0; i < NUM_OF_SLIDERS;i++){
        sliders[i] = SliderPot(slider_pin_start + i, NUM_OF_POS);
        slider_positions[i] = sliders[i].GetPosition();
    }
    for(int i = 0; i < NUM_OF_SLIDERS; i++){
        //motors[i] = MotorControl(motor_pin_start + i);
        //motors[i].TurnOff();
    }
}