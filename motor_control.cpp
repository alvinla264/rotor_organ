#include "motor_control.h"

MotorControl::MotorControl(int pin) : ESC_pin(pin){
    ESC.attach(pin);
    ESC.writeMicroseconds(1000);
}

void MotorControl::PlayNote(char note){
    float freq = getFrequency(note);
    float rpm = freq * 60;
    rpm = map(rpm, 0, 50000, 1000, 2000);
    ESC.writeMicroseconds(rpm);
}

void MotorControl::TurnOff(){
    ESC.writeMicroseconds(0);
}