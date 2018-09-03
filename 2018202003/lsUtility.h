/*
Name: Suraj Garg
Roll No: 2018202003
*/

#include <dirent.h>
#include <vector>

using namespace std;

bool isDirectory(struct dirent *entryPtr);
vector <struct dirent *> listFiles(char *currDir);