#include <string>
using namespace std;

#define cursorForward(x) printf("\033[%dC", (x))
#define cursorBackward(x) printf("\033[%dD", (x))
#define cursorUp(x) printf("\033[%dA", (x))
#define cursorDown(x) printf("\033[%dB", (x))
#define moveCursorBottom() printf("\033[%d;%dH",winLen,iCol)
#define moveCursorTop() printf("\033[2;%dH",iCol)
#define clearScreen() printf("\033[2J")


#define KEY_ESCAPE  0x001b
#define KEY_ENTER   	0x000a
#define KEY_UP      		0x0105
#define KEY_DOWN    	0x0106
#define KEY_LEFT    	0x0107
#define KEY_RIGHT   	0x0108
#define KEY_CAPQ 				81
#define KEY_SMALLQ 			113
#define KEY_COLON 			58
#define KEY_SMALLH 			104
#define KEY_CAPH 				72
#define KEY_BACKSPACE 	127
