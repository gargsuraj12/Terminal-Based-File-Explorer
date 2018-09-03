/*
Name: Suraj Garg
Roll No: 2018202003
*/

#include "searchUtility.h"

extern int winLen,iCol,iRow;
vector<string> fileVec;

int searchFile(int argc, string filetosearch, string currDir){
	if(argc != 2){
		printf("\033[%d;%dH",winLen-2,iCol);
		printf("Incorrect arguements..!!");
		return -1;
	}
	int x = chdir((char *)currDir.c_str());
	if(x != 0){
		printf("\033[%d;%dH",winLen-2,iCol);
		printf("Unable to goto %s\n",(char *)currDir.c_str());
		return -1;
	}
	DIR *dp;
	struct dirent *entryPtr;
	struct stat fileStat;
	string nextPath,found;
	
	dp = opendir((const char *) (char *)currDir.c_str());
	if(dp == NULL){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr, "Unable to open directory '%s'", (char *)currDir.c_str());
		return -1;
	}
	
	while((entryPtr = readdir(dp)) != NULL){
		stat(entryPtr->d_name, &fileStat);
		if(entryPtr->d_type == DT_DIR){	//if current dir entry is a directory then recurse
			if(strcmp(entryPtr->d_name,"..")!=0 && strcmp(entryPtr->d_name, ".")!=0){
				nextPath.append(currDir);
				nextPath.append("/");
				nextPath.append(entryPtr->d_name);
				//cout<<"Next path to enter is: "<<nextPath<<endl;
				searchFile(argc, filetosearch, nextPath);
				nextPath.clear();
			}
		}else{
			if(strcmp(entryPtr->d_name, (char *)filetosearch.c_str()) ==0){
				//cout<<"File found @ "<<currDir<<endl;
				fileVec.push_back(currDir);
			}
		}
	}
	return 0;	
}

vector<string> searchHandler (int argc, vector<string> argv, string currDir){
	vector<string> vec;
	int x = searchFile(argc, argv[1], currDir);
	if(x != 0){
		printf("\033[%d;%dH",winLen-2,iCol);
		fprintf(stderr,"Unable to locate file..");
		return vec;
	}
	return fileVec;
} 

/*int main(int argc, char **argv){
	vector<string> vec;
	for(int i = 0; i<argc; i++){
		vec.push_back(argv[i]);
	}
	searchHandler(argc, vec, "/home/suraj/Desktop");
	//string file = argv[1];
	//searchFile(argc, file, "/home/suraj/Desktop");
	cout<<"File found @ :"<<endl;
	for(auto it : fileVec){
		cout<<it<<endl;
	}
	return 0;
}*/