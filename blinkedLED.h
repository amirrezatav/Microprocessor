#ifndef BLINKEDLED_H
#define BLINKEDLED_H

class BlinkedLED
{
	public:
		void Init();
		void BlinkRight();
		void BlinkLeft();
		void Blink();
	
		void InterruptHandler();
	
	private:
		void Delay(int d);
		bool direction;
};

#endif