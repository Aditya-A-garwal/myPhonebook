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
		Person* q = p->getNext();				
		delete p;	
		p = q;			
	}
}

void PersonManager::addPerson (char * pName, char * pNumber, char * pBirthday) {
	
	// inits
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
		next = next->getNext();
	}
		
	// case: no person in list is greater than input, we have to add at end
	if( next == NULL ) {
		
		// debug
		DBG_MSG(cout << "add person at end" << endl);
		
		// attach the person as the new tail
		tail->setNext(p);
		p->setPrev(tail);
		tail = p;
	}		
	
	// case: person found before which we can insert
	else {
		
		// debug
		DBG_MSG(cout << "add person before " << next->getName() << endl);
		
		// get the previous person to attach to 
		prev = next->getPrev();
		
		// case: we are to become the head to an existing list
		if( prev == NULL) {
			
			// attach the person as the new head
			next->setPrev(p);
			p->setNext(next);
			head = p;
	
		}
		
		else {
		
			// make the linkage to the previous person
			prev->setNext(p);
			p->setPrev(prev);
		
			// make the linkage to the next person	
			next->setPrev(p);
			p->setNext(next);
		}
		
	}
			
}

void PersonManager::delPerson(char* name) {
	
	//inits
	Person* p;
	Person* prev;
	Person* next;
	
	//prepare for navigating the list
	p = head;	
	
	//create string from char* for comparison
	string str(name);
	
	while(p != NULL) {		
		if(str.compare(p->getName()) == 0) break; // if found then break the loop
		p = p->getNext();
	}
	
	if(p == NULL) return; // if not found then return from function		
			
	// get next and previous for de-linking
	prev = p->getPrev();
	next = p->getNext();				
				
	if(p == head)
		head = next;		
	
	else if(p != head) 
		prev->setNext(next);
	
	if(p == tail)	
		tail = prev; 
	
	else if(p != tail) 
		next->setPrev(prev);	
		
	delete p;		
}

void PersonManager::loadPerson() {	

	//intis
	int		which;
	char*	number;
	char*	date;	

	string	name;	
	
	ifstream f;		
	
	Person temp;
	
	//declarations
	number = new char[11];
	date = new char[11]; 	
	
	f.open ("phoneInfo.txt", ifstream::binary);		
	f.seekg(0, f.end);
	cout << "Length of file is: " << f.tellg() << endl;
	f.close();
	
	f.open ("phoneInfo.txt", ifstream::in);		
		
	if (!(f.is_open())) return;	
	
	while(f.eof() == 0) {		
		string line;			

		getline(f, line);				
		stringstream st(line);			
		
		name = "";
		strcpy(number, "");	
		strcpy(date, "");
	
		which = 1;
		
		while(st.eof() == 0) {		
			string str;
			st >> str;
		
			if(str.compare(",") == 0 && name.compare("") != 0) which++;							
			else {
				if(which == 1) name.append(" ").append(str);
				else if(which == 2) strcpy(number, str.c_str());	
				else if(which == 3) strcpy(date, str.c_str());				
			}							
		}
		
		if(which != 1) {
			if(temp.checkNum(number) == 0 && temp.checkDate(date) == 0) 
				addPerson((char *)(name.substr(1).c_str()), number, date);											
			else 
				cout << "found corrupted contact with name " << name << endl;
		}
	}
	f.close();	
	
	delete number;
	delete date;
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
		
		currPerson = currPerson->getNext();
		
		DBG_MSG(cout << "waiting 2500" << endl);
		DBG_MSG(Sleep(2500));		
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
					break;
				}
			}
		}					
		p=p->getNext();
	}

	
}

Person* PersonManager::checkPerson(char* check) {
		
	Person* p;
	
	string str(check);
	
	p = head; 
						
	while(p != NULL) {		
		if(str.compare(p->getName()) == 0) return p;	
		p = p->getNext();		
	}	
	return NULL;
}

void PersonManager::swapPerson(int pos1, int pos2) {
	Person* b = head;
	Person* y = head;
	Person* pBuff = NULL;		
	
	if(pos1 != -1) {
		for(int i = 0; i < pos1; i++) b=b->getNext();
	} 
	else { b = tail; }
	
	if(pos2 != -1) {
		for(int i = 0; i < pos2; i++) y=y->getNext();					
	}
	else { y = tail; }
	
			
	Person* a = b->getPrev();
	Person* c = b->getNext();
	
	Person* x = y->getPrev();
	Person* z = y->getNext();				
	
	if(a != NULL) a->setNext(y); else head = y;
	if(c != NULL) c->setPrev(y); else tail = y;	
	
	if(x != NULL) x->setNext(b); else head = b;
	if(z != NULL) z->setPrev(b); else tail = b;		
	
	pBuff = b->getPrev();	
	b->setPrev(y->getPrev());
	y->setPrev(pBuff);
	
	pBuff = b->getNext();
	b->setNext(y->getNext());
	y->setNext(pBuff);
		
}

