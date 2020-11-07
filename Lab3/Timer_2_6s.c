/**
 * Timer 2sec and 6sec LED glow
 */

#include "F28x_Project.h"

__interrupt void timer0_isr(void);
bool state1, state2;
int counter = 0;

void main(void)
{
    state1 = false;
    state2 = false;

    //Initialize sys resources
    InitSysCtrl();

    //Disable all interrupts (INTM)
    DINT;

    //Initialize PieCtrl regs to known state
    InitPieCtrl();

    //CPU interrupt enable and flag regs
    IER = 0x0000;
    IFR = 0x0000;

    //Initialize vector table regs to known state
    InitPieVectTable();

    EALLOW;
    PieVectTable.TIMER0_INT = &timer0_isr;  //Feed ISR address into TIMER0 vector table entry
    EDIS;

    InitCpuTimers();    //Initialise TIMERS to known state
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);    //2 sec trigger
    CpuTimer0Regs.TCR.all = 0x4000; //start TIMER0
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;   //TIMER0 interrupt
    EINT;   //INTM
    ERTM;   //Enable RealTimer interrupts Global

    //Configuring GPIO's
    InitGpio();
    GPIO_SetupPinOptions(31, 1, 1);
    GPIO_SetupPinOptions(34, 1, 1);

    while(1){}

}

__interrupt void timer0_isr(void)
{
    counter++;
    if(state1 == false){
        GPIO_WritePin(31, 1);
        state1 = true;
    }
    else{
        GPIO_WritePin(31, 0);
        state1 = false;
    }
    if(counter > 2){
        if(state2 == false){
            GPIO_WritePin(34, 1);
            state2 = true;
        }
        else{
            GPIO_WritePin(34, 0);
            state2 = false;
        }
        counter = 0;
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
