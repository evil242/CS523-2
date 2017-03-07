#include "ThunderdomeConfig.h"


class Warrior {  // individual 

  public:
     // generate new lines of code;
     Warrior(string n, int sn);
     // constructor used for new copy
     Warrior();
     //constructor used for crossover or mutation
     Warrior(long gen, string n, int sn);
     //constructor for mutation
     void Mutation();
     //start cross over operations
     
     //direct assignment 
     Warrior& operator=(const Warrior&);
     //cross over uniform
     Warrior& operator+(const Warrior&);
     //1-point crossover
     Warrior& operator*(const Warrior&);

     //Say My Name
     const char *SMNB() { return fname.c_str();};


     //increase Rank
     void scores(int w) { TribeRank += w; };
     void reset_scores() { TribeRank = 0; };
     //Say My Rank
     int SMR() { return TribeRank;};

     void fprint(FILE * file);
     void fprint();
     void print();
     int test_viable();

     // run a benchmark
     void PutMeInCoach();
     //Say My BenchMarkFitness
     int SMBMF() { return BenchmarkFit; };
     int ResetBMF() { BenchmarkFit=0; };

     int TwoFit() { return BenchmarkFit+TribeRank; };

  private:
        static char new_line[256];
        string new_line_of_code(void);

        long generation;
  	string header;
	string fname;
        int BenchmarkFit;
	int TribeRank;
	int serno;
	vector<string> body;
	//string body[20];
        int loc;
	string tail;

};
