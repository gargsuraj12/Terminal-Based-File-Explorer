#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "lsUtility.h"
#include "constants.h"
# include "termiControl.h"
#include "cpUtility.h"
#include "renameUtility.h"

using namespace std;

int commandMode();
int clearScreenAndListFiles(char *);
void gotoHome();
void gotoPreviousDirectory();
void enterDirectory(struct dirent *);
int commandHandler(vector<string>);

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
	moveCursorTop();
	return fc;
}

void gotoHome(){
	if(pathStack.empty()){//save and restore the cursor position using escape sequance
		printf("\033[%d;%dH",winLen,iCol);
		printf("\033[0J");
		printf("No parent directory exist..");
	}else{
		nextPath = homePath;
		pathStack = stack<string>();
		currPath = nextPath;
		fileVec.clear();
		fileCount = clearScreenAndListFiles((char *)nextPath.c_str());
		winIndex = 0;
		moveCursorTop();	
	}
}

void gotoPreviousDirectory(){
	if(pathStack.empty()){
			printf("\033[%d;%dH",winLen,iCol);
			printf("\033[0J");
			cout<<"No parent directory exist..";
			}else{
				prePath = pathStack.top();
				pathStack.pop();
				fileVec.clear();
				currPath = prePath;
				fileCount = clearScreenAndListFiles( (char *) prePath.c_str());
				winIndex = 0;
				moveCursorTop();
			}
}

void enterDirectory(struct dirent *entryPtr){
	if(strcmp(entryPtr->d_name,"..") == 0){
		gotoPreviousDirectory();
	} else if(strcmp(entryPtr->d_name,".") == 0){
		if(pathStack.empty()){
			printf("\033[%d;%dH",winLen,iCol);
			printf("\033[0J");
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
		winIndex = 0;
		moveCursorTop();
	}else{
		if(entryPtr->d_type == DT_REG){
			string file;
			file.append("xdg-open ");
			file.append(currPath);
			file.append("/");
			file.append(entryPtr->d_name);
			int rv;
			rv= system((char *)file.c_str());
			//fprintf(stderr, (system((char *)file.c_str()==0)));
			if(rv != 0){
				moveCursorBottom();
				printf("No application is registered to handle this file..");
				winIndex = 0;
				moveCursorTop();
			}
		}else{
			printf("This is not a regular file so cannot open it..");	
		}
	}	
}

int normalModedriver(int argc, char **argv){
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
			moveCursorTop();
			//KEY_ENTER ended here
			
        } else if (c == KEY_BACKSPACE){
			moveCursorBottom();
			
			gotoPreviousDirectory();
			
			winIndex = 0;
			moveCursorTop();
        } else if (c == KEY_SMALLH || c == KEY_CAPH){
			moveCursorBottom();
			
			gotoHome();
			
			winIndex = 0;
			moveCursorTop();
        }   else if (c == KEY_RIGHT) {
			moveCursorBottom();
			entryPtr = fileVec[winIndex];
			
			enterDirectory(entryPtr);
			
			winIndex = 0;
			moveCursorTop();
        } else if (c == KEY_LEFT) {
			moveCursorBottom();
			
			gotoPreviousDirectory();
			
			winIndex = 0;
			moveCursorTop();
        } else if (c == KEY_COLON){
			moveCursorBottom();
			unsetNonCanon();
			fileCount = clearScreenAndListFiles((char *)currPath.c_str());
			commandMode();						//Entering in Command mode
			setNonCanon();
			fileCount = clearScreenAndListFiles((char *)currPath.c_str());
			winIndex = 0;
			moveCursorTop();
        }
    }
	printf("\033[2J\033[%d;%dH",iRow,iCol);
    printf("\n");
}


//Function to take input in command mode
int commandMode(){
	vector<string> cVec;
	string arg,currDir;
	char ch;
	printf("\033[%d;%dH",winLen-3,iCol);	
	cout<<"Enter command here: ";
	while(true){
		ch = getchar();
		if(ch == KEY_ESCAPE){
			ch = getEscKey();
			if(ch == KEY_BACKSPACE){
				cursorBackward(3);
				printf("\033[0K");
			} else if(ch == KEY_LEFT){
				cursorBackward(1);
			} else if(ch == KEY_RIGHT){
				cursorForward(1);
			}else{
				//return;		//should be used later once functionality is buid
				break;			//meanwhile using this	
			}
		} else if(ch == ' '){
			cVec.push_back(arg);
			arg.clear();			
		} else if(ch == KEY_ENTER){
			cVec.push_back(arg);
			arg.clear();
			
			commandHandler(cVec);
			
			cVec.clear();
			printf("\033[%d;%dH",winLen-3,iCol);
			printf("\033[0J");
			printf("\033[%d;%dH",winLen-3,iCol);
			printf("Enter command here: ");
		} else{
			arg += ch;
		}	
	}
}

//Function to interpret command and calling appropriate function
int commandHandler(vector<string> vec){
	int size = vec.size();
	int status = 1;
	if(size < 3){
		printf("Insufficient arguements!!..");
		return -1;
	}
	string command = vec[0];
	if(command == "copy"){
		
		status = copyFiles(size, vec, currPath);
		
	}else if(command == "move"){
		
	}else if(command == "rename"){
		status = renameFile(size, vec, currPath);
		fileCount = clearScreenAndListFiles((char *)currPath.c_str());
		//cout<<"status = "<<status; 
	}else if(command == "create"){
		
	}else if(command == "delete"){
		
	}else if(command == "search"){
		
	}else{
		printf("Invalid command..");
		return -1;
	}
	vec.clear();
}

int main(int argc, char **argv){	
    normalModedriver(argc, argv);	
	unsetNonCanon();
    return 0;
}