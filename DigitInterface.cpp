#include "DigitInterface.h"

bool DigitInterface::isInRange(char ch) {
			return (ch >= '0' && ch <= '9') || (ch >='A' && ch <='F') || (ch >='a' && ch <='f') ;
}

string DigitInterface::table = "3e3d3c4e4d4g4cLO3f3g3a3b4f4a4bxx2c2g2d2e1c1d1eb92b2a2f1b1a1g1fb8b7b6b5b4b3b2b1b0";

DigitInterface::DigitInterface(int PCLK,int PSTB,int PDAT) {
	this->PCLK = PCLK;
	this->PSTB = PSTB;
	this->PDAT = PDAT;
	for(int i=0 ; i<4 ; i++)
		digits[i] = Digit('F');
#ifdef __linux__
	wiringPiSetup () ;
#endif
  	pinMode (this->PCLK, OUTPUT) ;
  	pinMode (this->PSTB, OUTPUT) ;
 	pinMode (this->PDAT, OUTPUT) ;
	clear();
	barFilled = 0;
	redLed = false;
}

void DigitInterface::setDigits(const string& str) {
	//digits is 4 byte string containing Hex Chars to be displayed on Screen
#ifdef __linux__
	assert(str.length() == 4);
#endif
	for(int i=0 ; i<4 ; i++) {
		if(isInRange(str[i]))
			digits[i] = Digit(str[i]);
		else
			digits[i] = Digit('F');
	}
}

void DigitInterface::setBars(int barFilled) {
	this->barFilled = barFilled;
}

void DigitInterface::setLed(bool redLed) {
	this->redLed = redLed;
}

#ifdef __linux__
void DigitInterface::display() {
	cout << "Digit Interface " << endl;
	cout << setw(4) << "Shift Register Clock (PCLK) :" << PCLK << endl;
	cout << setw(4) << "Data Register Clock (PSTB) :" << PSTB << endl;
	cout << setw(4) << "Serial Data (PDAT) :" << PDAT << endl;
	cout << "Digit Info " << endl;
	for(int i = 0 ; i<4 ; i++)
		digits[i].display();
}
#endif

void DigitInterface::write(bitset<40>& b) {
	//Sends data serially through PDAT
	//Starts from LSB to MSB
	for(int i = 0 ; i<40 ; i++) {
		digitalWrite(PDAT, b[i]);
		digitalWrite(PCLK, HIGH);
		digitalWrite(PCLK,LOW);
	}
	digitalWrite(PSTB,HIGH);
	digitalWrite(PSTB,LOW);
}

bitset<40> DigitInterface::getBits () {
	string table = DigitInterface::table;
	bitset<40> data;
	int current = 0;
	int bars = 0;
	for(int i = 0; i<40 ; i++) {
		string enquire = table.substr(current,2);
		if(isdigit(enquire[0])) //Means a Display
			data[i] = digits[enquire[0]-'0'-1].value(enquire[1]);
		else if(enquire[0] =='b' && bars++ < barFilled)
			data[i] = 0;
		else if(enquire == "LO")
			data[i] = !redLed;
		else
			data[i] = 1; // XX , not set
			current += 2;
	}
	return data;
}

void DigitInterface::write() {
	bitset<40> data = getBits();
	//cout << data.to_string() << endl;
	write(data);
}

void DigitInterface::clear() {
	bitset<40> data;
	data.set();
	write(data);
}

DigitInterface::~DigitInterface() {
	clear();
}
