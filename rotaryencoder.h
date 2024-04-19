#ifndef ROTARYENCODER_H_
#define ROTARYECODER_H_
#include "Arduino.h"
#define SLIDER_MAX_VALUE 23610
//#include "digitalWriteFast.h"
#ifdef ARDUINO_AVR_MEGA2560
#define BOARD "MEGA2560"
#define outA 3
#define outB 2
#define OUTA_PORT PE5
#define OUTB_PORT PE4
#define PIN_TYPE PINE
#elif defined(ARDUINO_AVR_UNO)
#define BOARD "UNO"
#define outA 3
#define outB 2
#define OUTA_PORT PD3
#define OUTB_PORT PD2
#define PIN_TYPE PIND
#endif
class RotaryEncoder{
    private:
        volatile long position;
        volatile bool last_outA_value;
        volatile bool last_outB_value;
    public:
        RotaryEncoder();
        void ReadState();
        long GetPositon();
        void SetPositionMax();
        void SetPositionMin();
};

#endif