#include "motor_control.h"
float fundamental_freq[] = {16.35, 17.32, 18.35, 19.45, 20.6, 21.83, 23.12, 24.5, 25.96, 27.5, 29.14,30.87}; //C C# D D# E F F# G G# A A# B

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

void MotorControl::PlayNote(String note, int octave, int offset){
    float freq = fundamental_freq[strToEnum(note)] * pow(2, octave);
    // rpm = (freq / num_of_plates) * 60 ; //converts freq(RPS) to RPM assuming freq and RPS are 1 to 1
    // int output = map(rpm, 0, MAX_RPM, 1100, 2000);
    frequency = freq;
    int output = 1077 + 0.44 * freq + -1.19E-04 * pow(freq, 2);
    output = (output + offset > 2000) ? 2000 : (output + offset < 1100) ? 1100 : output + offset;
    motor_output = output;
    ESC.writeMicroseconds(output);
}

void MotorControl::TurnOff(){
    ESC.writeMicroseconds(1000);
}

void MotorControl::writeMicroseconds(int value){
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