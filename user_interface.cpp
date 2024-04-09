#include "user_interface.h"

UserInterface::UserInterface(int slider_pin_start, int bttn_start): button_start(bttn_start){
    for(int i = 0; i < NUM_OF_SLIDERS;i++){
        sliders[i] = SliderPot(slider_pin_start + i, NUM_OF_POS);
        slider_positions[i] = sliders[i].GetPosition();
    }
    for(int i = 0; i < NUM_OF_BUTTONS; i++){
        pinMode(button_start + i, INPUT);
        button_status[i] = digitalRead(button_start + i);
    }
}

void UserInterface::ReadSliderPosition(){
    for(int i = 0; i < NUM_OF_SLIDERS; i++){
        slider_positions[i] = sliders[i].GetPosition();
    }
}

void UserInterface::ReadButtonPosition(){
    for(int i = 0; i < NUM_OF_BUTTONS; i++){
        button_status[i] = digitalRead(button_start + i);
    }
    
}