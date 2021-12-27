/*  more03.c  - version 0.2 of more
 *	read and print 24 lines then pause for a few special commands
 *      feature of version 0.2: reads from /dev/tty for commands
 *  improvement: no need to press Enter for the command to take effect
 */
#include	<stdio.h>
#include	<stdlib.h>
#include    <string.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    <sys/ioctl.h>
#include    <signal.h>
#include    <termios.h>

//#define	PAGELEN	24
#define	LINELEN	512
enum KEY_ACTION{
       
        ESC = 27           /* Escape */
       
};

void do_more(FILE *);
int ttySetRaw(int fd, struct termios *prevTermios);
void handleSigWinCh(int);
void updateWindowSize(void);

static struct termios userTermios;
static int screenrows;
static int screencols;
static int pagelen;

int main( int ac , char *av[] )
{
	FILE	*fp;

    setbuf(stdout, NULL);               /* Disable stdout buffering */
    signal(SIGWINCH, handleSigWinCh);
    updateWindowSize();
  

	if ( ac == 1 )
		do_more( stdin );
	else
		while ( --ac )
			if ( (fp = fopen( *++av , "r" )) != NULL )
			{
				do_more( fp ) ; 
				fclose( fp );
			}
			else
				exit(1);	

	return 0;
}

void do_more( FILE *fp )
/*
 *  read PAGELEN lines, then call see_more() for further instructions
 */
{
	char	line[LINELEN];
	int	num_of_lines = 0;
	int	reply;
	int	fp_tty;
	 

	fp_tty = open( "/dev/tty", O_RDONLY);	   /* NEW: cmd stream   */
	if ( fp_tty == -1 )			   /* if open fails     */
		exit(1);                           /* no use in running */
    if (ttySetRaw(fp_tty, &userTermios) == -1){
        fprintf(stderr, "error in setting termial to raw mode\n");
        exit(1);
    }
	while ( fgets( line, LINELEN, fp ) ){		/* more input	*/
		if ( num_of_lines == pagelen ) {	/* full screen?	*/
			char	c;
			int     n;
			printf("\033[7m more? \033[m");		/* reverse on a vt100	*/			
			for (;;){
				n = read(fp_tty, &c, 1);
				if (n <= 0){
					printf("error read in from terminal\n");		
					reply = 0;
					break;
				}
				if ( c == 'q' ){			/* q -> N		*/
					reply = 0;
					break;
				}
				if ( c == ' ' ){			/* ' ' => next page	*/
					reply = pagelen;		/* how many to show	*/
					break;
				}
				//if ( c == '\n' ){		/* Enter key => 1 line	*/
				if ( c == '\r' ){		/* Enter key => 1 line	*/
					reply = 1;	
					break;
				}	
			}
			if ( reply == 0 )		/*    n: done   */
				break;
			num_of_lines -= reply;		/* reset count	*/
		}
		if ( fputs( line, stdout )  == EOF )	/* show line	*/
			exit(1);			/* or die	*/
		num_of_lines++;				/* count it	*/
	}
	if (tcsetattr(fp_tty, TCSAFLUSH, &userTermios) == -1)
	     exit(1);  
}



int
ttySetRaw(int fd, struct termios *prevTermios)
{
    struct termios t;

    if (tcgetattr(fd, &t) == -1){
		fprintf(stderr, "can not get attr raw mode\n");
        return -1;
	}

    if (prevTermios != NULL)
        *prevTermios = t;

    t.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
                        /* Noncanonical mode, disable signals, extended
                           input processing, and echoing */

    t.c_iflag &= ~(BRKINT | ICRNL | IGNBRK | IGNCR | INLCR |
    //t.c_iflag &= ~(BRKINT | ICRNL | IGNBRK | INLCR |
                      INPCK | ISTRIP | IXON | PARMRK);
                        /* Disable special handling of CR, NL, and BREAK.
                           No 8th-bit stripping or parity error handling.
                           Disable START/STOP output flow control. */

    //t.c_oflag &= ~OPOST;                /* Disable all output processing */

    t.c_cc[VMIN] = 1;                   /* Character-at-a-time input */
    t.c_cc[VTIME] = 0;                  /* with blocking */

    if (tcsetattr(fd, TCSAFLUSH, &t) == -1)
        return -1;

    return 0;
}

void handleSigWinCh(int unused __attribute__((unused))) {
    updateWindowSize();
}

/* Use the ESC [6n escape sequence to query the horizontal cursor position
 * and return it. On error -1 is returned, on success the position of the
 * cursor is stored at *rows and *cols and 0 is returned. */
int getCursorPosition(int ifd, int ofd, int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;

    /* Report cursor location */
    if (write(ofd, "\x1b[6n", 4) != 4) return -1;

    /* Read the response: ESC [ rows ; cols R */
    while (i < sizeof(buf)-1) {
        if (read(ifd,buf+i,1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';

    /* Parse it. */
    if (buf[0] != ESC || buf[1] != '[') return -1;
    if (sscanf(buf+2,"%d;%d",rows,cols) != 2) return -1;
    return 0;
}

int getWindowSize(int ifd, int ofd, int *rows, int *cols) {
    struct winsize ws;

    if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        /* ioctl() failed. Try to query the terminal itself. */
        int orig_row, orig_col, retval;

        /* Get the initial position so we can restore it later. */
        retval = getCursorPosition(ifd,ofd,&orig_row,&orig_col);
        if (retval == -1) goto failed;

        /* Go to right/bottom margin and get position. */
        if (write(ofd,"\x1b[999C\x1b[999B",12) != 12) goto failed;
        retval = getCursorPosition(ifd,ofd,rows,cols);
        if (retval == -1) goto failed;

        /* Restore position. */
        char seq[32];
        snprintf(seq,32,"\x1b[%d;%dH",orig_row,orig_col);
        if (write(ofd,seq,strlen(seq)) == -1) {
            /* Can't recover... */
        }
        return 0;
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }

failed:
    return -1;
}

void updateWindowSize(void) {
    if (getWindowSize(STDIN_FILENO,STDOUT_FILENO,
                      &screenrows,&screencols) == -1) {
        perror("Unable to query the screen for size (columns / rows)");
        exit(1);
    }
	pagelen = screenrows - 1;
}
