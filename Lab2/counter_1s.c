/**
 * Toggle LED 1sec
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

    InitGpio();
    GPIO_SetupPinOptions(31, 1, 1);
    GPIO_SetupPinOptions(34, 1, 1);

    for(;;){
        GPIO_WritePin(31, 1);
        GPIO_WritePin(34, 1);
        DELAY_US(1000000);
        GPIO_WritePin(31, 0);
        DELAY_US(1000000);
        GPIO_WritePin(31, 1);
        GPIO_WritePin(34, 0);
        DELAY_US(1000000);
        GPIO_WritePin(31, 0);
        GPIO_WritePin(34, 0);
        DELAY_US(1000000);
    }
}
