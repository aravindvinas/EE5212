

/**
 * Toggle LED Program
 */

#include "F28x_Project.h"

void delay(void);

void main(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    EALLOW;
    //Set 31 and 34 pins as GPIO's
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;

    //Set 31 and 34 as Output
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    EDIS;

    //Turn on both RED and BLUE LED's
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
}

void delay(void)
{
    long i;
    for(i=0; i<1000000; i++){
        asm("NOP");
    }
}

