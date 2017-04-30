#include <DigitInterface.h>
using namespace std;
DigitInterface d1(1,2,3);
string str = "0123456789ABCDEF";
void setup() {
	
}
void loop() {
	
	d1.clear();
	
	string orig = str;
	int bars = 1;
	string val;
	do {
		d1.setDigits(str.substr(0,4));
		d1.setBars(bars++ % 11);
		rotate(str.begin(),str.begin()+1,str.end());
		d1.write();
		delay(1000);
		
	} while( str!= orig);
	for(int i = 0 ; i <10 ; i++) {
		d1.setDigits("ABCD");
		d1.setBars(10);
		d1.write();
		delay(500);
		d1.clear();
		delay(500);
	}
}
