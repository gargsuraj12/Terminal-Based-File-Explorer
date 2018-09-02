//Linux copy file & Directory utility
#include "cpUtility.h"

using namespace std;

extern string homePath; 
extern int winLen,iCol,iRow;

int copyFiles(int argc, vector<string> argv, string currDir){
	FILE *srcFile, *destFile;
	string destDir; 
	char ch;
	//Considering './a.out or copy' as first perameter. 
	if(argc < 3){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Insufficient arguements!!");
		return -1;
	}
	destDir = argv[argc-1];
	
	for(int i=1; i<argc-1; i++){
		chdir((char *)currDir.c_str());		
		srcFile = fopen((char *)argv[i].c_str(), "r");
		if(srcFile == NULL){
			printf("\033[%d;%dH",winLen-2,iCol);
			fprintf(stderr, "Unable to open file %s\n",(char *)argv[i].c_str());
			return -1;
		}
		chdir((char *)destDir.c_str());
		 
		destFile = fopen((char *)argv[i].c_str(), "w");
		//if unable to open the destDirination close the source also
		if(destFile == NULL){
			printf("\033[%d;%dH",winLen-2,iCol);
			fprintf(stderr, "Unable to copy file '%s'\n", (char *)argv[i].c_str());
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

/*
int copyDirectories(int argc, char **argv){
	FILE *srcFile, *destFile,*copyLoc;
	char *srcDir, *destDir;
	string currDir,currDest;
	DIR *dp;
	struct dirent *entryPtr;
	struct stat fileStat;
	int status;
	
	if(argc < 3){
		fprintf(stderr, "Insufficeint Arguements!!\n");
		return -1;
	}
	//Getting the current directory from PWD env variable and making the absolute source path
	currDir = (string) getenv("PWD");
	//cout<<"Current directory 1 is "<<currDir<<endl;
	
	srcDir = getenv("PWD");
	strcat(srcDir, "/");
	strcat(srcDir, argv[1]);
	
	//Changing directory to destination
	
	destDir = argv[2];
	chdir(destDir);
	strcat(destDir, argv[1]);
	currDest = (string) destDir;
	
	//Creating supplied directory at destination
	status = mkdir(destDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
	if(status == -1){
		fprintf(stderr, "Cannot create the directory '%s' as already exist at %s\n",argv[1],argv[2]);
		return -1;
	}else if(status == 0){
		fprintf(stdout, "Successfully created the directory '%s' @ '%s'\n",argv[1],argv[2]);
	}
	//Opening Current directory structure for operations
	dp = opendir((const char *) srcDir);
	if(dp == NULL){
		fprintf(stderr, "Unable to open source directory!! %s", srcDir);
		return -1;
	}
	//fprintf(stdout, "Current Destination directory is '%s'\n",destDir);
	//cout<<"\nCurrent directory 2 is "<<currDir<<endl;
	
	fprintf(stdout, "Current source directory is '%s'\n", srcDir);
	currDir.append("/");
	currDir.append(argv[1]);
	while((entryPtr = readdir(dp)) != NULL){
		stat(entryPtr->d_name, &fileStat);
		int status;
		char *command, *destPath;
		
		command = (char *) "copy";
		if(entryPtr->d_type == DT_DIR){	//if current dir entry is a directory then recurse
			if(strcmp(entryPtr->d_name,"..")!=0 && strcmp(entryPtr->d_name, ".")!=0){
				//Recursive code here
				chdir(srcDir);
				char *dirToCopy = (char *) entryPtr->d_name;
				destPath = destDir;
				strcat(destPath, "/");
				char *copyDataInfo[3] = {command, dirToCopy, destPath};
				status = copyDirectories(3, copyDataInfo);
				//chdir("..");
			}
		}else{			//if current directory entry is a file then copy
			//Current destination of the file needs to be changed
			cout<<"\nEntering in else of "<<currDir<<endl;
			char *fileToCopy = (char *) entryPtr->d_name;
			destPath = destDir;
			char *copyDataInfo[3] = {command, fileToCopy, (char *)currDest.c_str()};
			
			status = copyFiles(3,copyDataInfo,currDir);
			if(status == 0){
				fprintf(stdout, "file '%s' copied successfully..\n", entryPtr->d_name);
			}else{
				fprintf(stderr, "Error occured while copying the file '%s'\n", entryPtr->d_name);
			}
		}
	}
	cout<<"while ended of "<<currDir<<endl;
	//chdir(currDir.c_str());
	//closedir(dp);
	chdir("..");
	return 0;
}*/

/*int main(int argc, char **argv){
	
	//return copyFiles(3, copyDataInfo);
	//return copyDirectories(argc, argv);
	vector <string> vec;
	for(int i=1; i<argc; i++){
		vec.push_back(argv[i]);
	}
	string currDir = getenv("PWD");
	copyFiles(3, vec, currDir);
}*/