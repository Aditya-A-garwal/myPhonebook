#include <iostream>

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
		
		string 	getName		();		
		void 	setName		(char *);
		
		string 	getNum		();		
		void 	setNum		(char *);	
		
		//string getBirthday	();
		void setBirthday	(char *);
		
		void 	setPerson	(Person*);			
		Person* getPerson	();		

		void setDay			(short d) {vBirthday.day = d;}
		void setMonth		(short m) {vBirthday.month = m;}
		void setYear		(short y) {vBirthday.year = y;}

		long	getDay		() 			{return vBirthday.day;}
		long	getMonth	() 			{return vBirthday.month;}
		long	getYear		() 			{return vBirthday.year;}
	
		Person* nextPerson;		
		Person* prevPerson;					
		
	private:	
				
		string 	vName;		
		string 	vNumber;	
		
		struct Birthday vBirthday;
};