#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_
#include <Arduino.h>
#include <Servo.h>

//max freq is G# 2 octaves up 1661.2(6 octave)
#define num_of_plates 8
#define MAX_RPM 50000
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
        MotorControl();
        MotorControl(int pin);
        float PlayNote(String note, int octave = 4);
        void TurnOff();
};
//fourth octave
Note strToEnum(String note);
float getFrequency(String note);
String enumToString(Note n);
#endif //MOTOR_CONTROL_H_