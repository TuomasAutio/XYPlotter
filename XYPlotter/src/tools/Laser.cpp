#include "Laser.h"
#include "chip.h"


Laser::Laser(int port, int pin)
{
        Chip_SCT_Init(LPC_SCT1);
        Chip_SWM_MovablePortPinAssign(SWM_SCT1_OUT0_O, port, pin);

        LPC_SCT1->CONFIG |= (0 << 17);
        LPC_SCT1->CTRL_L |= (72 - 1) << 5;// Set prescaler, SCTimer/PWM Clock = 1 Mhz

        LPC_SCT1->MATCHREL[0].L = 20000-1;// Match 0 @ 1000/1MHz = (1 kHz PWM freq)
        LPC_SCT1->MATCHREL[1].L = 1;// Match 1 user for duty cycle (in 10 steps)

        LPC_SCT1->EVENT[0].STATE = 0xFFFFFFFF;// Event 0 happens in all states
        LPC_SCT1->EVENT[0].CTRL = (1 << 12);// Match 0 condition only

        LPC_SCT1->EVENT[1].STATE = 0xFFFFFFFF;// Event 1 happens in all state
        LPC_SCT1->EVENT[1].CTRL = (1 << 0) | (1 << 12);// Match 1 condition only

        // LPC_SCT1->OUT[0].SET = (1 << 0);// Event 0 will set SCTx_OUT0
        LPC_SCT1->OUT[0].CLR = (1 << 1);// Event 1 will clear SCTx_OUT0

        LPC_SCT1->CTRL_L &= ~(1 << 2);// Unhalt by clearing bit 2 of CTRL req

}
void Laser::setVal(signed int val){
    int percent = (int) (((float)val/255)*100);
    if(percent > 0) {
            LPC_SCT1->OUT[0].SET = (1 << 0); // event 2 will set SCTx_OUT0
            LPC_SCT1->MATCHREL[1].L = percent * 200;
        }
        else {
            LPC_SCT1->OUT[0].SET = 0; // event 2 has no effect on  SCTx_OUT0 --> laser is always off
            LPC_SCT1->MATCHREL[1].L = 1;
        }

}
