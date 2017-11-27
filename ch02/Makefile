#
# Makefile for Chapter 02
#
# Type  make    to compile all the programs
# in the chapter 
#

all: cp1 who1 who2 who3

clean:
	rm -f cp1 who1 who2 who3

cp1: cp1.c 
	cc -o cp1 cp1.c 

who1: who1.c 
	cc -o who1 who1.c 

who2: who2.c 
	cc -o who2 who2.c 

who3: who3.c utmplib.c
	cc -o who3 who3.c utmplib.c

