/*
 * ePWM 
 * 30% Duty Cycle
 */

#include "F28x_Project.h"

void Gpio_Select(void);
void Setup_ePWM3(void);

void
main(void)
{
    InitSysCtrl();
    DINT;
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

void Setup_ePWM3(void){
    EPwm4Regs.TBCTL.bit.CLKDIV = 1; // divide by 2
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = 1;  // divide by 2
    EPwm4Regs.TBCTL.bit.CTRMODE = 0;    // up mode
    EPwm4Regs.AQCTLA.all = 0x0012;  // Set high when TBCTR = 0 and low when TBCTR = CMPA
    EPwm4Regs.TBPRD =   25000; //corresponding to 1Khz
    EPwm4Regs.CMPA.bit.CMPA = EPwm4Regs.TBPRD*(0.3); //30% duty cycle
}

/***Code by EE16B131***/
