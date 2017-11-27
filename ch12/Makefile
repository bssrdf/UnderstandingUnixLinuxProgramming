#
# Makefile for Chapter 12
#
# Type  make    to compile all the programs
# in the chapter 
#
all: webserv

clean:
	rm -f webserv


webserv: webserv.c socklib.c
	cc -o webserv webserv.c socklib.c

