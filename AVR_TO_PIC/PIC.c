//PIC MASTER <- ATMEGA
#include<pic18.h>
void I2C_INIT();
void _I2C_START();
void _I2C_STOP();
void I2C_SEND_DATA(char a);
char I2C_READ_DATA(char a);
void TRANSMIT_CHAR(char b);
void main()
{
	int i;
    TRISD=0x00;
    TRISC=0x18;
    TXSTA=0x24;
    RCSTA=0x90;
    SPBRG=129;
    I2C_INIT();
    _I2C_START();//start slavead+R/w  
    I2C_SEND_DATA(0xf1);//1101 00 d0 and 1
    char m=I2C_READ_DATA(0);
    TRANSMIT_CHAR(m);

    m=I2C_READ_DATA(1);
    TRANSMIT_CHAR(m);
    _I2C_STOP();
    while(1) 	
    {

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
void TRANSMIT_CHAR(char b)
 {
    while(TXIF==0);
    TXREG=b; 
    TXIF=0;
 }
