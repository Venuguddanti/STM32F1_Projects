#include "stm32f10x.h"

int main(void){
	RCC->APB2ENR |=(1<<2)|(1<<4);
	
	GPIOA->CRL &=~((1<<0)|(1<<1));
	GPIOA->CRL &=~(1<<2);
	GPIOA->CRL |=(1<<3);
	
	GPIOC->CRH |=GPIO_CRH_MODE13; 
	GPIOC->CRH &=~GPIO_CRH_CNF13;
	
	while(1)
	{
		if(GPIOA->IDR & (1<<0))
		{
			GPIOC->ODR &=~(1<<13);
		}
		else{
			GPIOC->ODR |=(1<<13);
		}
	}
}

