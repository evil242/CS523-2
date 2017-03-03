#include "ThunderdomeConfig.h"


class Warrior {  // individual 

  public:
     // generate new lines of code;
     Warrior(string n, int sn);
     // constructor used for new copy
     Warrior();
     //start cross over operations
     //direct assignment 
     Warrior& operator=(const Warrior&);
     //cross over
     Warrior& operator+(const Warrior&);

     void Mutation();

     void fprint(FILE * file);
     void fprint();
     void print();
     int test_viable();



  private:
        static char new_line[256];
        string new_line_of_code(void);

  	string header;
	string fname;
	int rank;
	int serno;
	vector<string> body;
	//string body[20];
        int loc;
	string tail;

};
