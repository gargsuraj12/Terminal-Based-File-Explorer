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

using namespace std;

void doKeyEnterFunc(){
	
}

bool isDirectory(struct dirent *deptr){
	struct stat filestat;
	stat(deptr->d_name, &filestat);
	if(deptr->d_type == DT_DIR){
		return true;
	}
	return false;
}

vector <struct dirent *> listFiles(char *currDir){
	DIR *dp = NULL; 						//pointer to the directory
	struct dirent *deptr = NULL;		//pointer to directory entry
	struct stat filestat;
	unsigned int count;
	vector <struct dirent *> vecFiles;
	
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
	while((deptr = readdir(dp)) != NULL){
		vecFiles.push_back(deptr);
		//deptr = (struct dirent *) *it;
		stat(deptr->d_name, &filestat);
		fprintf(stdout,(deptr->d_type == DT_DIR)? "d":"-");
		fprintf(stdout,(filestat.st_mode & S_IRUSR )? "r":"-");
		fprintf(stdout,(filestat.st_mode & S_IWUSR )? "w":"-");
		fprintf(stdout,(filestat.st_mode & S_IXUSR )? "x":"-");
		
		fprintf(stdout,(filestat.st_mode & S_IRGRP )? "r":"-");
		fprintf(stdout,(filestat.st_mode & S_IWGRP )? "w":"-");
		fprintf(stdout,(filestat.st_mode & S_IXGRP )? "x":"-");
		
		fprintf(stdout,(filestat.st_mode & S_IROTH )? "r":"-");
		fprintf(stdout,(filestat.st_mode & S_IWOTH )? "w":"-");
		fprintf(stdout,(filestat.st_mode & S_IXOTH )? "x":"-");
		
		fprintf(stdout,"\t%s\t", deptr->d_name);
		fprintf(stdout,"%lu\t",filestat.st_size);
		fprintf(stdout,"%s",ctime(&filestat.st_mtime));
		count++;
	}
	return vecFiles;
}


/*int main(){
	char *currDir =  (char *) ".";
	vector <char *> temp;
	temp =  listFiles(currDir);
	cout<<endl;
	for(auto it = temp.begin(); it != temp.end(); ++it){
		fprintf(stdout,"%s\n", *it);
	}
}*/