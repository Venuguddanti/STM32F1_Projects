#include "stm32f10x.h"
void delay(int t);
void systick_init(void);
void systick_delay(void);
void delayMs(unsigned long t);

int main(void)
{
	systick_init();
	RCC->APB2ENR |=(1<<4);
	
	GPIOC->CRH |= GPIO_CRH_MODE13;
	GPIOC->CRH &=~(GPIO_CRH_CNF13);
	
	while(1)
	{
		GPIOC->ODR &=~(GPIO_ODR_ODR13);
		delayMs(1000);
		GPIOC->ODR |=(GPIO_ODR_ODR13);
		delayMs(1000);
	}
}
/*void delay(int t)
{
	int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<900;j++);
	}
}
*/
void systick_init(void)
{
	SysTick->CTRL =0;
	SysTick->LOAD=0x00FFFFFF;
	SysTick->VAL =0;
	SysTick->CTRL |=((1<<0)|(1<<2));
}
void systick_delay(void)
{
	SysTick->LOAD =72000-1;
	SysTick->VAL=0;
	while((SysTick->CTRL & (1<<16))==0);
	
}
void delayMs(unsigned long t)
{
	for(;t>0;t--)
	{
		systick_delay();
	}
}

