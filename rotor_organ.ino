#include <Servo.h>
#include "motor_control.h"
#include "user_interface.h"
#include "slider_pot.h"
#define ESC_PIN 9
#define POT A0
#define PUSH_BUTTON_START 34
#define PUSH_BUTTON_END 52
#define BTTN_CHANGE_FACTOR 2
#define OCTAVEOFFSET 2

//slidepot 1(850-1023), 2(650-800), 3(350-500), 4(0-150)
MotorControl motor;
//UserInterface interface(A0, 50);
Note root_note = (Note)1;
int key = 0;
int prev_key = 0;
int octave = 0;
int prev_octave = 0;
void setup(){
    Serial.begin(115200);
    //initalizes button pins to input
    for(int i = PUSH_BUTTON_START; i <= PUSH_BUTTON_END; i+=BTTN_CHANGE_FACTOR){
        pinMode(i, INPUT);
    }
    pinMode(POT, INPUT);
    Servo ESC;
    ESC.attach(ESC_PIN, 1000, 2000);
    //Serial.println("writing 2000");
    //ESC.writeMicroseconds(2000);
    //delay(5000);
    motor = MotorControl(ESC);
    Serial.println("Initalizing Motor");
    motor.InitializeMotor();
    Serial.println("Done");
    //delay(5000);
}

void loop(){
    DemoSoundTest();
}

// void UserInterfaceTest(){
//     interface.ReadButtonPosition();
//     interface.ReadSliderPosition();
//     int octave = interface.slider_positions[0];
//     Note notes[NUM_OF_SLIDERS];
//     for(int i = 0; i < NUM_OF_SLIDERS; i++){
//         if(i == 0){
//             notes[i] = root_note;
//         }
//         else{
//             notes[i] = (Note)((int)root_note + interface.slider_positions[i]);
//         }
//     }
//     for(int i = 0; i < NUM_OF_BUTTONS; i++){
//         if(interface.button_status[i]){
//             Serial.print("Motor ");
//             Serial.print(i);
//             Serial.print(": ");
//             Serial.println(enumToString(notes[i]));
//         }
//     }
//     Serial.println();
// }

void DemoSoundTest(){
    for(int i = PUSH_BUTTON_START; i <= PUSH_BUTTON_END; i+=BTTN_CHANGE_FACTOR){
        if(digitalRead(i)){
            key = (i - PUSH_BUTTON_START) / 2;
        }
    }
    int value = analogRead(POT);
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
    int potValue = analogRead(POT);
    potValue =  map(potValue, 0, 1023, 1000, 2000);
    Serial.println(potValue);
    //ESC.writeMicroseconds(potValue);
    motor.PotControl(potValue);
    delay(150);
}
// void loop(){
//     //Motor_Serial_Test();
// }
// void Motor_Button_Test(){
//     for(int i = PUSH_BUTTON_START; i < PUSH_BUTTON_END; i++){
//         if(digitalRead(i+1)){
//             motor.PlayNote(enumToString(Note(i+1-PUSH_BUTTON_START)), 4);
//         }
//         else motor.TurnOff();
//     }
// }


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
            Serial.print("Playing ");
            Serial.print(note);
            Serial.print(" ");
            Serial.println(octave);
            motor.PlayNote(note, octave);
            int freq = motor.GetFrequency();
            int rpm = motor.GetRPM();
            Serial.print("motor output: ");
            Serial.print(rpm);
            Serial.print(" frequency: ");
            Serial.println(freq);
            Serial.println();
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


