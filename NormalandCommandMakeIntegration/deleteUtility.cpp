#include "deleteUtility.h"

using namespace std;

//homePath from tbfeDriver need to be set as homePath  
extern string homePath; 
extern int winLen,iCol,iRow;
//string homePath= "/home/suraj/Desktop/Others/";

int deleteFile(string filename, string path){
	printf("\033[%d;%dH",winLen-1,iCol);
	cout<<"Path to delete is: "<<path<<endl;
	int x = chdir((char *)path.c_str());
	if(x != 0){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Unable to change directory to destination path..!!");
		return -1;
	}
	x = unlink((char *)filename.c_str());
	//if unable to open the destDirination close the source also
	if(x != 0){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "File '%s' not found..!!\n", (char *)filename.c_str());
		return -1;
	}
	return 0;
}

int deleteDirectory(string dirname, string path){
	int status;
	int x = chdir((char *)path.c_str());
	if(x != 0){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Unable to change directory to destination path..!!");
		return -1;
	}	
	status = rmdir((char *)dirname.c_str()); 
	if(status == -1){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Cannot delete the directory '%s' \n",(char *)dirname.c_str());
		return -1;
	}
	return status;
}

int deleteFileHandler(int argc, vector<string> argv, string currPath){
	if(argc != 3){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Incorrect arguements..!!");
		return -1;
	}
	string filename, path;
	filename = argv[1];
	if(argv[2] == "/"){
		path = homePath;
	} else if(argv[2] == "."){
		path = currPath;
	} else{
		path = argv[2];
	}
	return deleteFile(filename, path);
}

int deleteDirHandler(int argc, vector<string> argv, string currPath){
	if(argc != 3){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Incorrect arguements..!!");
		return -1;
	}
	string dirname, path;
	dirname = argv[1];
	if(argv[2] == "/"){
		path = homePath;
	} else if(argv[2] == "."){
		path = currPath;
	} else{
		path = argv[2];
	}
	DIR *dp = NULL; 									//pointer to the directory
	struct dirent *entryPtr = NULL;		//pointer to directory entry
	struct stat pathstat;
	
	stat((char *)path.c_str(), &pathstat);
    // if path does not exists or is not dir - exit with status -1
    if (S_ISDIR(pathstat.st_mode) == 0) {
		printf("\033[%d;%dH",winLen-2,iCol);
        fprintf(stderr, "'%s' Is not directory", (char *)path.c_str());
		return -1;
	    //removefile(path);
        //exit(-1);
    }
	dp = opendir((const char*)path.c_str());
	if(dp == NULL){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr,"Error: Could not open the destination directory\n");
		return -1;
		//exit(1);
	}
	/*	//To be rewriten according to directory only
	while((entryPtr = readdir(dp)) != NULL){
		if(entryPtr->d_name == dirname){
				if(entryPtr->d_type == DT_DIR ){
					return deleteDirectory(dirname, path);
				}else{
					return 	deleteFile(dirname, path);
				} 
		}
	}*/
	return 0;
}

/*int main(int argc, char **argv){
	vector<string> vec;
	string currPath;
	currPath = getenv("PWD");
	for(int i=0; i<argc; i++){
		vec.push_back(argv[i]);
	}
	//vec.push_back("delete");
	//vec.push_back("sample");
	//vec.push_back("/");
	//cout<<"Curr Path is: "<<currPath<<endl;
	//cout<<"Path is: "<<homePath<<endl;
	cout<<"Deletion status is: "<<deleteHandler(vec.size(), vec, currPath)<<endl;
	//cout<<"File creation status is: "<<deleteDirHandler(vec.size(), vec, currPath)<<endl;
	return 0;
}*/
