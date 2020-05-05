#include <iostream>
#include <string>
#include "PersonManager.hpp"

using namespace std;

int main(int argc, char* argv[]) {		
	
	for(int i = 1; i < argc; i++) 
		cout << argv[i] << endl;					
	
	int 			decision;
	char*			nameBuff;
	char*			numberBuff;
	char*			birthdayBuff;
	Person* 		p; 
	PersonManager 	pmgr;
	
	// inits
	decision = -1;
	nameBuff = new char[101];
	numberBuff = new char[11];
	birthdayBuff = new char[11];
	
	cout << "loading persons" << endl;
	pmgr.loadPerson();		
	cout << "Elapsed time in milliseconds: " << endl;
	
	// main loop
	while(decision != 5) {
		
		strcpy(nameBuff, "");
		strcpy(numberBuff, "");
		strcpy(birthdayBuff, "");																				
		
		cout << "\n\n1 to list contacts\n" << "2 to add contact\n" << "3 to delete contact\n" << "4 to find by name\n" << "5 to end program\n\n" << "What would you like to do: ";
		cin >> decision;		
		cin.ignore(1, '\n');
		
		switch(decision) {				
		
		case 1: 
			
			cout << "Listing Contacts" << endl;
			
			p = pmgr.getHead();	
			while(p != NULL) {
				cout << "Name: " << p->getName() << " Number: " << p->getNum() << " Birthday: " << p->getDay() << "/" << p->getMonth() << "/" << p->getYear() << endl;		
				p = pmgr.nextPerson(p);
			}
			break;
			
		case 2: 
			
			rename:
			cout << "Enter name: " << endl;							
			cin.getline(nameBuff, 101, '\n');				
			
			if(pmgr.checkPerson(nameBuff)) {
				cout << "\n" << "name taken" << "\n" << endl;
				goto rename;								
			}
	
			cout << "Enter number: " << endl;									
			cin.getline(numberBuff, 11, '\n');				
			
			redate:
			
			cout << "Enter Birthday dd/mm/yyyy: " << endl;						
			cin.ignore(0, '\n');			
			cin.getline(birthdayBuff, 11, '\n');	
			for(int i = 0; i < 10; i++) {
				if(birthdayBuff[i] == NULL) {
					cout << "\n" << "invalid date format" << "\n" << endl;
					goto redate;
				}
			}				
			
			pmgr.addPerson(nameBuff, numberBuff, birthdayBuff);			
			break;
		
		case 3: 
						
			cout << "Enter name of contact to be removed: " << endl;					
									
			cin.getline(nameBuff, 101, '\n');
			
			pmgr.delPerson(nameBuff);
			
			break;
			
		case 4: 
		
			cout << "Enter name: " << endl;							
			cin.getline(nameBuff, 101, '\n');	

			pmgr.findPerson(nameBuff);					
			break;
			
		case 5: 				
		
			cout << "Bye." << endl;
			pmgr.savePerson();
			//break;	
			
		}			
	}	
	
	delete [] nameBuff;
	delete [] numberBuff;
	delete [] birthdayBuff;
}