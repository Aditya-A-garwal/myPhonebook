#include "Person.hpp"

using namespace std;

Person::Person() {
	nextPerson = NULL;
	prevPerson = NULL;
}

Person::~Person(){
	
}

string Person::getName() {
	return vName;
}
	
void Person::setName(char * aName) {
	vName.erase(0, vName.length()-1);
	vName.append(aName);
}
	
string Person::getNum() {
	return vNumber;
}
		
void Person::setNum(char * aNum) {
	vNumber.erase(0, vNumber.length()-1);
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

void Person::setPerson(Person* aP) {
	//p = aP;
}

Person* Person::getPerson() {
	return this;
}