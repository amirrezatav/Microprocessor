#include "GPIO.h"
#include "WinkerLED.h"
#include "LPC17xx.h"                 
GPIO gpio;
	WinkerLED winker = WinkerLED();

void WinkerLEDTest()
{
	gpio.InitialIterrupt(2,11,RisingEdage);
	gpio.Initial(2, 11, GPIO_Input);
	while(true)
	{
		if(gpio.Get(2,11) == true)
		{
			winker.WinkLeft();
		}
		else
		{
			winker.WinkRight();
		}
	}
}
void WinkerLEDTest2()
{
	gpio.InitialIterrupt(2,11,RisingEdage);
	gpio.Initial(2, 11, GPIO_Input);
	while(true)
	{
		winker.Wink();
	}
}
int main()
{
	SystemInit(); // Set Frequency
	  //WinkerLEDTest();
	WinkerLEDTest2();
	return 0;
}
