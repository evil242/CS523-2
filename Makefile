# Makefile for object GA Warrior
#RM = /bin/rm -f

TARGET = ga_war
CC = g++
CFLAGS = -std=c++11 #-fpermissive 

HEADERS = obj_war.h Sorting.h ThunderdomeConfig.h
CFILES = obj_war.c++ Sorting.c ThunderdomeMain.c++ ThunderdomeConfig.c
XTRAF = plant.red Obj_Warrior.cfg
OBJS = obj_war.o Sorting.o ThunderdomeConfig.o

all: $(TARGET)

pmars:
	ln -s `which pmars` ./pmars

plant.red: 
	echo ";redcode-94\n;name plant\n;assert CORESIZE == 8000\nspl.x  #  0,#  0\n;end" >plant.red

Obj_Warrior.cfg: 
	printf ";the form of this must not be changed\n;the parser is very-very-very dumb\n;\n; value can be {0,1,2}\n; for NONE, ONEPOINT, or UNIFORM CROSSOVER\nCrossType=1\n; value can be {0,1,2}\n; for ROULETTE, TOURNAMENT, or RANDOM SELECTION\nSelecType=0\n; value can be {0,1}\ncreate_new_population=1\n; value must be {n>1} or else\npopulation_size=25\n; value must be {n>1} or else\nnumber_of_cycles=25\n; value must be {n>1} but keep small\nseed_cycles=10\n; value must be {n>=0}\nstarting_cycle=0\n; value must be {0<n<100}\nmax_instructions=10\n; value must be {n<=999} \nmax_number_size=10\n; values should be {0...100}\nmutation_rate=15\ninsertion_rate=5\nremoval_rate=5\nresurrection_rate=2\n;value must be {n>0}\nnumber_of_battles=25\n; 2 letters only...dumb\npopulation_name=DD\n; OK, dos use \\ unix use //\npath_symbol=/" > Obj_Warrior.cfg

ThunderdomeConfig.o: ThunderdomeConfig.c $(HEADERS)
	$(CC) $(CFLAGS) -c ThunderdomeConfig.c

obj_war.o: obj_war.c++ $(HEADERS)
	$(CC) $(CFLAGS) -c obj_war.c++

Sorting.o: Sorting.c $(HEADERS)
	g++ $(CFLAGS) -c Sorting.c

ga_war: $(HEADERS) $(CFILES) $(OBJS) $(XTRAF)
	g++ $(CFLAGS) -o ga_war ThunderdomeMain.c++ $(OBJS)


clean:
	$(RM) $(TARGET) $(OBJS) $(XTRAF) *.red

