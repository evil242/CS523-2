# CS523-2
CS523 Project 2 Genetic Algorithms 

Adding example of 2000 ga_war.c 
by jason boer 3/20/97
jason@ezmo.com
http://corewar.co.uk/boer/ga_war.c


compiles and runs on UNM CS ubuntu systems
Requires pmars be in the current directory 
  (will attempt to create link if pmars available in PATH)

compile via make 

make creates the following files

pmars: (link)

plant.red:  (simple corewar to test viability)
;redcode-94
;name plant
;assert CORESIZE == 8000
spl.x  #  0,#  0
;end


Obj_Warrior.cfg 
;the form of this must not be changed
;the parser is very-very-very dumb
;
; value can be {0,1,2}
; for NONE, ONEPOINT, or UNIFORM CROSSOVER
CrossType=1
; value can be {0,1,2}
; for ROULETTE, TOURNAMENT, or RANDOM SELECTION
SelecType=1
; value can be {0,1}
create_new_population=1
; value must be {n>1} or else
population_size=25
; value must be {n>1} or else
number_of_cycles=5
; value must be {n>1} but keep small
seed_cycles=10
; value must be {n>=0}
starting_cycle=0
; value must be {0<n<100}
max_instructions=30
; value must be {n<=999} 
max_number_size=10
; values should be {0...100}
mutation_rate=5
insertion_rate=5
removal_rate=5
annealing_rate=1.0025
;value must be {n>0}
number_of_battles=25
; 2 letters only...dumb
population_name=DD
; OK, dos use \ unix use //
path_symbol=/

$(OBJECTS) = ThunderdomeConfig.o obj_war.o Sorting.o

ga_war Executable

After configuring parameters in Obj_Warrior.cfg
Run Example:
  ./ga_war > Outfile &

TO STOP Simply touch the file HALT
  Example:
     touch HALT

ga_war will see HALT file, get to stopping point and write maximized warriors 
captured out to file as RagnarLothbrok_1.red and GrepSedAwk_2.red

ga_war will also write current tribe fitness to file GA_War_Sumfit.log

ga_war creates a single warrior and cycles through validation until
 it runs against plant.red

The primise of the warrior class is that it creates a warrior with 
initial random lines of code (need to add seed to random other wise same code).


Files:
  Sorting.c - Warrior Vector sorting functions
  Sorting.h - sorting functions external declerations

  ThunderdomeMain.c++ - Contains Main() function to kick everything off

  ThunderdomeConfig.h  - all the static and extern variables including sys 
                         specs, opt codes, opt mods, etc.
  ThunderdomeConfig.c  - setup() function reads Obj_Warrior.cfg and sets
                         extern declared variables

  obj_war.c++ - function code for Warrior class
  obj_war.h  - header file for the Warrior class definitions

  Makefile - creates .o and target ga_war exec, 
             creates plant.red if clenaed
             clean: rm's *.o ga_war *.red



Important Private variables:

    header - essentail information for start of .red file

    fname - file_name used to write out to, typic "CharChar_#.red"
            created at initial construction with short string n and serno

    body is a vector string rray of 10 lines of code 
    treat body as an array of strings (string array of char)
    (easy to incr vector w/ more lines of code using push_back(new_line_of_code)

    tail - essentail information for .red file

    loc - int used to track # lines of code

    rank - could track # of wins?

    serno - track creation order, "we are designation 6 of 9"
   
    BenchmarkFit // stores fitness measured from Wilkes Benchmark
  
    TribeRank // fitness measured from Tribe Battle Royal

Important Public Functions

    Warrior(string, int) // initial construction creates config warrior like new
    
    Warrior() //used for temp copy


    Operator=(const Warrior reference) Warrior takes a reference to another
       warrior and enables access to internal parts such as body for copy

    Operator+(const Warrior reference) Warrior takes a reference to another
       warrior and enables access to internal parts such as body 
       Can start of cross over of code between two warriors.

     Mutation () mutates lines of code in body.

     fprint() // no variable, print out to fname all current redcode

     print() // prints to std out full warrior

     test_viable() //Take current redcode and compare to simple warrior 
                   // in plant.red  
		   // uses system call ./pmars -b -o plant.red fname > temp.txt
		   // reads result of pmars fight from temp.txt

    reset_scores() // resets BenchmarkFit and TribeRank to 0

    TwoFit() // returns BenchmarkFit+TribeRank; 
   
   to create a single warrior
       Warrior myfirstwarrior("xx",0);


