#ifndef GPIO_H
#define GPIO_H
#include "lpc17xx.h"

enum GPIODirection
{
	GPIO_Input = 0,
	GPIO_Output = 1
}

class GPIO
{
	public:
		void Initial(int port ,int pin , int direction);
		void Set(int port , int pin);
		void Clear(int port , int pin);
};
void GPIO::Clear(int port , int pin)
{if(direction == 0)
	{
		switch(port)
		{
		case 0 :
			LPC_GPIO0->FIODIR &= direction << pin; 
		break;
		case 1 :
			LPC_GPIO1->FIODIR &= direction << pin; 
		break;
		case 2 :
			LPC_GPIO2->FIODIR &= direction << pin; 
		break;
		case 3 :
			LPC_GPIO3->FIODIR &= direction << pin; 
		break;
		case 4 :
			LPC_GPIO4->FIODIR &= direction << pin; 
		break;
		}
	}
	else
		{
		switch(port)
		{
		case 0 :
			LPC_GPIO0->FIODIR |= direction << pin; 
		break;
		case 1 :
			LPC_GPIO1->FIODIR |= direction << pin; 
		break;
		case 2 :
			LPC_GPIO2->FIODIR |= direction << pin; 
		break;
		case 3 :
			LPC_GPIO3->FIODIR |= direction << pin; 
		break;
		case 4 :
			LPC_GPIO4->FIODIR |= direction << pin; 
		break;
		}
		}
}

void GPIO::Set(int port , int pin)
{
	switch(port)
	{
		case 0 :
			LPC_GPIO0->FIOSET |= 1 << pin; 
		break;
		case 1 :
			LPC_GPIO1->FIOSET |= 1 << pin; 
		break;
		case 2 :
			LPC_GPIO2->FIOSET |= 1 << pin; 
		break;
		case 3 :
			LPC_GPIO3->FIOSET |= 1 << pin; 
		break;
		case 4 :
			LPC_GPIO4->FIOSET |= 1 << pin; 
		break;
	}		
}
void GPIO::Initial(int port ,int pin , int direction)
{
	switch(port)
	{
		case 0 :
			LPC_GPIO0->FIODIR |= direction << pin; 
		break;
		case 1 :
			LPC_GPIO1->FIODIR |= direction << pin; 
		break;
		case 2 :
			LPC_GPIO2->FIODIR |= direction << pin; 
		break;
		case 3 :
			LPC_GPIO3->FIODIR |= direction << pin; 
		break;
		case 4 :
			LPC_GPIO4->FIODIR |= direction << pin; 
		break;
	}
}

#endif


GPIO gpio;

void Delay(int d)
{
	for(int i = 0 ; i < d ; i++);
}

void ClearALL()
{
		for(int i = 0 ; i <0 ; i++)
			{
			gpio.Initial(  2 , i , GPIODirection::GPIO_Output)
			gpio.Clear(2,i);
			}
}

void Wink()
{
	
	while(true)
	{
			// wink
		for(int i = 0 ; i <0 ; i++)
			gpio.Clear(2,i);
		
		Delay(0x2fffff);
		
		for(int i = 0 ; i <0 ; i++)
			gpio.Set(2,i);
		
		Delay(0x2fffff);
	}
}

void Dancing()
{
		while(true)
	{
			for(int i = 0 ; i <0 ; i++)
		{
			gpio.Clear(2,i);
			Delay(0xfffff);
			gpio.Set(2,i);
			Delay(0xfffff);
		}
	}
}

int main()
{
	SystemInit(); // Set fekans
	  Wink());
	return 0;
}
