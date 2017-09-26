#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

string test_info;
string output_file;

struct Rect{
	int x;
	int y;
	int width;
	int height;

	Rect(){
		x=y=width=height=0;
	}

	Rect(int a, int b, int c, int d){
		this->x=a;
		this->y=b;
		this->width=c;
		this->height=d;
	}

	Rect& operator=(const Rect& b){
		this->x=b.x;
		this->y=b.y;
		this->width=b.width;
		this->height=b.height;
	}

	Rect(const Rect& b){
		this->x=b.x;
		this->y=b.y;
		this->width=b.width;
		this->height=b.height;
	}
};

struct frame_info{
		string name;
        Rect frame;
        int count;

        frame_info(int a, Rect b, string c){
                this -> count = a;
                this -> frame = b;
                this -> name = c;
        }
};

typedef vector< struct frame_info > uneg;


vector<string> getImageNames ( void );
vector<Rect> getAns(string image_name);
vector<frame_info> sorting(vector<frame_info> &answer);
void overlap_bool(vector<int>& result, Rect rectA, Rect rectB, int threshold, int i, int j );
vector<int> counting (vector<Rect>& counted);

int main( int argc, char** argv )
{
    //typedef unordered_map<frame_info,int> uneg;
    vector<string> image;
    string org_image;
    if (argc == 2){
        test_info = argv[1];
        image=getImageNames();
    }
    else if ( argc != 2 )
    {
           printf("Wrong command.");
           return -1;
    }

    for (unsigned int num = 0; num < image.size(); num++){//per image in the folder     
                        vector<Rect> neg_ans;
                        vector<int> counted;
                        uneg final_neg, final;
                        neg_ans = getAns(image[num]);
                        counted = counting(neg_ans);
                        for (unsigned int j=0; j < counted.size(); j++){
                            if(counted[j] > 10){
                            	struct frame_info tmp(counted[j], neg_ans[j], image[num]);
                                final_neg.push_back(tmp);
                               	}
                	 } 
                	final=sorting(final_neg);
                	int k=0;
 	 		 		for(uneg::iterator iter = final.begin(); iter != final.end(); iter++)  
    		 	 	 	{  
    		 	 	 		k++;
    		 	 	 		if(k==10) break;
        	 	 	 	 	cout<< iter->name<<endl;
        	 	 	 	 	cout<< iter->frame.x<<"\t"<< iter->frame.y<<"\t"<< iter->frame.width<<"\t"<< iter->frame.height<<endl;  
     	 	 	 	 	}   
    }	             
	return 0;
}
    
vector<Rect> getAns (string image_name){
	vector<Rect> Ans;
	//Read in real positions
	ifstream filestream;
	string filename = test_info;
	filestream.open(filename.c_str());
	if ( !filestream.is_open()){
		cout << "open failed" << endl; 
		exit(1);
	}
	string line;
	string word;
	int x,y,w,h;
	while (getline(filestream, line)) {
		if (line == image_name) {
			getline(filestream, line);
			istringstream iss(line);
			iss >> x;
			iss >> y;
			iss >> w;
			iss >> h;
			cout << "x=" << x <<  " y=" << y << " x2=" << x+w << " y2=" << y+h <<"\n";
			Ans.push_back(Rect(x,y,w,h));	
		}
	}
	filestream.close();
	//cout << Ans[0].x <<Ans[0].y<< Ans[0].width<< Ans[0].height<<"\n"; 
	return Ans;
}

vector<int> counting (vector<Rect>& counted){
	vector<int> result;
	for(unsigned int i=0; i<counted.size();i++){
		result.push_back(0);
	}
	for(unsigned int i=0; i<counted.size();i++){
		for(unsigned int j=1; j<counted.size();j++){
			overlap_bool(result, counted[i], counted[j], 80, i, j);
		}
	}  

	return result;
}

   
vector<string> getImageNames (void){
	vector<string> Ans;
	ifstream filestream;
	string filename = test_info;
	filestream.open(filename.c_str());
	if ( !filestream.is_open()){
		cout << "open failed" << endl;
		exit(1);
	}
	string line;
	string word;
	while (getline(filestream, line)) {
		Ans.push_back(line);
		getline(filestream, line);
	}
	filestream.close();
	return Ans;
}


void overlap_bool(vector<int>& result, Rect rectA, Rect rectB, int threshold, int i, int j){
	int x1,y1,x2,y2,overlap,_overlap;
	x1 = max(rectA.x,rectB.x);
	x2 = min(rectA.x+rectA.width,rectB.x+rectB.width);
	y1 = max(rectA.y,rectB.y);
	y2 = min(rectA.y+rectA.height,rectB.y+rectB.height);
	if ((x2>x1) && (y2>y1)) { 
		overlap = 100*(x2-x1)*(y2-y1)/(rectA.width*rectA.height);
		if (overlap > threshold) result[i]++;
		_overlap = 100*(x2-x1)*(y2-y1)/(rectB.width*rectB.height);
		if (_overlap > threshold) result[j]++;
	}
}


vector<frame_info> sorting(vector<frame_info> &answer){
	int max[10];
	int index[10];
	vector<frame_info> ans;
	for (int i=0;i<10;i++){
		max[i]=index[i]=0;
	}
	for(unsigned i=0; i<answer.size(); i++){
		for (int j=0;j<10;j++){
			if(answer[i].count > max[j]){
				for(int k=9;k>j;k++){
					max[k]=max[k-1];
					index[k]=index[k-1];
				}
				max[j]=answer[i].count;
				index[j]=i;
				break;
			}
		}
	}
	for (int i=0;i<10;i++){
		ans.push_back(answer[index[i]]);
	}

	return ans;
}