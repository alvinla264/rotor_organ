#include <Servo.h>
#include "motor_control.h"
#include "music.h"
#include "rotaryencoder.h"
#include "AD5245.h"
#include "Arduino.h"
#define ESC_PIN 9
#define POT_TEST A0
#define POT_OCTAVE_SLIDER A0
#define POT_NOTE A0
#define POT_OCTAVE1 A1
#define POT_OCTAVE2 A2
#define POT_BUTTON_THRESHOLD 350
#define MOTOR_SWITCH 30
#define PUSH_BUTTON_START 34
#define PUSH_BUTTON_END 52
#define BTTN_CHANGE_FACTOR 2
#define OCTAVEOFFSET 2
#define OFFSET_RANGE 20
#define DEBUG true
//slidepot 1(850-1023), 2(650-800), 3(350-500), 4(0-150)


volatile long counter = 0;
volatile bool last_outA_value;
volatile bool last_outB_value;
MotorControl motor;
int digi_pot_value = 0;
AD5245 AD(0x2C);
int key = 0;
int prev_key = 0;
bool first_pressed = true;
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
    Wire.begin();
    Wire.setClock(400000);
    AD.begin();
    pinMode(POT_OCTAVE_SLIDER, INPUT);
    pinMode(POT_NOTE, INPUT);
    pinMode(POT_OCTAVE1, INPUT);
    pinMode(POT_OCTAVE2, INPUT);
    pinMode(MOTOR_SWITCH, INPUT_PULLUP);
    Servo ESC;
    ESC.attach(ESC_PIN, 1000, 2000);
    // Serial.println("writing 2000");
    // ESC.writeMicroseconds(2000);
    // delay(5000);
    motor = MotorControl(ESC);
    Serial.println("Initalizing Motor");
    motor.InitializeMotor();
    attachInterrupt(digitalPinToInterrupt(outA), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(outB), updateEncoder, CHANGE);
    delay(5000);
    Serial.println("Done");
    while(!digitalRead(MOTOR_SWITCH)) continue;
}
void loop(){
    MayOrgan();
    //SliderTest();
    //Motor_Serial_Test();
    // Serial.print("Switch: ");
    // Serial.print(digitalRead(MOTOR_SWITCH));
    // Serial.print("  ");
    // for(int i = 0; i < 3; i++){
    //     int value = analogRead(POT_NOTE + i);
    //     Serial.print(i);
    //     Serial.print(" :");
    //     Serial.print(value);
    //     Serial.print("   ");
    // }
    // Serial.println();
    // delay(250);
}

void MayOrgan(){
    if(digitalRead(MOTOR_SWITCH)){
        int pot_note_value = analogRead(POT_NOTE);
        digi_pot_value = map(pot_note_value, 295, 560, 0, 255);
        AD.write(digi_pot_value);
        long pos = slider.GetPositon();
        if(pos > SLIDER_MAX_VALUE) {
            pos = SLIDER_MAX_VALUE;
            slider.SetPositionMax();
        }
        else if(pos < 0){
            pos = 0;
            slider.SetPositionMin();
        }
        note = Note(pos/(SLIDER_MAX_VALUE / 12)); //segments the slider into 12 regions representing the 12 notes
        int octave_value = analogRead(POT_OCTAVE1); //reads the octave slider pot and gets position
        int octave_value2 = analogRead(POT_OCTAVE2);
        if(octave_value > POT_BUTTON_THRESHOLD){
            octave = 1;
        }
        else if(octave_value2 > POT_BUTTON_THRESHOLD){
            octave = 2;
        }
        else{
            octave = 0;
        }
        if(note != prev_note || prev_octave != octave || first_pressed){
            first_pressed = false;
            prev_note = note;
            prev_octave = octave;
            motor.PlayNote(enumToString(note), octave + OCTAVEOFFSET, offset);
            if(DEBUG){
                float freq = motor.GetFrequency();
                unsigned int rpm = motor.GetRPM();
                int motor_output = motor.GetMotorOutput();
                Serial.print("Position: ");
                Serial.print(pos);
                Serial.print(" Pot value: ");
                Serial.print(pot_note_value);
                Serial.print(" digipot output: ");
                Serial.print(digi_pot_value);
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
    else{
        Serial.println("Off");
        motor.TurnOff();
        while(!digitalRead(MOTOR_SWITCH)){
            continue;
        }
    }
    delay(1);
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
    AD.write(255);
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


