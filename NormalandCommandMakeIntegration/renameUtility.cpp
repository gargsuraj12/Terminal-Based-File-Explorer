#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>
#include <unistd.h>
#include "renameUtility.h"

using namespace std;

extern string homePath; 
extern int winLen,iCol,iRow;

int renameFile(int argc, vector<string> vec, string path){
	if(argc != 3){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Incorrect no of arguements..!!");
		return -1;
	}
	int x = chdir((char *)path.c_str());
	int rv = rename((char *)vec[1].c_str(),(char *)vec[2].c_str());
	
	//cout<<rv<<endl;
	return rv;
}

/*int main(int argc, char **argv){
	vector<string> vec;
	for(int i=0; i<argc; i++){
		vec.push_back(argv[i]);
	}
	//renameFile(vec.size(), vec);
	
	return 0;
}*/