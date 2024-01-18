#include "motor_control.h"
float getFreq(char note) {
  switch (note) {
    case 'A':
      return 440.00;
    case 'B':
      return 493.88;
    case 'C':
      return 261.63;
    case 'D':
      return 293.66;
    case 'E':
      return 329.63;
    case 'F':
      return 349.23;
    case 'G':
      return 392.00;
    default:
      return 0;  // Return 0 for unknown notes
    }
}

MotorControl::MotorControl(int pin) : ESC_pin(pin){
    ESC.attach(pin);
    ESC.writeMicroseconds(1000);
}

void MotorControl::PlayNote(char note, int octave){
    bool down_octave = false;
    float freq = getFreq(note);
    octave = octave - 4;//center it at 0
    if(octave < 0){
        octave = -1 * octave;
        down_octave = true;
    }
    freq = (octave) ? ((down_octave) ? freq / ((float)num_of_plates * (float)octave) : freq * (num_of_plates * octave)) : freq;
    rpm = freq * 60;
    int output = map(rpm, 0, 50000, 1000, 2000);
    frequency = freq;
    rpm = output;
    ESC.writeMicroseconds(rpm);
}

void MotorControl::TurnOff(){
    ESC.writeMicroseconds(0);
}