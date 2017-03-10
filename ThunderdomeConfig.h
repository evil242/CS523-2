/*** File ThunderdomeConfig.h ***/
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

#define NOCROSS 0
#define ONEPTCROSS 1
#define UNIFORMCROSS 2

#define ROULETTE 0
#define TOURNAMENT 1
#define RANDOMSEL 2

static unsigned long NumOWilkies=12;

static string WilkiesBenchDir="WilkiesBench";

static string WilkiesBench[]={\
		"BLUEFUNK.RED", "FSTORM.RED", "MARCIA13.RED",\
		"PAPERONE.RED", "RAVE.RED","TIME.RED",\
		"CANNON.RED","IRONGATE.RED","NOBODY.RED",\
		"PSWING.RED","THERMITE.RED","TORNADO.RED"};

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

extern char path_symbol[32];

extern int create_new_population;
extern char population_name[32];
extern int population_size;

extern int starting_cycle;
extern int number_of_cycles;
extern int seed_cycles;

extern int number_of_battles;

extern int mutation_rate;

extern float TSprob;

extern float annealing_rate;
extern int insertion_rate;
extern int removal_rate;

extern int max_number_size;
extern int max_instructions;

extern int CrossType;
extern int SelecType;

/********************/
int a_random_integer(int);

int a_random_number(int);

void setup();

