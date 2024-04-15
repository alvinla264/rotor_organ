#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_
#include <Arduino.h>
#include <Servo.h>

//max freq is G# 2 octaves up 1661.2(6 octave)
#define num_of_plates 8
#define MAX_RPM 9480
#define MIN_RPM 500
enum Note{
  C = 0,
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
        unsigned int rpm;
        float frequency;
        int motor_output;
    public:
        MotorControl();
        MotorControl(Servo esc);
        void InitializeMotor();
        void PlayNote(String note, int octave = 4, int offset = 0);
        void TurnOff();
        unsigned int GetRPM(){return rpm;}
        float GetFrequency(){return frequency;}
        int GetMotorOutput(){return motor_output;}
        void writeMicroseconds(int value);
};
//fourth octave
Note strToEnum(String note);
float getFrequency(String note);
String enumToString(Note n);
#endif //MOTOR_CONTROL_H_