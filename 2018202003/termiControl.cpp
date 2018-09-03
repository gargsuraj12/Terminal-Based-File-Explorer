/*
Name: Suraj Garg
Roll No: 2018202003
*/

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "constants.h"
# include "termiControl.h"

using namespace std;

struct termios newTerm, iniTerm;

int setNonCanon(){
	//FILE *input, *output;
	if (!isatty(fileno(stdout))) {
		fprintf(stderr,"This is not a valid terminal, OK.\n");
		return -1;
	}
	/*input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if(!input || !output) {
		fprintf(stderr, "Unable to open standard terminal\n");
		//exit(1);
		return -1;
	}*/
	tcgetattr(fileno(stdin), &iniTerm);
    memcpy(&newTerm, &iniTerm, sizeof(newTerm));
    newTerm.c_lflag &= ~(ICANON | ECHO);
	newTerm.c_lflag &= ~ISIG;
    newTerm.c_cc[VMIN] = 1;
    newTerm.c_cc[VTIME] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &newTerm);
	return 0;
}

int unsetNonCanon(){
	tcsetattr(fileno(stdin), TCSANOW, &iniTerm);
	return 0;
}

/*int getch(void){
    int c = 0;
	setNonCanon();
	c = getchar();
	unsetNonCanon();
    return c;
}*/

int getEscKey(void){
    int c;
	c = getchar();
    if (c == '[') {
        switch (getchar()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
				c = KEY_RIGHT;
                break;
            case 'D':
				c = KEY_LEFT;
                break;
            default:
                c = 0;
                break;
        }
    } else {
        c = 0;
    }
    return c;
}

int getkey(void){
    int c;
    //c = getch();
	//setNonCanon();
	c = getchar();
    return (c == KEY_ESCAPE) ? getEscKey() : c;
}

