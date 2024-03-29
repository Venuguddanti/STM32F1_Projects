#include "stm32f10x.h"

void delay(int);

int signal=0;
int main(void)
{
	RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |=RCC_APB2ENR_IOPCEN;
	
	GPIOC->CRH |=GPIO_CRH_MODE13;
	GPIOC->CRH &=~(GPIO_CRH_CNF13);
	
	GPIOA->CRL &=~(GPIO_CRL_MODE0);
	GPIOA->CRL |=GPIO_CRL_CNF0_1;
	GPIOA->CRL &=~(GPIO_CRL_CNF0_0);
	
	GPIOA->CRL |=GPIO_CRL_MODE6;
	GPIOA->CRL &=~(GPIO_CRL_CNF6);
	
	//RCC->APB2ENR |=RCC_APB2ENR_AFIOEN;
	
	__disable_irq();
	AFIO->EXTICR[0]=0x00;
	EXTI->IMR |=1;
	EXTI->RTSR |=1;
	NVIC_EnableIRQ(EXTI0_IRQn);
	__enable_irq();
	
	while(1)
	{
		GPIOA->ODR |=(signal<<6);
		if(signal)
		{
			GPIOC->ODR&=~(1<<13);
			delay(50);
		}
		else
		{
			GPIOC->ODR |=(1<<13);
		}
	}
}

void EXTI0_IRQHandler()
{
	EXTI->PR |=1;
	if(signal)
	{signal=0;}
	else
	{signal=1;}
}


void delay(int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<922;j++);
	}
}
