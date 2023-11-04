#include<pic18.h>
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
while(SEN==1);// start bit
}
void i2c_stop()
{
PEN=1;
while(PEN==1);// stop bit
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
void main()
{

TRISB=TRISD=0x00;
TRISC=0x18;
for(long i=0;i<100000;i++);
i2c_init();
i2c_start();//start slave ad+R/w  
for(long i=0;i<100000;i++);
i2c_data(0xd0);//1101 000 0
i2c_data('S');
 
i2c_data('M');

i2c_stop(); 


while(1)
{


}
}

