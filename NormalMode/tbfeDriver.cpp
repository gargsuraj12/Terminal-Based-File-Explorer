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

struct dirent *entryPtr = NULL;
int c, fileCount, winLen;
string nextPath, homePath, currPath, prePath;

int clearScreenAndListFiles(char * path){
	int fc;
	clearScreen();													//clear the screen
	printf("\033[%d;%dH",iRow,iCol); 				//place the cursor at top
	fileVec = listFiles(path);
	winIndex = 0;
	fc = fileVec.size();
	movecursorTop();
	return fc;
}

void gotoHome(){
	if(pathStack.empty()){
		cout<<"No parent directory exist..";
	}else{
		nextPath = homePath;
		pathStack = stack<string>();
		currPath = nextPath;
		fileVec.clear();
		fileCount = clearScreenAndListFiles((char *)nextPath.c_str());	
	}
}

void gotoPreviousDirectory(){
	if(pathStack.empty()){
				cout<<"No parent directory exist..";
			}else{
				prePath = pathStack.top();
				pathStack.pop();
				fileVec.clear();
				currPath = prePath;
				fileCount = clearScreenAndListFiles( (char *) prePath.c_str());
			}
}

void enterDirectory(struct dirent *entryPtr){
	if(strcmp(entryPtr->d_name,"..") == 0){
		gotoPreviousDirectory();
	} else if(strcmp(entryPtr->d_name,".") == 0){
		if(pathStack.empty()){
			printf("Congrats!! You already in current directory..");						
		}else{
			//Do Nothing
		}
	}else if(entryPtr != NULL && isDirectory(entryPtr)){
		nextPath = currPath;
		nextPath.append("/");
		nextPath.append(entryPtr->d_name);
		pathStack.push(currPath);
		currPath = nextPath;
		fileVec.clear();
		fileCount = clearScreenAndListFiles((char *)nextPath.c_str());
	}else{
		if(entryPtr->d_type == DT_REG){
			string file;
			file.append("xdg-open ");
			file.append(currPath);
			file.append("/");
			file.append(entryPtr->d_name);
			system((char *)file.c_str());
		}else{
			printf("This is not a regular file so cannot open it..");	
		}
	}	
}

int driver(int argc, char **argv){
	currPath = getenv("PWD");
	if(argc == 2){
		currPath = argv[1];
	}
	homePath = currPath;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &wSize);		//to get the size of the current terminal
	winLen = wSize.ws_row;
	fileCount = clearScreenAndListFiles((char *)currPath.c_str());
	setNonCanon();				//Setting non canonical mode
	while (1) {
        c = getkey();
		//moveCursorBottom();
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
			moveCursorBottom();
			entryPtr = fileVec[winIndex];
			
			enterDirectory(entryPtr);
			
			winIndex = 0;
			movecursorTop();
			//KEY_ENTER ended here
			
        } else if (c == KEY_BACKSPACE){
			moveCursorBottom();
			
			gotoPreviousDirectory();
			
			winIndex = 0;
			movecursorTop();
        } else if (c == KEY_SMALLH || c == KEY_CAPH){
			moveCursorBottom();
			
			gotoHome();
			
			winIndex = 0;
			movecursorTop();
        }   else if (c == KEY_RIGHT) {
			moveCursorBottom();
			entryPtr = fileVec[winIndex];
			
			enterDirectory(entryPtr);
			
			winIndex = 0;
			movecursorTop();
        } else if (c == KEY_LEFT) {
			moveCursorBottom();
			
			gotoPreviousDirectory();
			
			winIndex = 0;
			movecursorTop();
        } else if (c == KEY_COLON){
			moveCursorBottom();
            printf("Pressing colon key..");
			winIndex = 0;
			movecursorTop();
        }
    }
	printf("\033[2J\033[%d;%dH",iRow,iCol);
    printf("\n");
}

int main(int argc, char **argv){	
    driver(argc, argv);	
	unsetNonCanon();
    return 0;
}