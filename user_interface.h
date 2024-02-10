#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "slider_pot.h"
#include "motor_control.h"

#define NUM_OF_SLIDERS 4
#define NUM_OF_POS 4
#define NUM_OF_MOTORS 1

class UserInterface{
    private:
        SliderPot sliders[NUM_OF_SLIDERS];
        int slider_positions[NUM_OF_SLIDERS];
        MotorControl motors[NUM_OF_MOTORS];
    public:
        UserInterface(int slider_pin_start, int motor_pin_start);
};


#endif //USER_INTERFACE_H_