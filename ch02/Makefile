#
# Makefile for Chapter 02
#
# Type  make    to compile all the programs
# in the chapter 
#

all: cp1 who1 who2 who3 who4 wc1 wc3 wc4 wc5 wc2

clean:
	rm -f cp1 who1 who2 who3

cp1: cp1.c 
	cc -o cp1 cp1.c 

who1: who1.c 
	cc -o who1 who1.c 

dump_utmpx: dump_utmpx.c 
	cc -o dump_utmpx dump_utmpx.c 

who2: who2.c 
	cc -o who2 who2.c 

who3: who3.c utmplib.c
	cc -o who3 who3.c utmplib.c

who4: who4.c 
	cc -o who4 who4.c 

wc1: wc1.c 
	cc -O3 -o wc1 wc1.c 

wc2: wc2.c 
	cc -O3 -march=native -o wc2 wc2.c 

wc3: wc3.c 
	cc -O3 -o wc3 wc3.c 
wc4: wc4.c 
	cc -O3 -o wc4 wc4.c 
wc5: wc5.c 
	cc -O3 -march=native -o wc5 wc5.c 


