#ifndef GPIO_H
#define GPIO_H
#include "LPC17xx.h"                    // Device header

enum GPIODirection
{
	GPIO_Input = 0,
	GPIO_Output = 1
};

enum SignalEdge
{
	FallingEdage = 0 ,
	RisingEdage = 1
};

class GPIO
{
	private:
		LPC_GPIO_TypeDef** LPC_GPIO;
	public:
		void InitialIterrupt(int port , int pin , SignalEdge edage);
		void Initial(int port ,int pin , GPIODirection direction );
		void Set(int port , int pin);
		void Clear(int port , int pin);
		bool Get(int port , int pin);
		bool GetInterruptStatus(int port , int pin , SignalEdge edage);
		void ClearInterrupt(int port , int pin);		
};
#endif
