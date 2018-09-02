#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>	
#include <vector>
#include <iostream>
#include <unistd.h>
#include <string>
#include "lsUtility.h"

using namespace std;

const char* sizeUnits[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

bool isDirectory(struct dirent *entryPtr){
	struct stat filestat;
	stat(entryPtr->d_name, &filestat);
	if(entryPtr->d_type == DT_DIR){
		return true;
	}
	return false;
}

vector <struct dirent *> listFiles(char *currDir){
	DIR *dp = NULL; 						//pointer to the directory
	struct dirent *entryPtr = NULL;		//pointer to directory entry
	struct stat filestat;
	unsigned int count;
	vector <struct dirent *> vecFiles;
	int row=2,col = 2;
	long double fileSize;
	//Checking if the current directory is accessible
	if(currDir == NULL){
		fprintf(stderr,"Error: Could not get the current working directory\n");
		//return -1;
		exit(1);
	}
	
	//opening the current working directory
	dp = opendir((const char*)currDir);
	if(dp == NULL){
		fprintf(stderr,"Error: Could not open the current working directory\n");
		exit(1);
	}
	
	fprintf(stdout,"\n");
	count =0;
	printf("\033[2J");
	printf("\033[1;%dH",col);
	while((entryPtr = readdir(dp)) != NULL){
		vecFiles.push_back(entryPtr);
		stat(entryPtr->d_name, &filestat);
		if(entryPtr->d_type == DT_DIR){
			printf("\033[%d;1H",row);
			printf(">");
		}
		printf("\033[%d;%dH",row,col);
		fprintf(stdout,"%s", entryPtr->d_name);
		printf("\033[%d;40H",row);
		fprintf(stdout,(entryPtr->d_type == DT_DIR)? "d":"-");
		fprintf(stdout,(filestat.st_mode & S_IRUSR )? "r":"-");
		fprintf(stdout,(filestat.st_mode & S_IWUSR )? "w":"-");
		fprintf(stdout,(filestat.st_mode & S_IXUSR )? "x":"-");
		fprintf(stdout,(filestat.st_mode & S_IRGRP )? "r":"-");
		fprintf(stdout,(filestat.st_mode & S_IWGRP )? "w":"-");
		fprintf(stdout,(filestat.st_mode & S_IXGRP )? "x":"-");
		fprintf(stdout,(filestat.st_mode & S_IROTH )? "r":"-");
		fprintf(stdout,(filestat.st_mode & S_IWOTH )? "w":"-");
		fprintf(stdout,(filestat.st_mode & S_IXOTH )? "x":"-");
		
		printf("\033[%d;60H",row);
		int i = 0;
		fileSize = filestat.st_size;
		while (fileSize > 1024) {
			fileSize /= 1024;
			i++;
		}
		fprintf(stdout,"%.*Lf %s", i, fileSize, sizeUnits[i]);
		//fprintf(stdout,"%lu\t",filestat.st_size);
		
		printf("\033[%d;80H",row);
		fprintf(stdout,"%s",ctime(&filestat.st_mtime));
		count++;
		row++;
	}
	printf("\033[30;%dH",col);
	return vecFiles;
}

/*int main(){
	char *currDir =  (char *) ".";
	vector <struct dirent *> temp;
	temp =  listFiles(currDir);
	/*cout<<endl;
	for(auto it = temp.begin(); it != temp.end(); ++it){
		fprintf(stdout,"%s\n", *it);
	}
	return 0;
}*/