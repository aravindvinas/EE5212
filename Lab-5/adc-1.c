/*
 * adc-1.c
 */

#include "F28x_Project.h"

void adc_setup(void);
void res(void);
void ini(void);
void dac_start(void);
__interrupt void isr(void);
Uint16 AdcaResult0;
Uint16 DAC_input = 0;
bool begin  = 1;
void main(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    InitCpuTimers();
    EALLOW;
    PieVectTable.TIMER0_INT = &isr;
    EDIS;
    ConfigCpuTimer(&CpuTimer0, 2000, 100000);
    CpuTimer0Regs.TCR.all = 0x4000;
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    EINT;
    ERTM;
    adc_setup();
    res();
    ini();
    while(1)
	{
      DacaRegs.DACVALS.bit.DACVALS = DAC_input;
      AdcaRegs.ADCSOCFRC1.all = 0x0001;
      while(AdcaRegs.ADCINTFLG.bit.ADCINT1==0);
      AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
      AdcaResult0 = AdcaResultRegs.ADCRESULT0;
    }
}

void adc_setup(void)
{
    EALLOW;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;//by 4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    DELAY_US(1000);
    EDIS;
}

void res(void)
{
    Uint16 acqps;
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
	{
        acqps = 14;
    }
    else
	{
        acqps = 63;
    }
    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 2; 
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; 
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0;
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    EDIS;
}

void ini(void)
{
    EALLOW;
    DacaRegs.DACCTL.bit.DACREFSEL = 1;
    DacaRegs.DACCTL.bit.LOADMODE = 0;
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1;
    DacaRegs.DACVALS.bit.DACVALS = DAC_input;
    DAC_input += 500;
    DELAY_US(10);
    EDIS;
}

void dac_start(void)
{
    EALLOW;
    DacaRegs.DACCTL.bit.DACREFSEL = 1;
    DacaRegs.DACCTL.bit.LOADMODE = 0;
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1;
    DacaRegs.DACVALS.bit.DACVALS = DAC_input;
    DAC_input += 500;
    EDIS;
}

__interrupt void isr(void)
{
    CpuTimer0.InterruptCount++;
    if(DAC_input < 4095 && begin)
	{
        InitDaca();
        begin = 0;
    }
    else if(DAC_input<4095 && !begin)
	{
        dac_start();
    }
    else
	{
        DAC_input = 0;
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
/***Code by EE16B131***/
