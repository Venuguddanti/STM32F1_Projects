#include "stm32f10x.h"
void delay(int time);

char ch = 'C';
int main(void)
{
	
	//Alternate function enable
	RCC->APB2ENR |=(RCC_APB2ENR_AFIOEN);
	
	//UART2 Enable Clock
	RCC->APB1ENR |=(RCC_APB1ENR_USART2EN);
	
	//Configure and enable pins for UART2
	RCC->APB2ENR |=(RCC_APB2ENR_IOPAEN); //enable clock to port A
	GPIOA->CRL |= GPIO_CRL_MODE2;        //PINA2-Tx as output alternate function
	GPIOA->CRL |= GPIO_CRL_CNF2_1;
	GPIOA->CRL &=~(GPIO_CRL_CNF2_0);
	
	GPIOA->CRL &=~(GPIO_CRL_MODE3);      //PINA3-Rx as input pin.
	GPIOA->CRL |=GPIO_CRL_CNF3_1;
	GPIOA->CRL &=~(GPIO_CRL_CNF3_0);
	
	//Setup the baudrate
	USART2->BRR =0xEA6;
	
	//enable transmit and receive
	USART2->CR1 |=(1<<2)|(1<<3);
	
	//enable the usart
	USART2->CR1 |=(1<<13);
	
	while(1)
	{
		//receive char
		while((USART2->SR & (1<<5))==0x00);
		ch=USART2->DR;
		//transmit char
		while((USART2->SR & (0x80))==0x00);
		USART2->DR =ch;
	}
}

void delay(int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{for(j=0;j<900;j++);}
}

