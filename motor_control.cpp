#include "motor_control.h"

Note strToEnum(String note){
  if(note == "C") return C;
  else if(note == "C#") return C_S;
  else if(note == "D") return D;
  else if(note == "D#") return D_S;
  else if(note == "E") return E;
  else if(note == "F") return F;
  else if(note == "F#") return F_S;
  else if(note == "G") return G;
  else if(note == "G#") return G_S;
  else if(note == "A") return A;
  else if(note == "A#") return A_S;
  else if(note == "B") return B;
  else return C;
}
MotorControl::MotorControl(int pin) : ESC_pin(pin){
    ESC.attach(pin);
    ESC.writeMicroseconds(1000);
}

void MotorControl::PlayNote(String note, int octave){
    bool down_octave = false;
    float freq = fundamental_freq[strToEnum(note)];
    octave = octave - 4;//center it at 0
    if(octave < 0){
        octave = -1 * octave;
        down_octave = true;
    }
    //changes the frequency to the proper octave
    freq = (octave) ? ((down_octave) ? freq / ((float)num_of_plates * (float)octave) : freq * (num_of_plates * octave)) : freq;
    rpm = freq * 60; //converts freq(RPS) to RPM assuming freq and RPS are 1 to 1
    int output = map(rpm, 0, MAX_RPM, 1000, 2000);
    frequency = freq;
    rpm = output;
    ESC.writeMicroseconds(rpm);
}

void MotorControl::TurnOff(){
    ESC.writeMicroseconds(0);
}