#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>	
#include <vector>

using namespace std;

vector <struct dirent *> vecDirent;

int listFiles(char *currDir){
	DIR *dp = NULL; 						//pointer to the directory
	struct dirent *deptr = NULL;		//pointer to directory entry
	struct stat filestat;
	unsigned int count;
	//vector<>
	
	//Checking if the current directory is accessible
	if(currDir == NULL){
		fprintf(stderr,"Error: Could not get the current working directory\n");
		return -1;
	}
	
	//opening the current working directory
	dp = opendir((const char*)currDir);
	if(dp == NULL){
		fprintf(stderr,"Error: Could not open the current working directory\n");
		return -1;
	}
	
	fprintf(stdout,"\n");
	count =0;
	while((deptr = readdir(dp)) != NULL){
		vecDirent.push_back(deptr);
		count++;
	}
	
	for(auto it = vecDirent.begin(); it != vecDirent.end(); ++it){
		deptr = (struct dirent *) *it;
		stat(deptr->d_name, &filestat);
		fprintf(stdout,S_ISDIR(filestat.st_mode)? "d":"-");
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
	}
	//fprintf(stdout,"Total %u\n",count);
	return 0;
}


int listFilesController(char *currDir){
	return listFiles(currDir);
}

/*int main(){
	char *currDir =  (char *) ".";
	return listFilesController(currDir);
}*/