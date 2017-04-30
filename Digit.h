#ifndef DIGIT_H
#define DIGIT_H
#ifdef __AVR__
#include <ArduinoSTL.h> //for cctype
#endif
#include <cctype>
typedef unsigned char byte;

class Digit	{
	private:
		byte digitState;
		char digit;
		static const byte* values;
	public:
		Digit();
		Digit(const char);
		bool value(char) const;
#ifdef __linux__
		void display() const;
#endif
};

#endif
