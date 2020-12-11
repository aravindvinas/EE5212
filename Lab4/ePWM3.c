/*
 * ePWM
 * Phase Shifting PWM
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

void Gpio_Select(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0; 
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1; 
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1; 
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
    EPwm3Regs.TBCTL.bit.CTRMODE = 1; 
    EPwm3Regs.TBCTL.bit.CLKDIV = 1;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = 1;
    EPwm3Regs.TBPRD = 5000; 
    EPwm3Regs.CMPA.bit.CMPA = EPwm3Regs.TBPRD*(0.3); 
    EPwm3Regs.TBCTL.bit.CTRMODE = 1; 
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE; 
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 
    EPwm3Regs.AQCTLA.bit.CAD = 10;  
    EPwm3Regs.AQCTLA.bit.ZRO = 01;
    EPwm3Regs.TBPHS.bit.TBPHS = 1250; 
    EPwm2Regs.TBCTL.bit.CTRMODE = 1; 
    EPwm2Regs.TBCTL.bit.CLKDIV = 1;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 1;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE; 
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; 
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; 
    EPwm2Regs.AQCTLA.bit.CAD = 10;  
    EPwm2Regs.AQCTLA.bit.ZRO = 01;
    EPwm2Regs.TBPRD = 5000; 
    EPwm2Regs.CMPA.bit.CMPA = EPwm2Regs.TBPRD*(0.3); 
    EPwm2Regs.TBPHS.bit.TBPHS = 0; 


}

/***Code by EE16B131***/




