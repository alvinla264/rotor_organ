#include "motor_control.h"
float fundamental_freq[] = {16.35, 17.32, 18.35, 19.45, 20.6, 21.83, 23.12, 24.5, 25.96, 27.5, 29.14,30.87}; //C C# D D# E F F# G G# A A# B

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
    motor_output = 0;
}

MotorControl::MotorControl(){
  frequency = 0;
  rpm = 0;
  motor_output = 0;
}

void MotorControl::PlayNote(String note, int octave){
    float freq = fundamental_freq[strToEnum(note)] * pow(2, octave);
    rpm = (freq / num_of_plates) * 60 ; //converts freq(RPS) to RPM assuming freq and RPS are 1 to 1
    int output = map(rpm, 0, MAX_RPM, 0, 2000);
    frequency = freq;
    motor_output = output;
    ESC.writeMicroseconds(output);
}

void MotorControl::TurnOff(){
    ESC.writeMicroseconds(1000);
}

void MotorControl::PotControl(int value){
  ESC.writeMicroseconds(value);
}


void MotorControl::InitializeMotor(){
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
  ESC.writeMicroseconds(1000);
  delay(250);
}