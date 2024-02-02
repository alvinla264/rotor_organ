#include <Servo.h>
#include "motor_control.h"
#define ESC_PIN 9
#define POT A0
#define PUSH_BUTTON_START 2
#define PUSH_BUTTON_END 8
MotorControl motor(ESC_PIN);

void setup(){
    Serial.begin(115200);
    //initalizes button pins to input
    for(int i = PUSH_BUTTON_START; i < PUSH_BUTTON_END; i++){
        pinMode(i + 1, INPUT);
    }
}
void loop(){
    for(int i = PUSH_BUTTON_START; i < PUSH_BUTTON_END; i++){
        if(digitalRead(i+1)){
            motor.PlayNote(enumToString(Note(i+1-PUSH_BUTTON_START)));
        }
        else motor.TurnOff();
    }
}


/*pot test code*/
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
