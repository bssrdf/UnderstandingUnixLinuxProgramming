#
# Makefile for Chapter 07
#
# Type  make    to compile all the programs
# in the chapter 
#
all: bounce1d bounce2d bounce_aio bounce_async hello1 	\
	hello2 hello3 hello4 hello5 sigactdemo sigdemo3 \
	sleep1 ticker_demo

clean:
	rm -f bounce1d bounce2d bounce_aio bounce_async hello1 	\
		hello2 hello3 hello4 hello5 sigactdemo sigdemo3 \
		sleep1 ticker_demo


bounce1d: bounce1d.c set_ticker.c -lcurses
	cc -o bounce1d bounce1d.c set_ticker.c -lcurses

bounce2d: bounce2d.c set_ticker.c -lcurses
	cc -o bounce2d bounce2d.c set_ticker.c -lcurses

bounce_aio: bounce_aio.c set_ticker.c -lrt  -lcurses
	cc -o bounce_aio bounce_aio.c set_ticker.c -lrt  -lcurses

bounce_async: bounce_async.c set_ticker.c -lcurses
	cc -o bounce_async bounce_async.c set_ticker.c -lcurses

hello1: hello1.c -lcurses
	cc -o hello1 hello1.c -lcurses

hello2: hello2.c -lcurses
	cc -o hello2 hello2.c -lcurses

hello3: hello3.c -lcurses
	cc -o hello3 hello3.c -lcurses

hello4: hello4.c -lcurses
	cc -o hello4 hello4.c -lcurses

hello5: hello5.c -lcurses
	cc -o hello5 hello5.c -lcurses

sigactdemo: sigactdemo.c
	cc -o sigactdemo sigactdemo.c

sigdemo3: sigdemo3.c
	cc -o sigdemo3 sigdemo3.c

sleep1: sleep1.c 
	cc -o sleep1 sleep1.c 

ticker_demo: ticker_demo.c 
	cc -o ticker_demo ticker_demo.c 

