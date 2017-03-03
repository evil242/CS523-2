/*** File ga_war.h ***/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::cout;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::to_string;
using namespace std;

/********************/

static unsigned long number_of_opcodes=17;

static string opcodes[]={\
                "dat","mov","add","sub",\
                "mul","div","mod","jmp",\
                "jmz","jmn","djn","spl",\
                "slt","cmp","seq","sne",\
                "nop"};

static unsigned long number_of_modifiers=7;

static string modifiers[]=
                {".a ",".b ",".ab",".ba",".f ",".x ",".i "};

static unsigned long number_of_address_modes=7;

static string address_modes[]=
                {"#","$","@","<",">","*","{","}"};


/************************************/
/*these are set from the config file*/

static char path_symbol[32]="";

static int create_new_population=1;
static char population_name[32]="";
static int population_size=5;

static int starting_cycle=0;
static int number_of_cycles=250;

static int number_of_battles=3;

static int mutation_rate=25;
static int resurrection_rate=2;
static int insertion_rate=5;
static int removal_rate=5;

static int max_number_size=10;
static int max_instructions=10;

/********************/




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

     Mutation();

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
