#include "Servo.h"
#include "motor_control.h"
#include "lcd_screen.h"
#define ESC_PIN 5
#define POT A1
Servo ESC;
LCDScreen lcd;
void setup(){
    ESC.attach(ESC_PIN);
    Serial.begin(9600);
}

void loop(){
    int potValue = analogRead(POT);
    potValue =  map(potValue, 0, 1023, 1000, 2000);
    ESC.writeMicroseconds(potValue);
    int freq = map(potValue, 1000, 2000, 0, 50000);
    char second_line[17];
    sprintf(second_line, "%d", freq);
    lcd.PrintBothLine("Frequency", second_line);
    
}
