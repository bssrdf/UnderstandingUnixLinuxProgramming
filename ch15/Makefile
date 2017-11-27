#
# Makefile for Chapter 15
#
# Type  make    to compile all the programs
# in the chapter 
#
all: file_tc file_ts selectdemo shmclnt1 shmclnt2 shmserv1 shmserv2

clean:
	rm -f file_tc file_ts selectdemo shmclnt1 shmclnt2 shmserv1 shmserv2


file_tc: file_tc.c
	cc -o file_tc file_tc.c

file_ts: file_ts.c
	cc -o file_ts file_ts.c

selectdemo: selectdemo.c
	cc -o selectdemo selectdemo.c

shmclnt1: shm_tc.c
	cc -o shmclnt1 shm_tc.c

shmclnt2: shm_tc2.c
	cc -o shmclnt2 shm_tc2.c

shmserv1: shm_ts.c
	cc -o shmserv1 shm_ts.c

shmserv2: shm_ts2.c
	cc -o shmserv2 shm_ts2.c

