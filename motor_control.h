#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_
#include <Arduino.h>
#include <Servo.h>
#include "music.h"

//max freq is G# 2 octaves up 1661.2(6 octave)
#define num_of_plates 8
#define MAX_RPM 9480
#define MIN_RPM 500

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

#endif //MOTOR_CONTROL_H_