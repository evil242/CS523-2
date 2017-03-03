# CS523-2
CS523 Project 2 Genetic Algorithms 

Adding example of 2000 ga_war.c 
by jason boer 3/20/97
jason@ezmo.com
http://corewar.co.uk/boer/ga_war.c


compiles and runs on UNM CS ubuntu systems

compile via make 

ga_war creates a single warrior and cycles through validation until
 it runs against plant.red


The primise of the warrior class is that it creates a warrior with 
initial random lines of code (need to add seed to random other wise same code).

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

Important Public Functions

    Warrior(string, int) // initial construction creates config warrior like new
    
    Warrior() //currently unused but thought for new copy


    Operator=(const Warrior reference) Warrior takes a reference to another
       warrior and enables access to internal parts such as body for copy

    Operator+(const Warrior reference) Warrior takes a reference to another
       warrior and enables access to internal parts such as body 
       Can start of cross over of code between two warriors.


     Mutation () undefined so far, but could be used for mutating lines of code
        in body.

     fprint() // no variable, print out to fname all current redcode

     print() // prints to std out full warrior

     test_viable() //Take current redcode and compare to simple warrior 
                   // in plant.red  
		   // uses system call ./pmars -b -o plant.red fname > temp.txt
		   // reads result of pmars fight from temp.txt

   
   to create a single warrior
       Warrior myfirstwarrior("xx",0);



to run
  $ ./ga_war
