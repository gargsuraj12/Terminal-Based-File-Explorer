/*
Name: Suraj Garg
Roll No: 2018202003
*/

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