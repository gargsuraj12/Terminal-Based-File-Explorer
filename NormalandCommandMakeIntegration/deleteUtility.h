#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

int deleteFile(string , string);
int deleteDirectory(string , string );
int deleteFileHandler(int , vector<string> , string );
int deleteDirHandler(int , vector<string> , string );