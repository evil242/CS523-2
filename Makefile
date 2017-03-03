# Makefile for object GA Warrior

ga_war: obj_war.c++ obj_war.h
	g++ -std=c++11 -o ga_war obj_war.c++
