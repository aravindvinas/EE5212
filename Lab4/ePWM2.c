/*
 * ePWM 
 * 60% Duty Cycle
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
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
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
    EPwm3Regs.TBCTL.bit.CTRMODE = 2; // up-down mode
    EPwm3Regs.TBCTL.bit.CLKDIV = 1; // divide by 2
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = 1;  // divide by 2
    EPwm3Regs.TBCTL.bit.CTRMODE = 2;    // up-down mode
    EPwm3Regs.AQCTLA.all = 0x0061;
    EPwm3Regs.AQCTLB.all = 0x0902;
    EPwm3Regs.TBPRD =   6250; //corresponding to 2Khz
    EPwm3Regs.CMPA.bit.CMPA = EPwm3Regs.TBPRD*(1-0.6); //60% duty cycle
    EPwm3Regs.CMPB.bit.CMPB = EPwm3Regs.TBPRD*(1-0.6); //60% duty cycle
}

/***Code by EE16B131***/



