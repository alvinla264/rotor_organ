#ifndef SLIDER_POT_H_
#define SLIDER_POT_H_

#include "Arduino.h"

#define THRESHOLD 50
class SliderPot{
    private:
        int pin;
        int position; //current position 0 to (interval-1)
        int num_of_positions;
        int interval;
    public:
        SliderPot();
        SliderPot(int pot_pin, int num_of_pos);
        int GetPosition();
};

#endif //SLIDER_POT_H_