#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "lsUtility.h"
#include "constants.h"
# include "termiControl.h"

using namespace std;

static struct winsize wSize;
static int winIndex = 0;
int iRow = 1, iCol = 1;
stack<string> pathStack;
vector <struct dirent *> fileVec;

string currPath, prePath;
struct dirent *deptr = NULL;
int c, fileCount, winLen;
string nextPath;

int clearScreenAndListFiles(char * path){
	int fc;
	printf("\033[2J");											//clear the screen
	printf("\033[%d;%dH",iRow,iCol); 				//place the cursor at top
	fileVec = listFiles(path);
	winIndex = 0;
	fc = fileVec.size();
	printf("\033[2;1H");
	return fc;
}

int driver(int argc, char **argv){
	currPath = getenv("PWD");
	if(argc == 2){
		currPath = argv[1];
	}			
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &wSize);		//to get the size of the current terminal
	winLen = wSize.ws_row;
	fileCount = clearScreenAndListFiles((char *)currPath.c_str());
	
	while (1) {
        c = getkey();
        if (c == KEY_SMALLQ || c == KEY_CAPQ){
            break;
			
        } else if (c == KEY_UP) {
			winIndex--;
			if(winIndex >= iRow-1){
				cursorUp(1);
			}else{
				winIndex++;
			}
           
        } else if (c == KEY_DOWN) {
			winIndex++;
			if(winIndex < fileCount){
				cursorDown(1);
			}else{
				winIndex--;
			}  
			
        } else if (c == KEY_ENTER){
			printf("\033[%d;%dH",winLen,iCol); 
			deptr = fileVec[winIndex];
			if(deptr != NULL && isDirectory(deptr)){
				nextPath = currPath;
				nextPath.append("/");
				nextPath.append(deptr->d_name);
				pathStack.push(currPath);
				currPath = nextPath;
				fileVec.clear();
				fileCount = clearScreenAndListFiles((char *)nextPath.c_str());
			}else{										//if file then write code to open file here
				printf("Not a directory cannot open it..");
			}
			winIndex = 0;
			printf("\033[2;%dH",iCol);	
			
			//KEY_ENTER ended here
			
        } else if (c == KEY_BACKSPACE){
			printf("\033[%d;%dH",winLen,iCol); 
			if(pathStack.empty()){
				cout<<"No parent directory exist..";
			}else{
				prePath = pathStack.top();
				pathStack.pop();
				fileVec.clear();
				currPath = prePath;
				fileCount = clearScreenAndListFiles( (char *) prePath.c_str());
			}
			winIndex = 0;
			printf("\033[2;%dH",iCol);
        }  else if (c == KEY_RIGHT) {
			printf("\033[%d;%dH",winLen,iCol); 
            printf("Pressing right arrow..");
			winIndex = 0;
			printf("\033[2;%dH",iCol); 
            //cursorBackward(1);
        } else if (c == KEY_LEFT) {
			printf("\033[%d;%dH",winLen,iCol); 
            printf("Pressing left arrow..");
			winIndex = 0;
			printf("\033[2;%dH",iCol); 
            //cursorForward(1);
        } else if (c == KEY_COLON){
			printf("\033[%d;%dH",winLen,iCol); 
            printf("Pressing colon key..");
			winIndex = 0;
			printf("\033[2;%dH",iCol); 
        } else if (c == KEY_SMALLH || c == KEY_CAPH){
			printf("\033[%d;%dH",winLen,iCol); 
            printf("Pressing h/H key..");
			winIndex = 0;
			printf("\033[2;%dH",iCol); 
        } 
    }
	printf("\033[2J\033[%d;%dH",iRow,iCol);
    printf("\n");
}

int main(int argc, char **argv){	
    driver(argc, argv);	
    return 0;
}