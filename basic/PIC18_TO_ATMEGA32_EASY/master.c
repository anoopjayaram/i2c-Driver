/*
 * File:   master.c
 * Author: anoop jayaram
 * Added data sending in loop
 * Created on 2 October, 2024, 10:25 AM
 */



#include<pic18.h>
void I2C_INIT();
void _I2C_STOP();
void I2C_SEND_DATA(char a);
char I2C_READ_DATA(char a);
void _I2C_START();
void main()
{
TRISB=TRISD=0x00;
TRISC=0x18;
int INTEGER_DATA=0;
while(1){

I2C_INIT();
_I2C_START();//start slave ad+R/w  
for(long i=0;i<100000;i++);//delay
I2C_SEND_DATA(0xd0);//1101 000 0
I2C_SEND_DATA(INTEGER_DATA +48);
_I2C_STOP();
INTEGER_DATA++;
for(long i=0;i<500000;i++);//delay
if (INTEGER_DATA>9)
{
    INTEGER_DATA=0;
}
}

}

void I2C_INIT()
{
SSPSTAT=0x00;//1000
SSPCON1=0x28;//
SSPCON2=0x00;
SSPADD=49;
} 
void _I2C_START()
{
SEN=1;
while(SEN==1);//
}

void _I2C_STOP()
{
PEN=1;
while(PEN==1);// 
}
void I2C_SEND_DATA(char a)
{
SSPIF=0;
SSPBUF=a;
while(SSPIF==0);
}
char I2C_READ_DATA(char a)
{
RCEN=1;//receive
while(RCEN);//
ACKDT=a;//1- NACK before stopping 0->ack
ACKEN=1;
while(ACKEN);
return SSPBUF;
}
