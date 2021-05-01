#include "UART.h"

void UART::Initial(int uartNum , int buadRate , WordLength wordLength , StopBit stopBit , ParityType parityType)
{
		SetBaudRate(uartNum , buadRate);
		LPC_UART_TypeDef * lPC_UART [] = {LPC_UART0 , 0 , LPC_UART2 , 0};
		LPC_UART = lPC_UART;
		LPC_UART[uartNum]->LCR = wordLength | (stopBit<<2) | (parityType != NoneParity)? ( (1<<3)|(parityType<<4) ) : (0<<3);
	switch(uartNum)
	{
			case 0:
				
			break;
			case 2: 		
				LPC_SC->PCONP |= 1 << 24 ; // Turn On Uart 2 
			                        // 0b11<<20
				LPC_PINCON->PINSEL0 &= !(0x300000); // reset P0,10
				LPC_PINCON->PINSEL0 |= !(1<<20); // set P0,10 = TXD2
			                      // 0b11<<22	
				LPC_PINCON->PINSEL0 &= !(0xc00000); // reset P0,11
				LPC_PINCON->PINSEL0 |= !(1<<22); // set P0,11 = RXD2
			break;
	}
}

void UART::Send(int uartNum , char data)
{
		  // 1 << 5 =32 =0b10000=0x20
			// waite while 5th bit of LPC_UART0->LSR is 0 => mean There is data for sending 
			while(!(LPC_UART0->LSR & 0x20)); 
			LPC_UART[uartNum]->THR = data; // send data 
}

char UART::Receive(int uartNum)
{
	 // waite while first bit of LPC_UART0->LSR is 0 => mean There isn't data for recieving 
		while(!(LPC_UART0->LSR & 1)); 
		return LPC_UART[uartNum]->RBR;// Receive data 
}
extern int SystemFrequency;
void UART::SetBaudRate(int uartNum, int Baudrate)
 {
	unsigned int uClk = SystemFrequency >> 2;
	unsigned int d, m, bestd, bestm, tmp;
	uint64_t best_divisor, divisor;
	unsigned int current_error, best_error;
	unsigned int recalcbaud;
	best_error = 0xFFFFFFFF; /* Worst case */
	bestd = 0;
	bestm = 0;
	best_divisor = 0;
	for (m = 1 ; m <= 15 ;m++)
	{
		for (d = 0 ; d < m ; d++)
		{
			divisor = ((uint64_t)uClk * 268435456)*m / (Baudrate*(m+d));
			current_error = divisor & 0xFFFFFFFF;

			tmp = divisor / 4294967296;

			/* Adjust error */
			if(current_error > ((unsigned int)0x80000000))
			{
				current_error = -current_error;
				tmp++;
			}

			/* Out of range */
			if(tmp < 1 || tmp > 65536)
				continue;

			if( current_error < best_error)
			{
				best_error = current_error;
				best_divisor = tmp;
				bestd = d;
				bestm = m;
				
				if(best_error == 0) 
					break;
			}
		} /* end of inner for loop */

		if (best_error == 0)
			break;
	} /* end of outer for loop  */
	recalcbaud = (uClk >> 4) * bestm / (best_divisor * (bestm + bestd));
	/* reuse best_error to evaluate baud error*/
	if(Baudrate > recalcbaud) 
		best_error = Baudrate - recalcbaud;
	else 
		best_error = recalcbaud - Baudrate;
	best_error = best_error * 100 / Baudrate;
 	if (best_error < 3)
	{
		LPC_UART[uartNum]->LCR |= 0x80;
		LPC_UART[uartNum]->DLM = (best_divisor >> 8) & 0xFF;
		LPC_UART[uartNum]->DLL = best_divisor & 0xFF;
		/* Then reset DLAB bit */
		LPC_UART[uartNum]->LCR &= ~0x80;
		LPC_UART[uartNum]->FDR = ((bestm << 4) & 0xF0)| (bestd & 0x0F);		 
	}
}
