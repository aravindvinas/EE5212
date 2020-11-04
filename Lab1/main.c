

/**
 * Addition of 2 nos:
 *  var_3 = 25
 *
 * Multiplication of 2 matrices
 *   mat_3 = [19 22]
 *           [43 50]
 */  

int var_1 = 15;
int var_2 = 10;
int var_3;

int mat_1[2][2] = {{1, 2}, {3, 4}};
int mat_2[2][2] = {{5, 6}, {7, 8}};
int mat_3[2][2];
#include "F28x_Project.h"
int main(void)
{
    int i, j, k;
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0X0000;
    InitPieVectTable();

    var_3 = var_1 + var_2;      //addition of 2 nos

    for(i=0; i<2; i++)          //Multiplication of 2 matrices
    {
        for(j=0; j<2; j++)
        {
            mat_3[i][j]=0;
            for(k=0; k<2; k++)
            {
                mat_3[i][j] += mat_1[i][k] * mat_2[k][j];
            }
        }
    }

	return 0;
}
