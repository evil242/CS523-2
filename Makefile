# Makefile for object GA Warrior
#RM = /bin/rm -f

TARGET = ga_war

all: $(TARGET)

plant.red: 
	echo ";redcode-94\n;name plant\n;assert CORESIZE == 8000\nspl.x  #  0,#  0\n;end" >plant.red

obj_war.o: obj_war.c++ obj_war.h ThunderdomeConfig.h
	g++ -std=c++11 -c obj_war.c++

ga_war: plant.red obj_war.o ThunderdomeMain.c++
	g++ -std=c++11 -o ga_war ThunderdomeMain.c++ obj_war.o


clean:
	$(RM) $(TARGET) *.o *.red temp.txt

