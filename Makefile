# Makefile for object GA Warrior
#RM = /bin/rm -f

TARGET = ga_war
CC = g++
CFLAGS = -fpermissive -std=c++11 

all: $(TARGET)

plant.red: 
	echo ";redcode-94\n;name plant\n;assert CORESIZE == 8000\nspl.x  #  0,#  0\n;end" >plant.red

ga_war.cfg: 
	printf ";the form of this must not be changed\n;the parser is very-very-very dumb\n;\n; value can be 0,1, or 2\n; for NONE,ONEPOINT, or UNIFORM CROSSOVER\nCrossType=1; value can be {0,1}\ncreate_new_population=1\n; value must be {n>1} or else\npopulation_size=25\n; value must be {n>1} or else\nnumber_of_cycles=250\n; value must be {n>=0}\nstarting_cycle=0\n; value must be {0<n<100}\nmax_instructions=10\n; value must be {n<=999} \nmax_number_size=10\n; values should be {0...100}\nmutation_rate=25\ninsertion_rate=5\nremoval_rate=5\nresurrection_rate=2\n;value must be {n>0}\nnumber_of_battles=3\n; 2 letters only...dumb\npopulation_name=xx\n; OK, dos use \\ unix use //\npath_symbol=//" > ga_war.cfg


obj_war.o: obj_war.c++ obj_war.h ThunderdomeConfig.h
	$(CC) $(CFLAGS) -c obj_war.c++

Sorting.o: Sorting.h Sorting.c obj_war.c++ obj_war.h ThunderdomeConfig.h
	g++ $(CFLAGS) -c Sorting.c

ga_war: plant.red obj_war.o ThunderdomeMain.c++ Sorting.o ga_war.cfg
	g++ $(CFLAGS) -o ga_war ThunderdomeMain.c++ obj_war.o Sorting.o


clean:
	$(RM) $(TARGET) *.o *.red temp.txt ga_war.cfg

