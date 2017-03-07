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

static int CrossType=0; //NOCROSS

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

static char path_symbol[32]="";

static int create_new_population=1;
static char population_name[32]="";
static int population_size=20;

static int starting_cycle=0;
static int number_of_cycles=100;

static int number_of_battles=3;

static int mutation_rate=25;
static int resurrection_rate=2;
static int insertion_rate=5;
static int removal_rate=5;

static int max_number_size=10;
static int max_instructions=10;

/********************/
int a_random_integer(int);

int a_random_number(int);

