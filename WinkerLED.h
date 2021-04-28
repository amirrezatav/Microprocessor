#ifndef WINKERLED_H
#define WINKERLED_H
enum Direction 
{
	Right = 0, 
	Left = 1
};
class WinkerLED
{
	private : 
		void Delay(int d);
	
	public :
		WinkerLED(void);
		void Initial();
		void WinkRight();
		void WinkLeft();
		void IterruptHandler();
		Direction direction;
		void Wink();
};
#endif 