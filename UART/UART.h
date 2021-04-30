#ifndef UART_H
#define UART_H

enum WordLength
{
	Word_5bit,  // 00
	Word_6bit,  // 01
	Word_7bit,  // 10
	Word_8bit,  // 11
};
enum StopBit 
{
	OneStopBit,  // 0
	TwoStopBit   // 1
};
enum ParityType
{
	OddParity,   // 00
	EvenParity,  // 01
	ForceOne,    // 10
	ForceZero,   // 11
	NoneParity
};
class UART
{
	public :
		void Initial(int uartNum , int buadRate , WordLength wordLength , StopBit stopBit , ParityType parityType);
		void Send(int uartNum , char data);
		char Receive(int uartNum);
	private:
		void SetBaudRate(int uartNum, int Baudrate);
};
#endif
