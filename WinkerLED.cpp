#include "WinkerLED.h"
#include "gpio.h"

extern GPIO gpio;

void WinkerLED::Initial()
{
	for(int i = 0 ; i <0 ; i++)
			{
			gpio.Initial(  2 , i , GPIO_Output);
			gpio.Clear(2,i);
			}
}
WinkerLED::WinkerLED(void)
{
	Initial();
}

void WinkerLED::WinkRight()
{
	for(int i = 0 ; i < 8 ; i++)
		{
			gpio.Clear(2,i);
			Delay(0x20ffff);
			gpio.Set(2,i);
			Delay(0x20ffff);
			gpio.Clear(2,i);
		}
}

void WinkerLED::WinkLeft()
{
	for(int i = 7 ; i >= 0 ; i--)
		{
			gpio.Clear(2,i);
			Delay(0x20ffff);
			gpio.Set(2,i);
			Delay(0x20ffff);
			gpio.Clear(2,i);
		}
}
	
void WinkerLED::Delay(int d)
{
	for(int i = 0 ; i < d ; i++); 
}
void WinkerLED::IterruptHandler()
{
		if(gpio.GetInterruptStatus(2,11,RisingEdage))
				direction = (Direction)!(direction);		
}

void WinkerLED::Wink()
{
	for(int i = (direction == Right)? 0 : 7 ; i < 8 && i>= 0; (direction == Right)? i++ : i--)
		{
			gpio.Clear(2,i);
			Delay(0x20ffff);
			gpio.Set(2,i);
			Delay(0x20ffff);
			gpio.Clear(2,i);
		}
}