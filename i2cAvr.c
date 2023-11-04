/*
 * main.c
 *
 * Created: 3/26/2022 10:32:07 AM
 *  Author: anoop
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void I2C_INIT();
char I2C_READ_DATA();
void UART_INIT();
int main(void)
{
	DDRA=DDRB=0xff;
	DDRD=0X02;
	UART_INIT();
	I2C_INIT();
	char v=I2C_READ_DATA();
	UART_TRANSMIT(v);
	char w=I2C_READ_DATA();
	UART_TRANSMIT(w);
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

void i2c_init()
{
	DDRC=0;//1111 1111
	TWAR=0xd0;//  02 0   0110 1000 0x61
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
