#include "PersonManager.hpp"
#include <fstream>

using namespace std;

PersonManager::PersonManager() {
	head = NULL;
	tail = NULL;			
}

PersonManager::~PersonManager() {
	Person* p = head;
	while(p != NULL) {
		Person* q = p->nextPerson;				
		delete p;	
		p = q;			
	}
}

void PersonManager::addPerson (char * pName, char * pNumber, char * pBirthday) {
	
	Person* p;
	Person* next;
	Person* prev;
	
	// populate the person object to be added
	p = new Person;
	p->setName (pName);
	p->setNum (pNumber);
	p->setBirthday (pBirthday);
	
	// case: first person in the list
	if( head == NULL ) {
		
		// debug
		DBG_MSG(cout << "add first person" << endl);
		
		// set the head and tail of the list
		head = p;
		tail = p;		
		
		// done
		return;		
	}	
		
	// prepare for navigating the list
	next = head;
	
	// loop to find the person before which the new person will get added
	while(next != NULL) {
		
		// case: comparison found the person greater than input person
		if(next->getName().compare(p->getName()) > 0) 
			break;
		
		// not yet, move to next person
		next = next->nextPerson;
	}
		
	// case: no person in list is greater than input, we have to add at end
	if( next == NULL ) {
		
		// debug
		DBG_MSG(cout << "add person at end" << endl);
		
		// attach the person as the new tail
		tail->nextPerson = p;
		p->prevPerson = tail;
		tail = p;
	}		
	
	// case: person found before which we can insert
	else {
		
		// debug
		DBG_MSG(cout << "add person before " << next->getName() << endl);
		
		// get the previous person to attach to 
		prev = next->prevPerson;
		
		// case: we are to become the head to an existing list
		if( prev == NULL) {
			
			// attach the person as the new head
			next->prevPerson = p;
			p->nextPerson = next;
			head = p;
	
		}
		
		else {
		
			// make the linkage to the previous person
			prev->nextPerson = p;
			p->prevPerson = prev;
		
			// make the linkage to the next person	
			next->prevPerson = p;
			p->nextPerson = next;
		}
		
	}
			
}

void PersonManager::delPerson(char* name) {
	
	Person* p;
	Person* prev;
	Person* next;
	
	p = head;	
	
	string str(name);
	
	while(p != NULL) {		
		if(str.compare(p->getName()) == 0) break;
		p = p->nextPerson;
	}
	
	if(p == NULL) 
		return;
			
	prev = p->prevPerson;
	next = p->nextPerson;				
				
	if(p == head)
		head = next;		
	
	else if(p != head) 
		prev->nextPerson = next;	
	
	if(p == tail)	
		tail = prev; 
	
	else if(p != tail) 
		next->prevPerson = prev; 	
		
	delete p;		
}

void PersonManager::loadPerson() {	

	ifstream f;
	f.open ("phoneInfo.txt");		
	
	string name;
	string number;
	string date;	
	
	int which;
	
	while(f.eof() == 0) {		
		string line;			

		getline(f, line);				
		stringstream st(line);			
		
		name = "";
		number = "";	
		date = "";
	
		which = 1;
		
		while(st.eof() == 0) {		
			string str;
			st >> str;
		
			if(str.compare(",") == 0) which++;							
			else {
				if(which == 1) name.append(" ").append(str);
				else if(which == 2) number = str;
				else if(which == 3) date = str;				
			}							
		}
		
		if(which != 1) addPerson((char *)((name.substr(1)).c_str()), (char *)(number.c_str()), (char *)(date.c_str()));											
	}
	f.close();	
}

void PersonManager::savePerson() {
	
	ofstream f;
	f.open ("phoneInfo.txt", ofstream::trunc);	
	
	Person* currPerson = head;
	while(currPerson != NULL) {
		
		string name = currPerson->getName();
		string number = currPerson->getNum();
		
		int day = currPerson->getDay();
		int month = currPerson->getMonth();
		int year = currPerson->getYear();
		
		f << name << " , " << number << " , ";		
		f << setfill('0') << setw(2) << day; 
		f << ","; 
		f << setfill('0') << setw(2) << month;
		f << ",";
		f << setfill('0') << setw(4) << year << endl;
		
		currPerson = currPerson->nextPerson;
	}		
	f.close();
}

void PersonManager::findPerson(char* pName) {
	
	string str1( pName );
	
	int len1;
	int len2;
	
	string str2;
	
	Person* p = head;
	len1 = str1.length();	
	
	while( p != NULL ) {
		
		str2 = p->getName();
		len2 = str2.length()-len1+1;
		
		for( int i = 0; i < len2; i++) {
			if(str1.at(0) == str2.at(i)) {
				if(str1.compare(str2.substr(i, len1)) == 0) {
					cout << "Name: " << p->getName() << " Number: " << p->getNum() << " Birthday: " << p->getDay() << "/" << p->getMonth() << "/" << p->getYear() << endl;		
				}
			}
		}					
		p=p->nextPerson;
	}

	
}

bool PersonManager::checkPerson(char* check) {
	
	string str(check);
	
	Person* p = head; 
						
	while(p != NULL) {		
		if(str.compare(p->getName()) == 0) return 1;	
		p = nextPerson(p);
	}	
	return 0;
}

void PersonManager::swapPerson(int pos1, int pos2) {
	Person* b = head;
	Person* y = head;
	Person* pBuff = NULL;		
	
	if(pos1 != -1) {
		for(int i = 0; i < pos1; i++) b=b->nextPerson;
	} 
	else { b = tail; }
	
	if(pos2 != -1) {
		for(int i = 0; i < pos2; i++) y=y->nextPerson;					
	}
	else { y = tail; }
	
			
	Person* a = b->prevPerson;
	Person* c = b->nextPerson;
	
	Person* x = y->prevPerson;
	Person* z = y->nextPerson;				
	
	if(a != NULL) a->nextPerson = y; else head = y;
	if(c != NULL) c->prevPerson = y; else tail = y;	
	
	if(x != NULL) x->nextPerson = b; else head = b;
	if(z != NULL) z->prevPerson = b; else tail = b;		
	
	pBuff = b->prevPerson;	
	b->prevPerson = y->prevPerson;
	y->prevPerson = pBuff;	
	
	pBuff = b->nextPerson;
	b->nextPerson = y->nextPerson;
	y->nextPerson = pBuff;
		
}

