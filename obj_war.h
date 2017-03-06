#include "ThunderdomeConfig.h"


class Warrior {  // individual 

  public:
     // generate new lines of code;
     Warrior(string n, int sn);
     // constructor used for new copy
     Warrior();
     //constructor used for crossover or mutation
     Warrior(long gen, string n, int sn);
     //start cross over operations
     
     //direct assignment 
     Warrior& operator=(const Warrior&);
     //cross over
     Warrior& operator+(const Warrior&);

     //Say My Name
     const char *SMNB() { return fname.c_str();};

     //increase Rank
     void scores(int w) { rank += w; };

     void Mutation();

     void fprint(FILE * file);
     void fprint();
     void print();
     int test_viable();
     vector<string> body;
     long generation;
     int serno;
     string fname;
     int rank;
  private:
        static char new_line[256];
        string new_line_of_code(void);

  	string header;
	//string fname;
	//int rank;
	//int serno;
	//vector<string> body;
	//string body[20];
        int loc;
	string tail;

};
