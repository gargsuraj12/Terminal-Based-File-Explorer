#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sys/ioctl.h>
#include "lsUtility.h"
#include "constants.h"
# include "termiControl.h"
#include "cpUtility.h"
#include "renameUtility.h"
#include "createUtility.h"
#include "deleteUtility.h"

using namespace std;

int commandMode();
int clearScreenAndListFiles(char *);
void gotoHome();
void gotoPreviousDirectory();
void enterDirectory(struct dirent *);
int gotoSpecificDirectory(string);
int commandHandler(vector<string>);
int normalModedriver(int argc, char **argv);