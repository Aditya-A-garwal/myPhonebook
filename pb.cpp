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
	Person*			modif;
	PersonManager 	pmgr;
	Person 			temp;
	
	// inits
	decision = -1;
	nameBuff = new char[101];
	numberBuff = new char[11];
	birthdayBuff = new char[11];
	
	cout << "\n\nPhonebook v2.0" << endl;
	
	cout << "Loading contacts" << endl;
	pmgr.loadPerson();				
	cout << "Contacts loaded" << endl;
	
	// main loop
	
	while(decision != 6) {
		
		strcpy(nameBuff, "");
		strcpy(numberBuff, "");
		strcpy(birthdayBuff, "");																				
		
		cout << "\n\n1 to list contacts\n2 to add contact\n3 to delete contact\n4 to find by name\n5 to modify contact\n6 to end program\n\nWhat would you like to do: ";		
		
		cin >> decision;		
		cin.ignore(1, '\n');
		cout << "\n" << endl;
		
		switch(decision) {				
		
		case 1: 					
			
			p = pmgr.getHead();	
			while(p != NULL) {
				cout << "Name: " << p->getName() << " Number: " << p->getNum() << " Birthday: " << p->getDay() << "/" << p->getMonth() << "/" << p->getYear() << endl;		
				p = p->getNext();
			}
			break;
			
		case 2: 					
			
			rename:
			
			cout << "Enter name: " << endl;							
			cin.getline(nameBuff, 101, '\n');				
			
			if(pmgr.checkPerson(nameBuff) != NULL) {
				cout << "\n" << "name taken" << "\n" << endl;
				goto rename;								
			}
	
			
			
			renumber:
	
			cout << "Enter number: " << endl;									
			cin.getline(numberBuff, 11, '\n');				
			
			if(temp.checkNum(numberBuff)) {
				cout << "\n" << "invalid number format" << "\n" << endl;
				goto renumber;
			}					
			
			
			
			redate:
			
			cout << "Enter Birthday dd/mm/yyyy: " << endl;						
			cin.ignore(0, '\n');			
			cin.getline(birthdayBuff, 11, '\n');	
			
			if(temp.checkDate(birthdayBuff)) {
				cout << "\n" << "invalid date format" << "\n" << endl;
				goto redate;
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
		
			cout << "Enter name of contact to modify: " << endl;
			cin.getline(nameBuff, 101, '\n');
			
			modif = pmgr.checkPerson(nameBuff);
			
			renumber2:
	
			cout << "Enter new number: " << endl;									
			cin.getline(numberBuff, 11, '\n');				
			
			if(temp.checkNum(numberBuff)) {
				cout << "\n" << "invalid number format" << "\n" << endl;
				goto renumber2;
			}					
			
			
			
			redate2:
			
			cout << "Enter new Birthday dd/mm/yyyy: " << endl;						
			cin.ignore(0, '\n');			
			cin.getline(birthdayBuff, 11, '\n');	
			
			if(temp.checkDate(birthdayBuff)) {
				cout << "\n" << "invalid date format" << "\n" << endl;
				goto redate2;
			}					
			
			modif->setNum(numberBuff);
			modif->setBirthday(birthdayBuff);
			
			break;
			
		case 6: 				
		
			cout << "Bye." << endl;
			cout << "Saving contacts" << endl;
			pmgr.savePerson();						
			cout << "Contacts saved" << endl;			
		}			
	}	
	
	delete [] nameBuff;
	delete [] numberBuff;
	delete [] birthdayBuff;
}