#include "Person.hpp"
#include <fstream>
//#include <filesystem>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class PersonManager {
	
	public:		
		
				PersonManager		();					
				~PersonManager		();
				
		void	addPerson			(char *, char *, char *);		
		void	delPerson			(char *);
		
		void	loadPerson			();
		void	savePerson			();
			
		Person*	checkPerson			(char * );			
		
		void 	swapPerson			(int, int);
		void 	findPerson			(char *);
			
		Person* getHead				() 			{return head;}
		
	private:		
				
		Person* head;
		Person* tail;
		
};
