#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void I2C_INIT();
char I2C_READ_DATA();
void UART_INIT();
void UART_TRANSMIT(char b);
void I2C_SEND_DATA(char a);
int main(void)
{
	DDRA=DDRB=0xff;
	DDRD=0X02;
	UART_INIT();
	I2C_INIT();
	I2C_SEND_DATA('A');
    I2C_SEND_DATA('B');
	while(1);
}

void UART_INIT()
{
	UCSRA=0X00;
	UCSRB=0X18;
	UCSRC=0X86;
	UBRRL=0X33;
	UBRRH=0X00;
}

void UART_TRANSMIT(char b)
{
	while((UCSRA&0X20)==0);
	UCSRA=0X20;
    UDR=b;	
}

void I2C_INIT()
{
	DDRC=0;//1111 1111
	TWAR=0xf0;//  02 0   0110 1000 0x61
	TWCR=0x44;//ack
	TWCR|=0x80;// TWCR=TWCR|0x80
	while((TWCR&(0x80))==0);//slave

}

char I2C_READ_DATA()
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);  // TWCR=0x44;  Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); //while((TWCR&(0x80))==0); slave ad+W
	return TWDR;

}
void I2C_SEND_DATA(char a)
{
TWDR=a;
TWCR=0x44;//
TWCR|=0x80;
while((TWCR&(0x80))==0);

}
