/*
 * ePWM 
 * Increment Duty Cycle
 */

#include "F28x_Project.h"

__interrupt void timer0_isr(void);
float isr_count = 0.1;

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
    EPwm4Regs.TBCTL.bit.CTRMODE = 0;    // up mode
    EPwm4Regs.AQCTLA.all = 0x0012;  // Set high when TBCTR = 0 and low when TBCTR = CMPA
    EPwm4Regs.TBPRD =   25000; //corresponding to 1Khz
    EPwm4Regs.CMPA.bit.CMPA = EPwm4Regs.TBPRD*(isr_count); //varying duty cycle
    isr_count += 0.30;
    if(isr_count >= 1) {isr_count = 0.1;}
}

__interrupt void timer0_isr(void)
{
    Setup_ePWM3();
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/*** Code by EE16B131 ***/

