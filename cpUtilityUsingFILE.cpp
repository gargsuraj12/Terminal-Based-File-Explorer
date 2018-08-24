//Linux copy file utility
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

int copyFiles(int argc, char **argv){
	FILE *srcFile, *destFile;
	char *currDir, *destDir; 
	char ch;
	//currently considering './a.out' as perameter. Remember to exclude that later
	int files[argc-2];
	if(argc < 3){
		fprintf(stderr, "Insufficient arguements!!\n");
		return -1;
	}
	currDir = getenv("PWD");
	destDir = argv[argc-1];
	//argv[1] to argv[argc-2] source file name
	for(int i=1; i<argc-1; i++){
		chdir(currDir);		
		srcFile = fopen(argv[i], "r");
		if(srcFile == NULL){
			fprintf(stderr, "Unable to open %s\n",argv[2]);
			return -1;
		}
		chdir(destDir);
		//argv[argc-1] = destDirination 
		destFile = fopen(argv[i], "w");
		//if unable to open the destDirination close the source also
		if(destFile == NULL){
			fprintf(stderr, "Unable to copy '%s'\n", argv[i]);
			fclose(srcFile);
			return -1;
		}
		
		while ((ch = fgetc(srcFile)) != EOF){
			fputc(ch, destFile);
		}
		fclose(srcFile);
		fclose(destFile);
	}
	return 0;	
}

int copyDirectories(int argc, char **argv){
	FILE *srcFile, *destFile,*copyLoc;
	char *srcDir, *destDir;
	DIR *dp;
	struct dirent *dePtr;
	struct stat fileStat;
	int status;
	
	if(argc < 3){
		fprintf(stderr, "Insufficeint Arguements!!\n");
		return -1;
	}
	//Getting the current directory from PWD env variable and making the absolute source path
	srcDir = getenv("PWD");	
	strcat(srcDir, "/");
	strcat(srcDir, argv[1]);
	
	//Changing directory to destination
	destDir = argv[2];
	chdir(destDir);
	strcat(destDir, argv[1]);
		
	//Creating supplied directory at destination
	status = mkdir(destDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
	if(status == -1){
		fprintf(stderr, "Cannot create the directory '%s' as already exist at %s\n",argv[1],argv[2]);
		return -1;
	}else if(status == 0){
		fprintf(stdout, "Successfully created the directory '%s'\n",argv[1]);
	}
	//Opening the source directory for iteration
	dp = opendir((const char *) srcDir);
	if(dp == NULL){
		fprintf(stderr, "Unable to open source directory!! %s", srcDir);
		return -1;
	}
	while((dePtr = readdir(dp)) != NULL){
		//printf("-------------Entering in while----------------\n");
		stat(dePtr->d_name, &fileStat);
		if(dePtr->d_type == DT_DIR){	//if current dir entry is a directory then recurse
			printf("-------------Entering in if--> curr file is directory----------------\n");
			fprintf(stdout, "file name is '%s'\n", dePtr->d_name);
		}else{			//if current dir entry is a file then copy	
			int status;
			char *command = (char *) "copy";
			char *fileToCopy = (char *) dePtr->d_name;
			char *destPath = destDir;
			char *copyDataInfo[3] = {command, fileToCopy, destPath};
			status = copyFiles(3,copyDataInfo);
			/*if(status == -1){
				fprintf(stderr, "Error occured while copying the file '%s'\n", dePtr->d_name);
				return -1;
			}*/
		}
	}
}

int main(int argc, char **argv){
	/*char *command = (char *) "copy";
	char *fileToCopy = (char *) "cpTestDataFile";
	char *destPath = (char *) "/home/suraj/Desktop/Others/Test";
	char *copyDataInfo[3] = {command, fileToCopy, destPath};
	return copyFiles(3, copyDataInfo);
	*/
	return copyDirectories(argc, argv);
}