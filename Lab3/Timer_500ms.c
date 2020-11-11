/**
 * Timer 500ms interrupt
 */

#include "F28x_Project.h"

__interrupt void timer0_isr(void);
bool state;

void main(void)
{
    state = false;

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
    ConfigCpuTimer(&CpuTimer0, 200, 2500000);    //500 millis trigger
    CpuTimer0Regs.TCR.all = 0x4000; //start TIMER0
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;   //TIMER0 interrupt
    EINT;   //INTM
    ERTM;   //Enable RealTimer interrupts Global

    //Configuring GPIO's
    InitGpio();
    GPIO_SetupPinOptions(31, 1, 1);

    while(1){}

}

__interrupt void timer0_isr(void)
{
    if(state == false){
        GPIO_WritePin(31, 1);
        state = true;
    }
    else{
        GPIO_WritePin(31, 0);
        state = false;
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

