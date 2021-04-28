#include "BlinkedLED.h"
#include "gpio.h"

extern GPIO gpio;

void BlinkedLED::Init()
{
	direction = true;
	for (int i = 0; i < 8; i++)
	{
		gpio.Init(2, i, GPIO_Output);
		gpio.Clear(2, i);
	}
}

void BlinkedLED::BlinkRight()
{
	for (int i = 0; i < 8; i++)
	{
			gpio.Clear(2, i);
			Delay(0x20ffff);
			gpio.Set(2, i);
			Delay(0x20ffff);
			gpio.Clear(2, i);
	}
}

void BlinkedLED::BlinkLeft()
{
	for (int i = 7; i >= 0; i--)
	{
			gpio.Clear(2, i);
			Delay(0x20ffff);
			gpio.Set(2, i);
			Delay(0x20ffff);
			gpio.Clear(2, i);
	}
}

void BlinkedLED::Blink()
{
	int i = 0;
	if (direction == false) i = 7;
	for (; i < 8 && i >= 0; )
	{
			gpio.Clear(2, i);
			Delay(0x20ffff);
			gpio.Set(2, i);
			Delay(0x20ffff);
			gpio.Clear(2, i);
			if (direction) i++;
			else i--;
	}
}

void BlinkedLED::Delay(int d)
{
	for (int i = 0; i < d; i++);
}

void BlinkedLED::InterruptHandler()
{
	if (gpio.GetInterruptStatus(2, 11, RisingEdge))
		direction = !direction;
	gpio.ClearInterrupt(2, 11);
}
