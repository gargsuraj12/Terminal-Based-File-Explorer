#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define cursorForward(x) printf("\033[%dC", (x))
#define cursorBackward(x) printf("\033[%dD", (x))
#define cursorUp(x) printf("\033[%dA", (x))
#define cursorDown(x) printf("\033[%dB", (x))

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108
#define KEY_CAPQ 81
#define KEY_SMALLQ 113
#define KEY_COLON 58
#define KEY_SMALLH 104
#define KEY_CAPH 72
#define KEY_BACKSPACE 8


static struct termios newTerm, iniTerm;

int setNonCanon(){
	FILE *input, *output;
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
    newTerm.c_cc[VMIN] = 1;
    newTerm.c_cc[VTIME] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &newTerm);
	return 0;
}

int unsetNonCanon(){
	tcsetattr(fileno(stdin), TCSANOW, &iniTerm);
	return 0;
}

static int getch(void){
    int c = 0;
	setNonCanon();
	c = getchar();
	unsetNonCanon();
    return c;
}

static int kbesc(void){
    int c;
    c = getch();
    if (c == '[') {
        switch (getch()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_LEFT;
                break;
            case 'D':
                c = KEY_RIGHT;
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

static int getkey(void){
    int c;
    c = getch();
    return (c == KEY_ESCAPE) ? kbesc() : c;
}

int main(void){
    int c;

    while (1) {
        c = getkey();
        if (c == KEY_SMALLQ || c == KEY_CAPQ){
            break;
        } else if (c == KEY_UP) {
           cursorUp(1);
        } else if (c == KEY_DOWN) {
            cursorDown(1);
        } else if (c == KEY_RIGHT) {
            cursorBackward(1);
        } else if (c == KEY_LEFT) {
            cursorForward(1);
        } else if (c == KEY_COLON){
            putchar(c);
        } else if (c == KEY_SMALLH || c == KEY_CAPH){
            putchar(c);
        } else if (c == KEY_BACKSPACE){
            putchar(c);
        }  
    }
    printf("\n");
    return 0;
}