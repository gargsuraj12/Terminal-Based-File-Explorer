#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

int renameFile(int argc, vector<string> vec, string path){
	if(argc != 3){
		fprintf(stderr, "Incorrect no of arguements..!!");
		return -1;
	}
	cout<<"Src path is: "<<path<<endl;
	int x = chdir((char *)path.c_str());
	cout<<"chdir status = "<<x<<"    ";
	for(auto it : vec){
		cout<<it<<" ";
	}
	int rv = rename((char *)vec[1].c_str(),(char *)vec[2].c_str());
	
	//cout<<rv<<endl;
	return rv;
}

/*int main(int argc, char **argv){
	vector<string> vec;
	for(int i=0; i<argc; i++){
		vec.push_back(argv[i]);
	}
	renameFile(vec.size(), vec);
	
	return 0;
}*/