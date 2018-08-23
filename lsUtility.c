#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>	

int main(){
	
	char *currDir = NULL;
	DIR *dp = NULL; 				//pointer to the directory
	struct dirent *deptr = NULL;	//pointer to directory entry
	struct stat filestat;
	unsigned int count;
	
	//storing the current directory using PWD environment variable 
	currDir = getenv("PWD");
	if(currDir == NULL){
		printf("\nError: Could not get the current working directory\n");
		return -1;
	}
	
	//opening the current working directory
	dp = opendir((const char*)currDir);
	if(dp == NULL){
		printf("\nError: Could not open the current working directory\n");
		return -1;
	}
	
	printf("\n");
	count =0;
	while((deptr = readdir(dp)) != NULL){
		stat(deptr->d_name, &filestat);
		printf(S_ISDIR(filestat.st_mode)? "d":"-");
		printf((filestat.st_mode & S_IRUSR )? "r":"-");
		printf((filestat.st_mode & S_IWUSR )? "w":"-");
		printf((filestat.st_mode & S_IXUSR )? "x":"-");
		
		printf((filestat.st_mode & S_IRGRP )? "r":"-");
		printf((filestat.st_mode & S_IWGRP )? "w":"-");
		printf((filestat.st_mode & S_IXGRP )? "x":"-");
		
		printf((filestat.st_mode & S_IROTH )? "r":"-");
		printf((filestat.st_mode & S_IWOTH )? "w":"-");
		printf((filestat.st_mode & S_IXOTH )? "x":"-");
		
		printf("\t%s\t", deptr->d_name);
		printf("%lu\t",filestat.st_size);
		printf("%s",ctime(&filestat.st_mtime));
		count++;
	}
	printf("Total %u\n",count);
	return 0;
}