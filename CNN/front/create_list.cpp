#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
using namespace std;

string positive_list="/home/capstone/cnn_train_models/train_front/tmp_pos.txt";
string negative_list="/home/capstone/cnn_train_models/train_front/tmp_neg.txt";
string train_list="/home/capstone/cnn_train_models/train_front/train3.txt";
ifstream read_pos;
ifstream read_neg;
ofstream  write_train;
int main(int argc, char** argv){
     srand((unsigned)time(NULL));
     int iteration;
     int pos_percent;
     if(argc!=3){
	cout<<"./create_list iteration_time positive_number"<<endl;
	return -1;
     }
     else if(argc==3){
	iteration=atoi(argv[1]);
	pos_percent=atoi(argv[2]);
     }
     int neg_percent=100-pos_percent;
     read_pos.open(positive_list.c_str());
     read_neg.open(negative_list.c_str());
     write_train.open(train_list.c_str()); 
     for(int i=0;i<iteration;i++){
	vector<string> tmp;
	string line1;
	string line2;
	for(int j=0;j<pos_percent;j++){
		getline(read_pos,line1);
		tmp.push_back(line1);
		//write_train<<line1<<endl;	
	}
	for(int m=0;m<neg_percent;m++){
		getline(read_neg,line2);
		//write_train<<line2<<endl;
		tmp.push_back(line2);	
	}
	for(int t=0;t<50;t++){
	      int ran1=rand()%25;
	      int ran2=rand()%75+25;
	      string tmpstr;
	      tmpstr=tmp[ran1];
	      tmp[ran1]=tmp[ran2];
	      tmp[ran2]=tmpstr;
	}
	for(int z=0;z<tmp.size();z++){
		write_train<<tmp[z]<<endl;
	}
     }
    read_pos.close();
    read_neg.close();
    write_train.close();
   return 0;
}


