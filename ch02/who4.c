/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 40-2 */

/* dump_utmpx.c

   Display the contents of the utmp-style file named on the command line.

   This version of the program differs from that which appears in the book in
   that it prints extra information from each utmpx record.

   This program is Linux-specific.
*/
#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmpx.h>
#include <paths.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	SHOWHOST	/* include remote machine on output */
void showtime( long timeval );

int
main(int argc, char *argv[])
{
    struct utmpx *ut;
    struct in_addr in;

    setutxent();


    while ((ut = getutxent()) != NULL) {        /* Sequential scan to EOF */
        if ( ut->ut_type != USER_PROCESS )
                continue;;
        printf("%-8s ", ut->ut_user);
        printf("%5ld %-7.7s %-4.4s host %-16.16s", (long) ut->ut_pid,
                ut->ut_line, ut->ut_id, ut->ut_host);


        time_t tv_sec = ut->ut_tv.tv_sec;
        //printf("%s", ctime((time_t *) &tv_sec));
		showtime(tv_sec);
        printf("\n");
    }

    endutxent();
    exit(0);
}
void showtime( long timeval )
/*
 *      displays time in a format fit for human consumption
 *      uses ctime to build a string then picks parts out of it
 *      Note: %12.12s prints a string 12 chars wide and LIMITS
 *      it to 12chars.
 */
{
        char    *cp;                    /* to hold address of time      */

        cp = ctime(&timeval);           /* convert time to string       */
                                        /* string looks like            */
                                        /* Mon Feb  4 00:46:40 EST 1991 */
                                        /* 0123456789012345.            */
        printf("%12.12s", cp+4 );       /* pick 12 chars from pos 4     */
}
