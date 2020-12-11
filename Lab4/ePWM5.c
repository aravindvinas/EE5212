/*
 * ePWM
 * Increment Phase
 */

#include "F28x_Project.h"

__interrupt void timer0_isr(void);
int phase = 90;

void Gpio_Select(void);
void Setup_ePWM3(void);

void
main(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    EALLOW;
    PieVectTable.TIMER0_INT = &timer0_isr;
    EDIS;
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);
    CpuTimer0Regs.TCR.all = 0x4000;
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    EINT;
    ERTM;
    Gpio_Select();
    Setup_ePWM3();
    while(1){}
}

void Gpio_Select(void){
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
    GpioCtrlRegs.GPAMUX2.all = 0;
    GpioCtrlRegs.GPBMUX1.all = 0;
    GpioCtrlRegs.GPBMUX2.all = 0;
    GpioCtrlRegs.GPCMUX1.all = 0;
    GpioCtrlRegs.GPCMUX2.all = 0;
    GpioCtrlRegs.GPDMUX1.all = 0;
    GpioCtrlRegs.GPDMUX2.all = 0;
    GpioCtrlRegs.GPEMUX1.all = 0;
    GpioCtrlRegs.GPEMUX2.all = 0;
    GpioCtrlRegs.GPFMUX1.all = 0;
    //GpioCtrlRegs.GPFMUX2.all = 0;

    GpioCtrlRegs.GPADIR.all = 0;
    GpioCtrlRegs.GPBDIR.all = 0;
    GpioCtrlRegs.GPCDIR.all = 0;
    GpioCtrlRegs.GPDDIR.all = 0;
    GpioCtrlRegs.GPEDIR.all = 0;
    GpioCtrlRegs.GPFDIR.all = 0;
    EDIS;
}

void Setup_ePWM3(void)
{
    EPwm4Regs.TBCTL.bit.CLKDIV = 0; // divide by 1
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0;  // divide by 1
    EPwm4Regs.TBCTL.bit.CTRMODE = 1;    // down mode
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm4Regs.TBPRD =   25000; //corresponding to 1Khz
    EPwm4Regs.TBCTL.bit.SYNCOSEL = 0;
    EPwm4Regs.TBCTL.bit.PHSEN = 1;
    EPwm4Regs.TBPHS.bit.TBPHS = 1000*phase/10;
    if(phase == 0){phase = 360;}
    else{phase -= 5;}
}

__interrupt void timer0_isr(void)
{
    Setup_ePWM3();
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/*** Code by EE16B131 ***/

