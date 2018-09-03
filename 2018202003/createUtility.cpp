/*
Name: Suraj Garg
Roll No: 2018202003
*/

#include "createUtility.h"

using namespace std;

extern string homePath; 
extern int winLen,iCol,iRow;

int createFile(string filename, string path){
	FILE *file;
	int x = chdir((char *)path.c_str());
	if(x != 0){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Unable to change directory to destination path..!!");
		return -1;
	}
	file = fopen((char *)filename.c_str(), "w");
	//if unable to open the destDirination close the source also
	if(file == NULL){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Unable to create file '%s'\n", (char *)filename.c_str());
		return -1;
	}
	fclose(file);
	return 0;
}

int createDirectory(string dirname, string path){
	int status;
	int x = chdir((char *)path.c_str());
	if(x != 0){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Unable to change directory to destination path..!!");
		return -1;
	}
	status = mkdir((char *)dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
	if(status == -1){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Cannot create the directory '%s' as already exist \n",(char *)dirname.c_str());
		return -1;
	}
	return status;
}

int createFileHandler(int argc, vector<string> argv, string currPath){
	if(argc != 3){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Incorrect arguements..!!");
		return -1;
	}
	string filename, path;
	filename = argv[1];
	if(argv[2] == "."){
		path = currPath;
	}else{
		path = argv[2];
	}
	return createFile(filename, path);
}

int createDirHandler(int argc, vector<string> argv, string currPath){
	if(argc != 3){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Incorrect arguements..!!");
		return -1;
	}
	string filename, path;
	filename = argv[1];
	if(argv[2] == "."){
		path = currPath;
	}else{
		path = argv[2];
	}
	return createDirectory(filename, path);
}

/*int main(int argc, char **argv){
	vector<string> vec;
	string currPath;
	currPath = getenv("PWD");
	//for(int i=0; i<argc; i++){
		//vec.push_back(argv[i]);
	//}
	vec.push_back("create_file");
	vec.push_back("testdir1");
	vec.push_back("/home/suraj/Desktop/Others");
	cout<<"Curr Path is: "<<currPath<<endl;
	//cout<<"File creation status is: "<<createFileHandler(vec.size(), vec, currPath)<<endl;
	cout<<"File creation status is: "<<createDirHandler(vec.size(), vec, currPath)<<endl;
	return 0;
}*/