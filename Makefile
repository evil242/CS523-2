# Makefile for object GA Warrior


obj_war.o: obj_war.c++ obj_war.h ThunderdomeConfig.h
	g++ -std=c++11 -c obj_war.c++

ga_war: obj_war.o WarriorMain.c++
	g++ -std=c++11 -o ga_war WarriorMain.c++ obj_war.o

