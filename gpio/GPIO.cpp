#include "GPIO.h"
#include "WinkerLED.h"
void GPIO::Clear(int port , int pin)
{
	LPC_GPIO[port]->FIOCLR |= 1 << pin; 
}
void GPIO::Set(int port , int pin)
{
	LPC_GPIO[port]->FIOSET |= 1 << pin; 	
}
void GPIO::Initial(int port ,int pin  , GPIODirection direction )
{
		// Initial LPC_GPIO Array 
		LPC_GPIO_TypeDef * lpc_GPIO [] = {LPC_GPIO0 , LPC_GPIO1 , LPC_GPIO2 , LPC_GPIO3 , LPC_GPIO4} ;
		LPC_GPIO = lpc_GPIO;
		
		LPC_GPIO[port]->FIODIR &= ~(1 << pin); 
		LPC_GPIO[port]->FIODIR |= (direction << pin);  
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
	return LPC_GPIO[port]->FIOPIN & (1 << pin);
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
