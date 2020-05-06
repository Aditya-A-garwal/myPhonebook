#include "Person.hpp"

using namespace std;

Person::Person() {
	nextPerson = NULL;
	prevPerson = NULL;
	
	vName = "";
	vNumber = "";
}

Person::~Person(){
	
}

void Person::setNum(char * aNum) {
	vNumber.clear();
	vNumber.append(aNum);
}		

void Person::setBirthday(char * date) {
	char d[3];
	char m[3];
	char y[5];
		
	d[0] = date[0];				
	d[1] = date[1];

	m[0] = date[3];				
	m[1] = date[4];
	
	y[0] = date[6];
	y[1] = date[7];
	y[2] = date[8];
	y[3] = date[9];		
		
	vBirthday.day = atoi(d);
	vBirthday.month = atoi(m);
	vBirthday.year = atoi(y);
}

bool Person::checkNum (char * aNum) {
	if(strlen(aNum) != 10) return 1;
	for(int i = 0; i < 10; i++) {
		if (!(aNum[i] >= '0' && aNum[i] <= '9')) return 1;
	}
	return 0;
}

bool Person::checkDate (char * aDate) {
	if(strlen(aDate) != 10) return 1;
	for(int i = 0; i < 10; i++) {
		if(i == 2 || i == 5) i++;
		if (!(aDate[i] >= '0' && aDate[i] <= '9')) return 1;
	}
	return 0;
}

