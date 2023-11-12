#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_
#include <Arduino.h>
#include <Servo.h>
//float fundamental_freq[] = {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3, 440, 466,16, 493.88}; //C C# D D# E F F# G G# A A# B
//max freq is G# 2 octaves up 1661.2(6 octave)
class MotorControl{
    private:
        int ESC_pin;
        Servo ESC;
    public:
        MotorControl(int pin);
        void PlayNote(char note, int octave = 4);
        void TurnOff();
};
//fourth octave
float getFreq(char note);
#endif //MOTOR_CONTROL_H_