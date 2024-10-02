/*
 * File:   slave.c
 * Author: anoop
 * 
 * Created on 2 October, 2024, 10:27 AM
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void I2C_INIT();
char I2C_READ_DATA();
void UART_INIT();
void UART_TRANSMIT(char b);
int main(void)
{
	DDRA=DDRB=0xff;
	DDRD=0X02;
	UART_INIT();

	while(1)
	{
        I2C_INIT();
	char v=I2C_READ_DATA();
 	UART_TRANSMIT(v);
        UART_TRANSMIT('\r');
        UART_TRANSMIT('\n');
    }
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
	DDRC=0; 
	TWAR=0xd0;//  SLAVE ADDRESS 
	TWCR=0x44;//ack
	TWCR|=0x80;// TWCR=TWCR|0x80
	while((TWCR&(0x80))==0);//slave

}

char I2C_READ_DATA()
{
	TWCR=0x44;// TWCR=0x44;  Clear TWI interrupt flag,Enable TWI
	TWCR|=0x80;
	while (!(TWCR & (1<<TWINT))); //while((TWCR&(0x80))==0); slave ad+W
	return TWDR;

}
