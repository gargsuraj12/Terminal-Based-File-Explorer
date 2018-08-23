//Linux copy file utility
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>



int main(int argc, char **argv){
	FILE *srcFile, *destDir; 
	char ch;
	//currently considering './a.out' as perameter. Remember to exclude that later
	int files[argc-2];
	if(argc < 3){
		fprintf(stderr, "Insufficient arguements!!\n");
		return -1;
	}
	//argv[2] = source file name
	srcFile = fopen(argv[1], "r");
	if(srcFile == NULL){
		fprintf(stderr, "Unable to open %s\n",argv[2]);
		return -1;
	}
	chdir(argv[2]);
	//argv[3] = destDirination 
	destDir = fopen(argv[1], "w");
	//if unable to open the destDirination close the source also
	if(files[1] == -1){
		fprintf(stderr, "Unable to open %s\n",argv[2]);
		fclose(srcFile);
		return -1;
	}
	
    while ((ch = fgetc(srcFile)) != EOF){
        fputc(ch, destDir);
    }
	fclose(srcFile);
	fclose(destDir);
	return 0;
}