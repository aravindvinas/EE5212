/*
 * ePWM
 * SPWM Code
 */

#include "F28x_Project.h"
#include "math.h"

__interrupt void timer0_isr(void);
float theta = 0.0, sine_value = 0.0, sine_shifted = 0.0;
float m_index = 40, PI = 3.1416, Ts = 0.0002;
int sine_freq = 40;

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
    EPwm4Regs.TBCTL.bit.CLKDIV = 1; // divide by 2
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = 1;  // divide by 2
    EPwm4Regs.TBCTL.bit.CTRMODE = 2;    // up down mode
    EPwm4Regs.AQCTLA.bit.CAU = 2;
    EPwm4Regs.AQCTLA.bit.CAD = 1;
    EPwm4Regs.TBPRD =   2500; //corresponding to 1Khz
    EPwm4Regs.TBCTL.bit.SYNCOSEL = 1; //Master
    EPwm4Regs.CMPA.bit.CMPA = sine_shifted*2500;
}

__interrupt void timer0_isr(void)
{
    EPwm4Regs.CMPA.bit.CMPA = sine_shifted*2500;
    if(theta<(2*PI)){
    sine_value = sin(theta);
    sine_shifted = 0.5 + (m_index*sine_value)/2;
    theta = theta + (2*PI*sine_freq*Ts);
  }
  
    else{
    theta = 0;
    sine_value = sin(theta);
    sine_shifted = 0.5 + (m_index*sine_value)/2;
}
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/*** Code by EE16B131 ***/

