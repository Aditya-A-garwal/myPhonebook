#include <iostream>
#include <windows.h>

using namespace std;

//#define PB_DEBUG	1

#ifdef PB_DEBUG
		#define DBG_MSG(x)	x
#else 
		#define DBG_MSG(x) 
#endif	

struct Birthday {
	long day:8;
	long month:8;
	long year:16;			
};

class Person {			
		
	public:		
		
				Person		();					
				~Person		();
		
		string 	getName		()						{return vName;}		
		void 	setName		(char * aName) 			{vName.append(aName);}
		
		string 	getNum		()						{return vNumber;}		
		void 	setNum		(char *);		
				
		void setBirthday	(char *);		

		long	getDay		() 						{return vBirthday.day;}
		long	getMonth	() 						{return vBirthday.month;}
		long	getYear		() 						{return vBirthday.year;}
		
		Person* getNext		()						{return nextPerson;}
		Person* getPrev		()						{return prevPerson;}					

		void setNext		(Person * pNextPerson)	{nextPerson = pNextPerson;}
		void setPrev		(Person * pPrevPerson)	{prevPerson = pPrevPerson;}	
		
		bool checkNum		(char *);
		bool checkDate		(char *);
		
	private:	
	
		Person* nextPerson;		
		Person* prevPerson;	
				
		string 	vName;		
		string 	vNumber;	
		
		struct Birthday vBirthday;
};