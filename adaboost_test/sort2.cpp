#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <stdlib.h>
using namespace std;

struct pos{
    int x;
    int y;
    int width;
    int height;
};

void getAns(string image_name, vector<pos>& ans);
bool overlap_bool(pos rectA, pos rectB, int threshold, pos &overlap);
vector<string> getImageNames(string filename);
void sort(vector<pos> overlap, vector<int> count, vector<pos> &result, vector<int> &count_result);
void getImage(map<string,vector<pos> > &my_map, string filename);
void vector_copy(vector<pos> org, vector<pos> & result);

string test_data_folder = "/home/capstone/adaboost/adaboost_sample/";
//string test_data_folder = "/media/zwx/a03a94ae-d453-48cc-9a57-5990509f8d71/wenxuan/Documents/july21/";
string out_file = "./neg_sort.txt";
string input_file;
int topnumber;
map<string, vector<pos> > image_info;

int main(int argc, char* argv[]){
	if(argc !=3){
		//cout<<"the input number is not correct!"<<endl;
		return -1;

	}
	else{
		input_file=argv[1];
		topnumber=atoi(argv[2]);
	}
	getImage(image_info,input_file);
	//vector<string> ImageNames=getImageNames(input_file);
	int i=0;
	map<string,vector<pos> >::iterator it2;
	for(it2=image_info.begin();it2!=image_info.end();it2++){
		//cout<<"inside for i"<<endl;
		vector<pos> neg_pos;
		vector_copy(it2->second, neg_pos);
		//getAns(ImageNames[i], neg_pos);
		//cout<<"what about here1"<<endl;
		int m, n;
		vector<pos> overlap;
		vector<int> overlap_count;
		vector<int> if_group;
		int c=0;
		//cout<<"what about here2"<<endl;
		while(c<neg_pos.size()){
			c++;
			int a=0;
			if_group.push_back(a);
		}	
		//cout<<"what about here3"<<endl;
		for(m=0;m<neg_pos.size();m++){
			//cout<<"m="<<m;
			if(if_group[m]!=0) continue;
			int flag=0;
			if(overlap.size()!=0){
				for(int j=0;j<overlap.size();j++){
				   //cout<<" j="<<j;
				   pos tmp;
				   int result=overlap_bool(neg_pos[m],overlap[j],70, tmp);
				   if(result){
					overlap_count[j]++;
					flag=1;
					if_group[m]=j+1;
					break;
				   }
				}
			}
			if(flag){
				//cout<<endl;
				continue;
			}
			for(n=m+1;n<neg_pos.size();n++){
			       //cout<<" n="<<n<<endl;
			       if(if_group[n]!=0) continue;
			       pos tmp2;
			       int result2=overlap_bool(neg_pos[m],neg_pos[n],70, tmp2);
			       if(result2){
					overlap.push_back(tmp2);
					overlap_count.push_back(2);
					if_group[m]=overlap.size();
					if_group[n]=overlap.size();
					break;
			       }
			}
		}
		//cout<<"before sort"<<endl;
		for(int ss=0;ss<overlap.size();ss++){
			//cout<<overlap[ss].x<<" "<<overlap[ss].y<<" "<<overlap[ss].width<<" "<<overlap[ss].height<<" ";
			//cout<<overlap_count[ss]<<endl;	
		}
		vector<pos> sort_result;
		vector<int> count_result;
		sort(overlap, overlap_count,sort_result,count_result);
		//cout<<"after sort"<<endl;
		for(int ss=0;ss<sort_result.size();ss++){
			cout<<it2->first<<" 1 ";
			cout<<sort_result[ss].x<<" "<<sort_result[ss].y<<" "<<sort_result[ss].width<<" "<<sort_result[ss].height<<endl;
			//cout<<count_result[ss]<<endl;	
		}	
	}
	return 0;	
}


void vector_copy(vector<pos> org, vector<pos> & result){
	       for(int i=0;i<org.size();i++){
		   result.push_back(org[i]);
	       }
}

void sort(vector<pos> overlap, vector<int> count, vector<pos> &result, vector<int> &count_result){
	for(int j=0;j<topnumber;j++){
		int max_index=0;
		if(count.size()==0) break;
		for(int i=1; i<count.size();i++){
			if(count[i]>count[max_index]) max_index=i;
		}
		if(count[max_index]<10) break;
		else{
			vector<pos>::iterator itera=overlap.begin()+max_index;
			vector<int>::iterator iterb=count.begin()+max_index;
			result.push_back(*itera);
			count_result.push_back(*iterb);
			overlap.erase(itera);
			count.erase(iterb);
		}
	}
	return;	
}



/* overlap_bool
 * Compare rectangle "rectA" with every element in rectangle vector "answer".
 *  If the overlap area over the original area of "rectA" is larger than 
 * "threshold" in percentage, return 1, return 0 otherwise.
 * 
 * percentage_over_itself = 1: percentage is calculated with the area of
 * rectA as denominator(for recall rate). 
 * percentage_over_itself = 0: the area of the answer is the denominator
 * (for pos-neg labels).
 */
