#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_
#include <Servo.h>
float fundamental_freq[] = {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3, 440, 466,16, 493.88}; //C C# D D# E F F# G G# A A# B
//max freq is G# 2 octaves up 1661.2
class MotorControl{
    private:
        int ESC_pin;
        Servo ESC;
    public:
        MotorControl(int pin);
        void PlayNote(char note);
        void TurnOff();
};

float getFrequency(char note) {
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

#endif //MOTOR_CONTROL_H_