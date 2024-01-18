#include <Servo.h>
#include "motor_control.h"
#include "lcd_screen.h"
#define ESC_PIN 9
#define POT A0

MotorControl motor(ESC_PIN);

void setup(){
    Serial.begin(115200);
}



//Servo ESC;
// void setup(){
//     ESC.attach(ESC_PIN, 1000, 2000);
//     Serial.begin(9600);
// }

// void loop(){
//     int potValue = analogRead(POT);
//     potValue =  map(potValue, 0, 1023, 1000, 2000);
//     Serial.println(potValue);
//     ESC.writeMicroseconds(potValue);
//     delay(150);
// }
