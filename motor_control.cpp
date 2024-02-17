#include "motor_control.h"
float fundamental_freq[] = {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3, 440, 466,16, 493.88}; //C C# D D# E F F# G G# A A# B

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

String enumToString(Note n){
  switch(n){
    case C:
      return "C";
    case C_S:
      return "C#";
    case D:
      return "D";
    case D_S:
      return "D#";
    case E:
      return "E";
    case F:
      return "F";
    case F_S:
      return "F#";
    case G:
      return "G";
    case G_S:
      return "G#";
    case A:
      return "A";
    case A_S:
      return "A#";
    case B:
      return "B";
    default:
      return "C";
  }
}

MotorControl::MotorControl(Servo esc){
    ESC = esc;
    frequency = 0;
    rpm = 0;
}

MotorControl::MotorControl(){
  frequency = 0;
  rpm = 0;
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
    int output = map(rpm, 0, MAX_RPM, 1100, 2000);
    frequency = freq;
    rpm = output;
    ESC.writeMicroseconds(rpm);
}

void MotorControl::TurnOff(){
    ESC.writeMicroseconds(1000);
}

int MotorControl::GetFrequency(){ return frequency;}

int MotorControl::GetRPM(){ return rpm; }

void MotorControl::PotControl(int value){
  ESC.writeMicroseconds(value);
}