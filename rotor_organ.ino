#include <Servo.h>
Servo ESC;
void setup(){
    ESC.attach(9);
    Serial.begin(9600);
}

void loop(){
    int potValue = analogRead(A0);
    potValue =  map(potValue, 0, 1023, 1000, 2000);
    ESC.writeMicroseconds(potValue);
}