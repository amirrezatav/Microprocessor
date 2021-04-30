#include "UART.h"
UART _uart;
void Delay(int d)
{
	for(int i = 0 ; i < d ; i++); 
}
void UartTest()
{
	_uart.Initial(2,9600,Word_8bit,OneStopBit , NoneParity);
	// Build operating systems
	while(true)
	{
		_uart.Send(2,'A');
		Delay(0xffffff);
	}
}
int main()
{
	SystemInit(); // Set fekans
	UartTest();
	return 0;
}
