#include <Servo.h>
#include "motor_control.h"
#include "music.h"
#include "rotaryencoder.h"
#include "Arduino.h"
#define ESC_PIN 9
#define POT_TEST A0
#define POT_OCTAVE_SLIDER A0
#define POT_NOTE A1
#define POT_TUNER A2
#define POT_OCTAVE A3
#define POT_BUTTON_THRESHOLD 300
#define PUSH_BUTTON_START 34
#define PUSH_BUTTON_END 52
#define BTTN_CHANGE_FACTOR 2
#define OCTAVEOFFSET 2
#define OFFSET_RANGE 20
#define SLIDER_MAX_VALUE 23610
#define DEBUG false
//slidepot 1(850-1023), 2(650-800), 3(350-500), 4(0-150)


volatile long counter = 0;
volatile bool last_outA_value;
volatile bool last_outB_value;
MotorControl motor;
int key = 0;
int prev_key = 0;
Note note = C;
Note prev_note = C;
int offset = 0;
int octave = 0;
int prev_octave = 0;
RotaryEncoder slider;

void updateEncoder(){
    slider.ReadState();
}

void setup(){
    Serial.begin(115200);
    pinMode(POT_OCTAVE_SLIDER, INPUT);
    pinMode(POT_NOTE, INPUT);
    pinMode(POT_TUNER, INPUT);
    pinMode(POT_OCTAVE, INPUT);
    Servo ESC;
    ESC.attach(ESC_PIN, 1000, 2000);
    //Serial.println("writing 2000");
    //ESC.writeMicroseconds(2000);
    //delay(5000);
    motor = MotorControl(ESC);
    Serial.println("Initalizing Motor");
    motor.InitializeMotor();
    Serial.println("Done");
    attachInterrupt(digitalPinToInterrupt(outA), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(outB), updateEncoder, CHANGE);
    delay(5000);
}
void loop(){
    MayOrgan();
}

void MayOrgan(){
    while(analogRead(POT_NOTE) > POT_BUTTON_THRESHOLD){
        long pos = slider.GetPositon();
        note = Note(pos/(SLIDER_MAX_VALUE / 12)); //segments the slider into 12 regions representing the 12 notes

        int octave_value = analogRead(POT_OCTAVE_SLIDER); //reads the octave slider pot and gets position
        if(octave_value > 850){
            octave = 0;
        }
        else if(octave_value > 650){
            octave = 1;
        }
        else if(octave_value > 350){
            octave = 2;
        }
        else{
            octave = 3;
        }
        if(analogRead(POT_OCTAVE) > POT_BUTTON_THRESHOLD) octave += 4;
        while(analogRead(POT_TUNER) > POT_BUTTON_THRESHOLD){ //tuning mode
            pos = slider.GetPositon();
            pos -= SLIDER_MAX_VALUE / 2; //changes range from 0 to MAX to -MAX/2 to MAX/2
            offset = map(pos, -(SLIDER_MAX_VALUE / 2), (SLIDER_MAX_VALUE / 2), -OFFSET_RANGE, OFFSET_RANGE); //maps position range to -OFFSET_RANGE TO OFFSET_RANGE
            motor.PlayNote(enumToString(note), octave + OCTAVEOFFSET, offset);
            delay(250);
        }
        if(note != prev_note || prev_octave != octave){
            prev_note = note;
            prev_octave = octave;
            motor.PlayNote(enumToString(note), octave + OCTAVEOFFSET, offset);
            if(DEBUG){
                float freq = motor.GetFrequency();
                unsigned int rpm = motor.GetRPM();
                int motor_output = motor.GetMotorOutput();
                Serial.print("Position: ");
                Serial.print(pos);
                Serial.print(" Playing ");
                Serial.print(enumToString(note));
                Serial.print(" ");
                Serial.println(octave + OCTAVEOFFSET);
                Serial.print("motor output: ");
                Serial.print(motor_output);
                Serial.print(" rpm: ");
                Serial.print(rpm);
                Serial.print(" frequency: ");
                Serial.println(freq);
                Serial.println();
            }
        }
    }
}

