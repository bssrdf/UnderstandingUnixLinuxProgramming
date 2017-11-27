#
# Makefile for Chapter 09
#
# Type  make    to compile all the programs
# in the chapter 
#
all: changeenv showenv smsh1 smsh2 smsh3 smsh4

clean:
	rm -f changeenv showenv smsh1 smsh2 smsh3 smsh4


changeenv: changeenv.c
	cc -o changeenv changeenv.c

showenv: showenv.c
	cc -o showenv showenv.c

smsh1: smsh1.c splitline.c execute.c
	cc -o smsh1 smsh1.c splitline.c execute.c

smsh2: smsh2.c splitline.c execute.c process.c controlflow.c 
	cc -o smsh2 smsh2.c splitline.c execute.c process.c controlflow.c 

smsh3: smsh2.c splitline.c execute.c process2.c controlflow.c \
		builtin.c varlib.c 
	cc -o smsh3 smsh2.c splitline.c execute.c process2.c controlflow.c \
		builtin.c varlib.c 

smsh4: smsh4.c splitline.c execute2.c process2.c controlflow.c \
		builtin.c varlib.c 
	cc -o smsh4 smsh4.c splitline.c execute2.c process2.c controlflow.c \
		builtin.c varlib.c 

