#include "slider_pot.h"

SliderPot::SliderPot(int pot_pin, int num_of_pos){
    pin = pot_pin;
    pinMode(pin, INPUT);
    num_of_positions = num_of_pos;
    interval = 1023/num_of_pos;
}

int SliderPot::GetPosition(){
    int value = analogRead(pin);
    for(int i = 0; i < num_of_positions; i++){
        if(value >= (interval * i) - THRESHOLD && value <= (interval * i) +THRESHOLD){
            position = i;
            return i;
        }
    }
}