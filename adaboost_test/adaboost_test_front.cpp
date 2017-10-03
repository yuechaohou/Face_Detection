#include "utility.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace std;
using namespace cv;


extern std::string test_data_folder;
extern std::string test_info;

//model
string left_cascade_name = "/home/capstone/adaboost/adaboost_train/left_profile_face_model/cascade.xml";
string front_cascade_name = "/home/capstone/adaboost/adaboost_train/front_profile_face_model/cascade.xml";
string right_cascade_name = "/home/capstone/adaboost/adaboost_train/right_profile_face_model/cascade.xml";

//string positive_file_directory="/home/capstone/adaboost/adaboost_test/new_positive_file_log_left.txt";
//string negative_file_directory="/home/capstone/adaboost/adaboost_test/new_negative_file_log_left.txt";
string output_file_left="/home/capstone/pipeline/AdaBoost_to_CNN/faces_log_front.txt";
CascadeClassifier left_face_cascade;
CascadeClassifier front_face_cascade;
CascadeClassifier right_face_cascade;


bool testOverlap(Rect&, Rect&, int);
void testNextRect(std::vector<Rect>&, Rect&, std::vector<int>&);
void testAllRect(std::vector<Rect>&, std::vector<Rect>&, std::vector<int>&);
void CutRect(std::string image_name, std::vector<Rect>&, Mat*);

unordered_map<string, vector<Rect>> images_info;

//ofstream file_positive;
//ofstream file_negative;
ofstream file_left;

int main( int argc, char** argv )
{
    //file_positive.open(positive_file_directory.c_str());
    //file_negative.open(negative_file_directory.c_str());
    file_left.open(output_file_left.c_str());
    std::vector<string> image;

    if (argc == 1){
        //load the txt file into  image vector<string>
         image=getImageNames("/home/capstone/adaboost/adaboost_sample/data_info_produce_recall/new_pos_info.txt");
        //image=getImageNames("/home/capstone/adaboost/adaboost_sample/new_pos_info.txt");
    }
    else if (argc == 2){
        //Detect one file
        image.push_back(argv[1]);
    }
    else
    {
       printf("Wrong command.");
       return -1;
    }

    cout <<"hhh"<<endl;
	//image_info unordered_map<string, vector<Rect>>& images_info
    ReadImagesInfo("/home/capstone/adaboost/adaboost_sample/data_info_produce_recall/new_pos_info.txt", images_info);
    if( !left_face_cascade.load( left_cascade_name ) ){ printf("--(!)Error loading left face cascade\n"); return -1; };
    if( !front_face_cascade.load( front_cascade_name ) ){ printf("--(!)Error loading front face cascade\n"); return -1; };
    if( !right_face_cascade.load( right_cascade_name ) ){ printf("--(!)Error loading right face cascade\n"); return -1; };

    // cout <<  "image size:" << image.size() << endl;
	for (int num = 0; num < image.size(); num++){//per image in the folder  
        Mat frame;
        Mat frame_gray;
        std::vector<Rect> left_faces;
        vector<Rect> front_faces;
        vector<Rect> right_faces;
            
        //Load Trained Model   
        //Load Image image[num] is a directory
        frame = imread( image[num], 1 );
    	//Preprocess transfer to gray
        cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
        //Detect faces
        //Sliding Windows produced       
        //left_face_cascade.detectMultiScale( /*input file*/frame_gray, /*output file*/ left_faces, /*scaling rate*/1.1, /*more than 2*/4, 0, /*ending size*/Size(frame.size().height/5, frame.size().width/5) , frame.size() );     
	//final frame size 1/10
        front_face_cascade.detectMultiScale( frame_gray, front_faces, 1.1, 4, 0, Size(frame.size().height/10, frame.size().width/10) , frame.size() );  
	//final frame size 1/5
	//front_face_cascade.detectMultiScale( frame_gray, front_faces, 1.1, 4, 0, Size(frame.size().height/5, frame.size().width/5) , frame.size() );      
        //right_face_cascade.detectMultiScale( frame_gray, right_faces, 1.1, 4, 0, Size(frame.size().height/5, frame.size().width/5) , frame.size() );     
        // cout << "after detect face." << endl;
       /* cout<<left_faces.size()<<endl;
        cout<<right_faces.size()<<endl;
        cout<<front_faces.size()<<endl;*/
        vector<Rect> faces;

        //faces.insert(faces.end(), left_faces.begin(), left_faces.end());
        faces.insert(faces.end(), front_faces.begin(), front_faces.end());
        //faces.insert(faces.end(), right_faces.begin(), right_faces.end());
        //combine rectangles------added code
        cout<<"Faces Detected: "<<faces.size()<<endl;
        std::vector<Rect> ResultFaces = {};
        if (!faces.empty())
        {
            ResultFaces.push_back(faces[0]); 
            std::vector<int> weight;
            weight.push_back(1);
            testAllRect(ResultFaces, faces, weight);
            // cout << "after test all rect" << endl;
        }
        //Cut rectangles
       //cout<<"Faces Combined: "<<ResultFaces.size()<<endl;
        CutRect(image[num] ,ResultFaces, &frame); 
    }
   // file_positive.close();
    //file_negative.close();
      file_left.close();
	return 0;
}

