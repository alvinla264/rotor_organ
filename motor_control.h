#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_
#include <Arduino.h>
#include <Servo.h>

//max freq is G# 2 octaves up 1661.2(6 octave)
#define num_of_plates 8
#define MAX_RPM 50000
float fundamental_freq[] = {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3, 440, 466,16, 493.88}; //C C# D D# E F F# G G# A A# B
enum Note{
  C,
  C_S,
  D,
  D_S,
  E,
  F,
  F_S,
  G,
  G_S,
  A,
  A_S,
  B
};
class MotorControl{
    private:
        int ESC_pin;
        Servo ESC;
        int rpm;
        int frequency;
    public:
        MotorControl(int pin);
        void PlayNote(String note, int octave = 4);
        void TurnOff();
};
//fourth octave
Note strToEnum(String note);
float getFrequency(String note);

#endif //MOTOR_CONTROL_H_