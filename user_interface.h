#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "slider_pot.h"
#include "motor_control.h"

#define NUM_OF_SLIDERS 4
#define NUM_OF_POS 4
#define NUM_OF_BUTTONS 4

class UserInterface{
    private:
        SliderPot sliders[NUM_OF_SLIDERS];
        int button_start;
        
    public:
        bool button_status[NUM_OF_BUTTONS];
        int slider_positions[NUM_OF_SLIDERS];
        UserInterface(int slider_pin_start, int bttn_start);
        void ReadSliderPosition();
        void ReadButtonPosition();
};


#endif //USER_INTERFACE_H_