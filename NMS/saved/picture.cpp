#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;
using namespace cv;

typedef pair<double, double> point;
String test_data_folder = "TestData";
String test_info = "positive_file_log.txt";

std::vector<Rect> overall(std::vector<Rect> faces);
std::vector<String> getImageNames (void);
std::vector<Rect> getAns(String image_name);
void draw_rects(Mat *frame, std::vector<Rect> faces, int color, int thickness, int lineType);
double power(double a);

int main( int argc, char** argv )
{
    std::vector<String> image;
	
    if (argc == 1){
	//Scan the folder
	image=getImageNames();
    }
    else if ( argc != 1 )
    {
	   printf("Wrong command.");
    	   return -1;
    }
	
	for (unsigned int num = 0; num < image.size(); num++){//per image in the folder	
		//Load Image
		Mat frame;
		Mat frame_gray;
		frame = imread( image[num], 1 );
		cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
		equalizeHist( frame_gray, frame_gray );
		if ( frame.data ){
			std::vector<Rect> faces_ans;
			std::vector<Rect> final_face;
			faces_ans = getAns(image[num]);
			Mat tmpp = imread( image[num], 1 );
			cvtColor( tmpp, frame_gray, COLOR_BGR2GRAY );
			Mat * temp = &tmpp;
			draw_rects(temp, faces_ans, 1,1,0);
			imwrite("sample.jpg", tmpp); 
			final_face = overall(faces_ans);
			Mat * tmp = &frame;
			draw_rects(tmp, final_face, 1,1,0);
		}
		imwrite("OK.jpg", frame ); 
	}
	
	waitKey(0);
	return 0;
}
    
std::vector<Rect> getAns (String image_name){
	std::vector<Rect> Ans;
	//Read in real positions
	ifstream filestream;
	string filename = test_info;
	filestream.open(filename.c_str());
	if ( !filestream.is_open()){
		cout << "open failed1" << endl; 
		exit(1);
	}
	std::string line;
	std::string word;
	int x,y,w,h;
	while (getline(filestream, line)) {
		if (line == image_name) {
			getline(filestream, line);
			istringstream iss(line);
			iss >> x;
			iss >> y;
			iss >> w;
			iss >> h;
			//cout << "x=" << x <<  " y=" << y << " x2=" << x+w << " y2=" << y+h <<"\n";
			Ans.push_back(Rect(x,y,w,h));	
		}
	}
	filestream.close();
	//cout << Ans[0].x <<Ans[0].y<< Ans[0].width<< Ans[0].height<<"\n"; 
	return Ans;
}

   
std::vector<String> getImageNames (void){
	std::vector<String> Ans;

	ifstream filestream;
	string filename = test_info;
	filestream.open(filename.c_str());
	if ( !filestream.is_open()){
		cout << "open failed" << endl;
		exit(1);
	}
	std::string line;
	std::string word;
	while (getline(filestream, line)) {
		Ans.push_back(line);
		getline(filestream, line);
	}
	filestream.close();
	return Ans;
}

void draw_rects(Mat *frame, std::vector<Rect> faces, int color, int thickness, int lineType){
		for (size_t i=0; i< faces.size(); i++){
			Point top_left( faces[i].x, faces[i].y);
			Point bottom_right( faces[i].x + faces[i].width, faces[i].y + faces[i].height );
			rectangle(*frame, top_left, bottom_right, color, thickness, lineType);
			//cout << faces[i].x <<" "<<faces[i].y<<" "<< faces[i].x+faces[i].width<<" "<< faces[i].y+faces[i].height<<"\n"; 
		}
}

std::vector<Rect> overall(std::vector<Rect> faces){
	std::vector<point> mid;
	std::vector<bool> mark;
	std::vector<int> type;
	vector<Rect> Ans;
	int a,b;
	for (size_t i=0; i< faces.size(); i++){
		mid.push_back(make_pair(faces[i].x+faces[i].width/2, faces[i].y+faces[i].height/2));	
		mark.push_back(false);
		type.push_back(0);
	}
	int i=0;
	int j=i+1;
	int style=1;
	int N=mid.size();
	while(i<N){
		if(mark[i]){
			i++;
			j=i+1;
		}
		else{
			next:
			if(j==N){
				Rect sum=Rect(0.0,0.0,0.0,0.0);
				double num=0;
				mark[i]=true;
				type[i]=style;
				for(size_t k=i; k<N; k++){
					if(mark[k] && (type[k]==style)){
						sum=Rect(sum.x+faces[k].x, sum.y+faces[k].y, sum.width+faces[k].width, sum.height+faces[k].height);
						num++;
					}
					//Ans.push_back(Rect((int)(sum.x /num), (int)(sum.y /num), (int)(sum.width /num), (int)(sum.height /num)));
				}
				//mark[i]=true;
				//cout << "write" << "\n";
				Ans.push_back(Rect(sum.x/num, sum.y/num, sum.width/num, sum.height/num));
				style++;
			}
			else{
				//cout<<"i:"<< i <<"\n";
				//cout<<"j:"<< j <<"\n";
				if(mark[j]){
					j++;
					goto next;
				}
				else{
					//cout<<"j:"<<j<< "\n";
					if((power((mid[i].first-mid[j].first))+power(mid[i].second-mid[j].second))<=90000.0){
						mark[j]=true;
						type[j]=style;
					}
					j++;
					goto next;
				}
			}		
		}
	}
	return Ans;
}

double power(double a){
	return (a*a);
}