void CutRect(std::string image_path, std::vector<Rect>& ResultFaces, Mat* ptr) {
    string image_name = image_path.substr(image_path.find_last_of("/")+1);
    image_name = image_name.substr(0, image_name.find_last_of("."));
     cout <<  "resultfaces size: " << ResultFaces.size() << endl;
    //int positive_count=0;
    //int negative_count=0;
     int count=0;
    for( size_t i = 0; i < ResultFaces.size(); i++ )
    {
        Point top_left( ResultFaces[i].x, ResultFaces[i].y);
        Point bottom_right( ResultFaces[i].x + ResultFaces[i].width, ResultFaces[i].y + ResultFaces[i].height );
        //make sure rect inside original image 
        if((ResultFaces[i].x > 0) && (ResultFaces[i].y > 0) && 
            ((ResultFaces[i].width + ResultFaces[i].x) < (*ptr).size().width) &&
            ((ResultFaces[i].height + ResultFaces[i].y) < (*ptr).size().height)) {
            //cut image
            cv::Mat croppedFaceImage;
            croppedFaceImage = (*ptr)(ResultFaces[i]).clone();
            std::string path="/home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_front/";
            std::string name = image_name + "_" + to_string(count) + ".jpg";
            file_left<<image_path<<endl;
            file_left<<ResultFaces[i].x<<' '<<ResultFaces[i].y<<' '<<ResultFaces[i].width<<' '<<ResultFaces[i].height<<endl;
            //imwrite(path+name,croppedFaceImage);
            //resize to 32*32     
            cv::Mat resized_image;
            resize(croppedFaceImage,resized_image,Size(32,32),0,0,CV_INTER_LINEAR);
            imwrite(path+name,resized_image);
            count++;
            /*if (overlap_bool(ResultFaces[i], images_info[image_name], 90, 0)) {
                path = "/home/capstone/adaboost/adaboost_test/new_positive/";
                std::string name = image_name + "_" + to_string(i) + ".jpg";
                // cout << "writing to " << path << name << endl;
                //cout<<path+name<<endl;
                file_positive<<image_path<<endl;
                file_positive<<ResultFaces[i].x<<' '<<ResultFaces[i].y<<' '<<ResultFaces[i].width<<' '<<ResultFaces[i].height<<endl;
                //resize to 32*32
                //cv::Mat resized_image
                imwrite(path+name, croppedFaceImage);
                positive_count++;
            } else if (!overlap_bool(ResultFaces[i], images_info[image_name], 10, 0)) {
                path = "/home/capstone/adaboost/adaboost_test/new_negative/";
                std::string name = image_name + "_" + to_string(i) + ".jpg";
                // cout << "writing to " << path << name << endl;
                file_negative<<image_path<<endl;
                file_negative<<ResultFaces[i].x<<' '<<ResultFaces[i].y<<' '<<ResultFaces[i].width<<' '<<ResultFaces[i].height<<endl;    
                //resize to 32*32
                imwrite(path+name, croppedFaceImage);
                negative_count++;
            }*/
        }
    }
    cout<<"count:"<<count<<endl;
   // cout<< "positive_image"<<positive_count<<endl;
   // cout<< "negative_image"<<negative_count<<endl;

}

//move the true rect up, down, left, right
// void moveRect(std::vector<Rect>& ResultFaces) {
//     size_t orisize = ResultFaces.size();
//     for(size_t i = 0; i < orisize; i++) {
//         //if(....) {
//             Rect move = ResultFaces[i];
//             move.x = ResultFaces[i].x + ResutFaces[i].width * rand() % 100 / 2000.;
//             ResultFaces.push_back(move);
//             move = ResultFaces[i];
//             move.x = ResultFaces[i].x - ResultFaces[i].width * rand() % 100 / 2000.;
//             ResultFaces.push_back(move);
//             move = ResultFaces[i];
//             move.y = ResultFaces[i].y - ResultFaces[i].height * rand() % 100 / 2000.;
//             ResultFaces.push_back(move);
//             move = ResultFaces[i];
//             move.y = ResultFaces[i].y + ResultFaces[i].height * rand() % 100 / 2000.;
//             ResultFaces.push_back(move);
//          //}
//     }
    
// }

void testAllRect(std::vector<Rect>&  ResultFaces, std::vector<Rect>& faces, std::vector<int>& weight) {
    for(size_t i = 1; i < faces.size(); i++) {
        testNextRect(ResultFaces, faces[i], weight);
    }
}

///////////////////////////////////////////////
//  a-----------------b
//  |                 |
//  d-----------------c
///////////////////////////////////////////////
//test overlap; if overlap, adjust overlapped rect
bool testOverlap(Rect& r1, Rect& r2, int w) {
    int ax = std::max(r1.x, r2.x);
    int ay = std::max(r1.y, r2.y);
    int cx = std::min(r1.x + r1.width, r2.x + r2.width);
    int cy = std::min(r1.y + r1.height, r2.y + r2.height);
    int minArea = std::min(r1.width * r1.height, r2.width * r2.height);

    if((ax <= cx) && (ay <= cy) && (((cy-ay)*(cx-ax)) >= (0.9*minArea))){
        r1.width = (r1.width * w + r2.width)/(w + 1);
        r1.height = (r1.height * w + r2.height)/(w + 1);
        r1.x = (r1.x * w + r2.x)/(w + 1);
        r1.y = (r1.y * w + r2.y)/(w + 1);
        return true;
    }else {
        return false;
    }

}

// if not overlap, add to ResultFaces;
void testNextRect(std::vector<Rect>& ResultFaces, Rect& r1, std::vector<int>& weight) {
/*    for(size_t i = 0; i < ResultFaces.size(); i++) {
        if(testOverlap(ResultFaces[i], r1, weight[i])) {
            weight[i]++;
            return;
        }
    }*/
    ResultFaces.push_back(r1);
    weight.push_back(1);
}
