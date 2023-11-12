#include "motor_control.h"

MotorControl::MotorControl(int pin) : ESC_pin(pin){
    ESC.attach(pin);
    ESC.writeMicroseconds(1000);
}

void MotorControl::PlayNote(char note, int octave){
    bool down_octave = false;
    float freq = getFrequency(note);
    octave = octave - 4;//center it at 0
    if(octave < 0){
        octave = -1 * octave;
        down_octave = true;
    }
    freq = (octave) ? ((down_octave) ? freq / (2.0 * (float)octave) : freq * (2 * octave)) : freq;
    float rpm = freq * 60;
    rpm = map(rpm, 0, 50000, 1000, 2000);
    ESC.writeMicroseconds(rpm);
}

void MotorControl::TurnOff(){
    ESC.writeMicroseconds(0);
}