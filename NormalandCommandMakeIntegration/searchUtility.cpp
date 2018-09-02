#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

string srcDir = getenv("PWD");
vector<string> fileVec;

int searchFile(int argc, string filetosearch, string currDir){
	//cout<<"Src path is: "<<currDir<<endl;
	int x = chdir((char *)currDir.c_str());
	if(x != 0){
		printf("Unable to goto %s\n",(char *)currDir.c_str());
		return -1;
	}
	if(argc != 2){
		printf("Incorrect arguements..!!");
		return -1;
	}
	DIR *dp;
	struct dirent *entryPtr;
	struct stat fileStat;
	string nextPath,found;
	
	dp = opendir((const char *) (char *)currDir.c_str());
	if(dp == NULL){
		fprintf(stderr, "Unable to open directory '%s'", (char *)currDir.c_str());
		return -1;
	}
	
	while((entryPtr = readdir(dp)) != NULL){
		stat(entryPtr->d_name, &fileStat);
		if(entryPtr->d_type == DT_DIR){	//if current dir entry is a directory then recurse
			if(strcmp(entryPtr->d_name,"..")!=0 && strcmp(entryPtr->d_name, ".")!=0){
				nextPath.append(currDir);
				nextPath.append("/");
				nextPath.append(entryPtr->d_name);
				//cout<<"Next path to enter is: "<<nextPath<<endl;
				searchFile(argc, filetosearch, nextPath);
				nextPath.clear();
			}
		}else{
			if(strcmp(entryPtr->d_name, (char *)filetosearch.c_str()) ==0){
				//cout<<"File found @ "<<currDir<<endl;
				fileVec.push_back(currDir);
			}
		}
	}
	return 0;	
}

int main(int argc, char **argv){
	string file = argv[1];
	searchFile(argc, file, "/home/suraj/Desktop");
	cout<<"File found @ :"<<endl;
	for(auto it : fileVec){
		cout<<it<<endl;
	}
	return 0;
}