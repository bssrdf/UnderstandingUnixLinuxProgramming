#
# Makefile for Chapter 14
#
# Type  make    to compile all the programs
# in the chapter 
#
all: hello_multi hello_single incprint tanimate tbounce1d 	\
	twc1 twc2 twc3 twc4 twebserv

clean:
	rm -f hello_multi hello_single incprint tanimate tbounce1d 	\
		twc1 twc2 twc3 twc4 twebserv


hello_multi: hello_multi.c -lpthread
	cc -o hello_multi hello_multi.c -lpthread

hello_single: hello_single.c
	cc -o hello_single hello_single.c

incprint: incprint.c -lpthread
	cc -o incprint incprint.c -lpthread

tanimate: tanimate.c -lcurses -lpthread 
	cc -o tanimate tanimate.c -lcurses -lpthread 

tbounce1d: tbounce1d.c -lcurses -lpthread 
	cc -o tbounce1d tbounce1d.c -lcurses -lpthread 

twc1: twordcount1.c -lpthread
	cc -o twc1 twordcount1.c -lpthread

twc2: twordcount2.c -lpthread
	cc -o twc2 twordcount2.c -lpthread

twc3: twordcount3.c -lpthread
	cc -o twc3 twordcount3.c -lpthread

twc4: twordcount4.c -lpthread
	cc -o twc4 twordcount4.c -lpthread

twebserv: twebserv.c socklib.c -lpthread 
	cc -o twebserv twebserv.c socklib.c -lpthread 