bool overlap_bool(pos rectA, pos rectB, int threshold, pos &overlap){
        int x1,y1,x2,y2;
	//cout<<"rectA "<<rectA.x<<" "<<rectA.y<<" "<<rectA.width<<" "<<rectA.height<<endl;
	//cout<<"rectB "<<rectB.x<<" "<<rectB.y<<" "<<rectB.width<<" "<<rectB.height<<endl;
        x1 = max(rectA.x,rectB.x);
        x2 = min(rectA.x+rectA.width,rectB.x+rectB.width);
        y1 = max(rectA.y,rectB.y);
        y2 = min(rectA.y+rectA.height,rectB.y+rectB.height);
	//cout<<"x1="<<x1<<" x2="<<x2<<" y1="<<y1<<" y2="<<y2<<endl;
        if ((x2>x1) && (y2>y1)) { 
	   float over=min(100*(x2-x1)*(y2-y1)/(rectA.width * rectA.height),100*(x2-x1)*(y2-y1)/(rectB.width * rectB.height));
	   //cout<<over<<endl;
           if( min(100*(x2-x1)*(y2-y1)/(rectA.width * rectA.height),100*(x2-x1)*(y2-y1)/(rectB.width * rectB.height))>threshold){
	     overlap.x=x1;
	     overlap.y=y1;
	     overlap.width=x2-x1;
	     overlap.height=y2-y1;
	     return 1;
	    }
        }
    return 0;
}

// void draw_rects(Mat *frame, vector<Rect> faces, int color, int thickness, int lineType){
//     for( size_t i = 0; i < faces.size(); i++ )
//         {
//             Point top_left( faces[i].x, faces[i].y);
//             Point bottom_right( faces[i].x + faces[i].width, faces[i].y + faces[i].height );
//             rectangle(*frame, top_left, bottom_right, color, thickness, lineType);
//             //cout << faces[i].x <<" "<<faces[i].y<<" "<< faces[i].x+faces[i].width<<" "<< faces[i].y+faces[i].height<<"\n"; 
//         }
// }
   
void getAns (string image_name, vector<pos>& Ans){
	//vector<pos> Ans;
	//Read in real positions
	ifstream filestream;
	string filename = input_file;
	filestream.open(filename.c_str());
	if ( !filestream.is_open()){
		cout << "open failed1" << endl; 
		return;
	}
	string line;
	string word;
	int x,y,w,h;
	while (getline(filestream, line)) {
		istringstream istr;
		istr.str(line);
		string newname;
		istr>>newname;
		if (newname == image_name) {
			//getline(filestream, line);
			//cout<<newname<<endl;
			getline(filestream, line);
			istringstream iss(line);
			iss >> x;
			iss >> y;
			iss >> w;
			iss >> h;
			//cout << "x=" << x <<  " y=" << y << " w" << w << " h=" << h <<"\n";
			pos tmp;
			tmp.x=x;
			tmp.y=y;
			tmp.width=w;
			tmp.height=h;
			Ans.push_back(tmp);	
		}
	}
	filestream.close();
	//cout << Ans[0].x <<Ans[0].y<< Ans[0].width<< Ans[0].height<<"\n"; 
	return;
}

     void getImage(map<string,vector<pos> > &my_map, string filename){
          ifstream filestream;
          filestream.open(filename.c_str());
	  if ( !filestream.is_open()){
        	cout << "open failed" << endl;
        	cout << "in getImageNames, " << filename << endl;
                return;
    	  }
	  string line;
	  while (getline(filestream, line)) {
        	istringstream iss(line);
		string word;
		int x,y,w,h;
		iss >> word; 
		getline(filestream, line);
		istringstream isss(line);
		isss >> x;
		isss >> y;
		isss >> w;
		isss >> h;
		//cout << "x=" << x <<  " y=" << y << " w" << w << " h=" << h <<"\n";
		pos tmp;
		tmp.x=x;
		tmp.y=y;
		tmp.width=w;
		tmp.height=h;
		map<string,vector<pos> >:: iterator it=my_map.find(word);
        	if(it==my_map.end()){
		    vector<pos> new_pos;
		    new_pos.push_back(tmp);
		    my_map.insert(make_pair(word,new_pos));
		}
		else{
		   (it->second).push_back(tmp);
		}	
   	  }
	  return;  
      }


 vector<string> getImageNames (string filename){
    vector<string> Ans;
    ifstream filestream;
    filestream.open(filename.c_str());
    if ( !filestream.is_open()){
        cout << "open failed" << endl;
        cout << "in getImageNames, " << filename << endl;
        return Ans;
    }
    string line;
    string word;
    while (getline(filestream, line)) {
        istringstream iss(line);
        iss >> word;   
	const string t=word;
	vector<string>:: iterator r;
	int flag=0;
	for(r=Ans.begin();r!=Ans.end();r++){
		if(!strcmp((*r).c_str(),word.c_str())){
			flag=1;
			break;
		}
	}
	if(flag){
		getline(filestream,line);
		continue;
	}
	//cout<<word<<endl;
	Ans.push_back(word);
	getline(filestream,line);
/*        cout<<word<<endl;
        ifstream f(word);
        if (f.good()) *///if the file exists
    }
    filestream.close();
    return Ans;
}