void SliderTest(){
    long pos = slider.GetPositon();
    note = Note(pos/(SLIDER_MAX_VALUE / 12));
    int value = analogRead(POT_OCTAVE_SLIDER);
    if(value > 850){
        octave = 0;
    }
    else if(value > 650){
        octave = 1;
    }
    else if(value > 350){
        octave = 2;
    }
    else{
        octave = 3;
    }
    if(note != prev_note || prev_octave != octave){
        prev_note = note;
        prev_octave = octave;
        if(octave == 0){
            motor.TurnOff();
            Serial.println("Motor Off");
        }
        else{
            Serial.print("Position: ");
            Serial.print(pos);
            Serial.print(" Playing ");
            Serial.print(enumToString(note));
            Serial.print(" ");
            Serial.println(octave + OCTAVEOFFSET);
            motor.PlayNote(enumToString(note), octave + OCTAVEOFFSET);
            float freq = motor.GetFrequency();
            unsigned int rpm = motor.GetRPM();
            int motor_output = motor.GetMotorOutput();
            Serial.print("motor output: ");
            Serial.print(motor_output);
            Serial.print(" rpm: ");
            Serial.print(rpm);
            Serial.print(" frequency: ");
            Serial.println(freq);
            Serial.println();
        }
        
    }
}
void DemoSoundTest(){
    for(int i = PUSH_BUTTON_START; i <= PUSH_BUTTON_END; i+=BTTN_CHANGE_FACTOR){
        if(digitalRead(i)){
            key = (i - PUSH_BUTTON_START) / 2;
        }
    }
    int value = analogRead(POT_OCTAVE_SLIDER);
    if(value > 850){
        octave = 0;
    }
    else if(value > 650){
        octave = 1;
    }
    else if(value > 350){
        octave = 2;
    }
    else{
        octave = 3;
    }
    
    if(key && (key != prev_key || prev_octave != octave)){
        prev_key = key;
        prev_octave = octave;
        String note = enumToString((Note) key);
        Serial.print("Playing ");
        Serial.print(note);
        Serial.print(" ");
        Serial.println(octave + OCTAVEOFFSET);
        motor.PlayNote(note, octave + OCTAVEOFFSET);
        float freq = motor.GetFrequency();
        unsigned int rpm = motor.GetRPM();
        int motor_output = motor.GetMotorOutput();
        Serial.print("motor output: ");
        Serial.print(motor_output);
        Serial.print(" rpm: ");
        Serial.print(rpm);
        Serial.print(" frequency: ");
        Serial.println(freq);
        Serial.println();
    }
    else if(!key && prev_key){
        prev_key = key;
        motor.TurnOff();
        Serial.println("Turning off");
    }
    delay(250);
}

void Pot_Test(){
    int potValue = analogRead(POT_TEST);
    potValue =  map(potValue, 0, 1023, 1000, 2000);
    Serial.println(potValue);
    //ESC.writeMicroseconds(potValue);
    motor.writeMicroseconds(potValue);
    delay(150);
}

void Motor_Serial_Test(){
    if(Serial.available()){
        String input = Serial.readString();
        if(input == "off"){
            motor.TurnOff();
            Serial.println("turning motor off");
        }
        else{
            int space_index = input.indexOf(' ');
            String note = input.substring(0, space_index);
            int octave = input.substring(space_index+1).toInt();
            if(note == "motor"){
                motor.writeMicroseconds(octave);
                Serial.print("motor output: ");
                Serial.println(octave);
            }
            else{
                Serial.print("Playing ");
                Serial.print(note);
                Serial.print(" ");
                Serial.println(octave);
                motor.PlayNote(note, octave);
                float freq = motor.GetFrequency();
                unsigned int rpm = motor.GetRPM();
                int motor_output = motor.GetMotorOutput();
                Serial.print("motor output: ");
                Serial.print(motor_output);
                Serial.print(" rpm: ");
                Serial.print(rpm);
                Serial.print(" frequency: ");
                Serial.println(freq);
                Serial.println();
            }
            
        }
    }
    delay(250);
}

/*pot test code*/
//Servo ESC;
// void setup(){
//     ESC.attach(ESC_PIN, 1000, 2000);
//     Serial.begin(115200);
//     ESC.writeMicroseconds(1000);
//     delay(10000);
// }


