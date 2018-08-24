//Linux copy file utility
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

int main(int argc, char **argv){
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