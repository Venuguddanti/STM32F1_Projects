#include "stm32f10x.h"
void delay(int);
int main(void){
	
	RCC->APB2ENR |=(1<<4);
	
	GPIOC->CRH |=(1<<20)|(1<<21);
	GPIOC->CRH &=~(1<<22);
	GPIOC->CRH &=~(1<<23);
	
	while(1){
		GPIOC->ODR |=(1<<13);
		delay(100);
		GPIOC->ODR &=~(1<<13);
		delay(100);
	}
}
void delay(int time)
{
	int i;int j;
	for(i=0;i<time;i++){
		for(j=0;j<5000;j++);
	}
}

