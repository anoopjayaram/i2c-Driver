#include<pic18.h>
#include "header.h"

void main()
{
    char DATA;
    TRISB=TRISD=0x00;
    TRISC=0x18;
    TXSTA=0X24;
    RCSTA=0X90;
    SPBRG=129;
    I2C_SEND_DATA(5,'A');
    DATA=I2C_READ_DATA(5);
    trans(DATA);
    I2C_SEND_DATA(7,'N');
    DATA=I2C_READ_DATA(7);
    trans(DATA);
    while(1)
    {

   }
}
