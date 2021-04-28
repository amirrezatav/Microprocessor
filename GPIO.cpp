#include "lpc17xx.h"
#include "GPIO.h"
#include "WinkerLED.h"

void GPIO::Clear(int port , int pin)
{
	switch(port)
	{
		case 0 :
			LPC_GPIO0->FIOCLR |= 1 << pin; 
		break;
		case 1 :
			LPC_GPIO1->FIOCLR |= 1 << pin; 
		break;
		case 2 :
			LPC_GPIO2->FIOCLR |= 1 << pin; 
		break;
		case 3 :
			LPC_GPIO3->FIOCLR |= 1 << pin; 
		break;
		case 4 :
			LPC_GPIO4->FIOCLR |= 1 << pin; 
		break;
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
void GPIO::Initial(int port ,int pin  , GPIODirection direction )
{
		switch(port)
		{
		case 0 :
			LPC_GPIO0->FIODIR &= ~(1 << pin); 
			LPC_GPIO0->FIODIR |= (direction << pin);  
		break;
		case 1 :
			LPC_GPIO1->FIODIR &= ~(1 << pin); 
			LPC_GPIO0->FIODIR |= (direction << pin);  

		break;
		case 2 :
			LPC_GPIO2->FIODIR &= ~(1 << pin); 
			LPC_GPIO0->FIODIR |= (direction << pin);
		break;
		case 3 :
			LPC_GPIO3->FIODIR &= ~(1 << pin);
			LPC_GPIO0->FIODIR |= (direction << pin);		
		break;
		case 4 :
			LPC_GPIO4->FIODIR &= ~(1 << pin); 
			LPC_GPIO0->FIODIR |= (direction << pin);
		break;
		}
	
}

void GPIO::InitialIterrupt(int port , int pin , SignalEdge edage)
{
		NVIC_EnableIRQ(EINT3_IRQn);
		Initial(port,pin,GPIO_Input);
	switch(port)
		{
		case 0 :
			if(edage == RisingEdage)
			LPC_GPIOINT->IO0IntEnR |= 1 << pin;
		else
			LPC_GPIOINT->IO0IntEnF |= 1 << pin;
		break;
		case 2 :
			if(edage == RisingEdage)
			LPC_GPIOINT->IO2IntEnR |= 1 << pin;
		else
			LPC_GPIOINT->IO2IntEnF |= 1 << pin; 
		break;
		}
		
}


bool GPIO::Get(int port , int pin)
{
	switch(port)
  {
		case 0 : return 	LPC_GPIO0->FIOPIN & (1 << pin);
		case 1 : return 	LPC_GPIO1->FIOPIN & (1 << pin);
		case 2 : return 	LPC_GPIO2->FIOPIN & (1 << pin);
		case 3 : return 	LPC_GPIO3->FIOPIN & (1 << pin);
		case 4 : return 	LPC_GPIO4->FIOPIN & (1 << pin);
		default: return false;
	}
}
bool GPIO::GetInterruptStatus(int port , int pin , SignalEdge edage)
{
	switch(port)
		{
		case 0 :
			if(edage == RisingEdage)
				return LPC_GPIOINT->IO0IntStatR & (1 << pin);
			else
				return LPC_GPIOINT->IO0IntStatF & (1 << pin);
		break;
		case 2 :
			if(edage == RisingEdage)
			  return LPC_GPIOINT->IO2IntStatR & (1 << pin);
		  else
			 return LPC_GPIOINT->IO2IntStatF & (1 << pin);
		break;
			default : return false;
		}
}
void GPIO::ClearInterrupt(int port , int pin)
{
	switch(port)
		{
		case 0 :
				 LPC_GPIOINT->IO0IntClr = 1 << pin;
		break;
		case 2 :
				LPC_GPIOINT->IO2IntClr = 1 << pin;
		break;
		}
}
extern WinkerLED winker ;
extern "C"
{
void EINT3_IRQHandler()
{
	winker.IterruptHandler();
}
}

