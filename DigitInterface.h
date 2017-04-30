#ifndef DIGITALINTERFACE_H
#define DIGITALINTERFACE_H
#include "Digit.h"

#ifdef __linux__
#include <wiringPi.h>
#include <cassert> //Assert on Arduino makes no sense
#endif
#ifdef __AVR__
#include <Arduino.h>
#include <ArduinoSTL.h>
#endif
//C++ STL Libraries 
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <bitset>

using namespace std;
class DigitInterface	{
	private:
		//PCLK is Shift Register Clock
		//PSTB is Data Register Clock
		//PDAT is Serial Data
		int PCLK,PSTB,PDAT;
		static bool isInRange(char);
		Digit digits[4];
		int barFilled;
		bool redLed;
	public:
		static string table;
		DigitInterface(const int PCLK,const int PSTB,const int PDAT);
		void setDigits(const string& str);
		void setBars(int barFilled);
		void setLed(bool redLed);
#ifdef __linux__
		void display();
#endif
		void write(bitset<40>& b);
		bitset<40> getBits ();
		void write();
		void clear();
		~DigitInterface();
};
#endif
