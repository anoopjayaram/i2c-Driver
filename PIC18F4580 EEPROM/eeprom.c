/*
 * File:   def.c
 * Author: anoop jayaram
 *
 * Created on 5 October, 2023, 4:54 PM
 */


#include <xc.h>
void i2c_init()
{
SSPSTAT=0x00;//1000
SSPCON1=0x28;//
SSPCON2=0x00;
SSPADD=49;
}
void i2c_start()
{
SEN=1;
while(SEN==1);//
}
void re_start()
{
RSEN=1;
while(RSEN==1);//
}
void i2c_stop()
{
PEN=1;
while(PEN==1);//
}
void i2c_data(char a)
{
SSPIF=0;
SSPBUF=a;
while(SSPIF==0);
}
char i2c_read(char a)
{
RCEN=1;//receive
while(RCEN);//
ACKDT=a;//1- NACK before stopping 0->ack
ACKEN=1;
while(ACKEN);
return SSPBUF;
}
void trans(int t)
{
    TXREG=t;
    while(TXIF==0);
    TXIF=0;
}
void I2C_SEND_DATA(int ADDRESS,char DATA)
{
    for(long i=0;i<100000;i++);
    i2c_init();
    i2c_start();//start slave ad+R/w  
    i2c_data(0XA2);//1101 000 0
    i2c_data(ADDRESS);
    i2c_data(0x00);
    i2c_data(DATA);
    i2c_stop();
    
}

char I2C_READ_DATA(int ADDRESS)
{
    for(long i=0;i<100000;i++);
    i2c_start();//start slave ad+R/w  
    i2c_data(0xA2);//1101 000 0
    i2c_data(ADDRESS);
    i2c_data(0x00);
    re_start();//i2c_start();//start slave ad+R/w  
    i2c_data(0xA3);//1101 000 0
    char read=i2c_read(1);
    i2c_stop();
    return read;
}
