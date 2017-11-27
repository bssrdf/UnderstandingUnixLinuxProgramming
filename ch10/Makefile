#
# Makefile for Chapter 10
#
# Type  make    to compile all the programs
# in the chapter 
#
all: listargs pipe pipedemo pipedemo2 stdinredir1 stdinredir2 whotofile

clean:
	rm -f listargs pipe pipedemo pipedemo2 stdinredir1 stdinredir2 whotofile


listargs: listargs.c
	cc -o listargs listargs.c

pipe: pipe.c
	cc -o pipe pipe.c

pipedemo2: pipedemo2.c
	cc -o pipedemo2 pipedemo2.c

pipedemo: pipedemo.c
	cc -o pipedemo pipedemo.c

stdinredir1: stdinredir1.c
	cc -o stdinredir1 stdinredir1.c

stdinredir2: stdinredir2.c
	cc -o stdinredir2 stdinredir2.c

whotofile: whotofile.c
	cc -o whotofile whotofile.c

