#include "Digit.h"

#ifdef __linux__
#include <iostream>
#include <iomanip>
using namespace std;
#endif


//Encoded in abcd-efgh format
//Negative logic , Common Anode

static const unsigned char digitData[]  =  {0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09,0x11,0xc1,0x63,0x85,0x61,0x71};
const byte* Digit::values = digitData;

Digit::Digit()  {
	this->digit = 'F';
	digitState = values['F'-'A'+10];
}

Digit::Digit(const char digit)	{
	this->digit = digit;
	if (isdigit(digit))
		digitState = values[digit-'0'];
	else
		digitState = values[toupper(digit)-'A'+10];
}

bool Digit::value(char segment) const	{
	int noOfShift = 7 - (segment - 'a');
	return ( digitState >> noOfShift ) & 0x01;
}

#ifdef __linux__
void Digit::display() const {
	cout << "Current Digit" << setw(4) << digit << endl;
	cout << "Segment" << setw(4) << "|" << setw(4) << "Value" << setw(4) << endl;
	for(char ch = 'a' ; ch<='h' ; ch++)
		cout<< ch << setw(4) << "|" << setw(4) << value(ch) << setw(4) << endl;
}
#endif

