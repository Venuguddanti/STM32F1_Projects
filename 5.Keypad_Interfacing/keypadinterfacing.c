#include "stm32f10x.h"

void delay(int time);
uint8_t number;
int main(void)
{
	RCC->APB2ENR |=(1<<2);
	
	//Rows as output port A0-A3
	GPIOA->CRL |=(GPIO_CRL_MODE0)|(GPIO_CRL_MODE1)|(GPIO_CRL_MODE2)|(GPIO_CRL_MODE3);
	GPIOA->CRL &=(~(GPIO_CRL_CNF0))&(~(GPIO_CRL_CNF1))&(~(GPIO_CRL_CNF2))&(~(GPIO_CRL_CNF3));
	
	//coloumns as input port A4-A7
	GPIOA->CRL &=(~(GPIO_CRL_MODE4))&(~(GPIO_CRL_MODE5))&(~(GPIO_CRL_MODE6))&(~(GPIO_CRL_MODE7));
	GPIOA->CRL |=(GPIO_CRL_CNF4_1)|(GPIO_CRL_CNF5_1)|(GPIO_CRL_CNF6_1)|(GPIO_CRL_CNF7_1);
	GPIOA->CRL &=~((GPIO_CRL_CNF4_0)|(GPIO_CRL_CNF5_0)|(GPIO_CRL_CNF6_0)|(GPIO_CRL_CNF7_0));
	
	while(1)
	{
		//row 1
		GPIOA->ODR |=(1<<0);
		GPIOA->ODR &=~((1<<1)|(1<<2)|(1<<3));
		if(((GPIOA->IDR &(1<<4))>>4)==1){number=1;delay(100);}
		if(((GPIOA->IDR &(1<<5))>>5)==1){number=2;delay(100);}
		if(((GPIOA->IDR &(1<<6))>>6)==1){number=3;delay(100);}
		if(((GPIOA->IDR &(1<<7))>>7)==1){number='A';delay(100);}
		
		//row 2
		GPIOA->ODR |=(1<<1);
		GPIOA->ODR &=~((1<<0)|(1<<2)|(1<<3));
		if(((GPIOA->IDR &(1<<4))>>4)==1){number=4;delay(100);}
		if(((GPIOA->IDR &(1<<5))>>5)==1){number=5;delay(100);}
		if(((GPIOA->IDR &(1<<6))>>6)==1){number=6;delay(100);}
		if(((GPIOA->IDR &(1<<7))>>7)==1){number='B';delay(100);}
		
		//row 3
		GPIOA->ODR |=(1<<2);
		GPIOA->ODR &=~((1<<0)|(1<<1)|(1<<3));
		if(((GPIOA->IDR &(1<<4))>>4)==1){number=7;delay(100);}
		if(((GPIOA->IDR &(1<<5))>>5)==1){number=8;delay(100);}
		if(((GPIOA->IDR &(1<<6))>>6)==1){number=9;delay(100);}
		if(((GPIOA->IDR &(1<<7))>>7)==1){number='C';delay(100);}
		
		//row 4
		GPIOA->ODR |=(1<<3);
		GPIOA->ODR &=~((1<<0)|(1<<1)|(1<<1));
		if(((GPIOA->IDR &(1<<4))>>4)==1){number='*';delay(100);}
		if(((GPIOA->IDR &(1<<5))>>5)==1){number=0;delay(100);}
		if(((GPIOA->IDR &(1<<6))>>6)==1){number='#';delay(100);}
		if(((GPIOA->IDR &(1<<7))>>7)==1){number='D';delay(100);}
	}
	
}

void delay(int time)
{
	int i;int j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<900;j++);
	}
}

