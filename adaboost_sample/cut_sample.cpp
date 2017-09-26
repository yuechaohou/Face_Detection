#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>
#include <string>
#include <algorithm>

using namespace std;
using namespace cv;

int CropImage(string image_path, Rect& rect, string store_path, int num) 
{  
    strstream ss;
    int tmp=num;
    string s;
    ss << tmp;
    ss >> s;
    string image_name = image_path.substr(image_path.find_last_of("/")+1);
    image_name = image_name.substr(0, image_name.find_last_of("."));
Mat image ;

   // cout<<"a"<<endl;
image= imread(image_path, 1);
//cout<<"b"<<endl;

    
    int ori_x = rect.x;
    int ori_y = rect.y;
    rect.width = std::min(rect.width, image.size().width - rect.x);
    rect.height = std::min(rect.height, image.size().height - rect.y);
    if (rect.width<0||rect.height<0) return 0;
//cout<<"c"<<endl;
    Mat crop_image ;
try
{
    crop_image= image(rect).clone();
    }
catch( cv::Exception& e )
{
    const char* err_msg = e.what();
    cout << "exception caught: " << image_path<< std::endl;
}
//cout<<"d"<<endl;
    imwrite(store_path + image_name + "_nr"+"_"+s+".jpg", crop_image);

    cout << image_name <<"nr"<< "_"<<s<<".jpg" << " 1 0 0 "<< rect.width << " "<< rect.height << endl;

    ss.clear();
    tmp++;
    /*ss << tmp;
    ss >> s;  
    rect.x = ori_x * 0.95;
    crop_image = image(rect).clone();
    imwrite(store_path + image_name + "_nr"+"_"+s+".jpg", crop_image);
    cout << image_name <<"nr"<< "_"<<s<<".jpg" << " 1 0 0 "<< rect.width << " "<< rect.height << endl;

    ss.clear();
    tmp++;
    ss << tmp;
    ss >> s;  
    rect.x = ori_x;
    rect.y = ori_y * 0.95;
    crop_image = image(rect).clone();
    imwrite(store_path + image_name + "_nr"+"_"+s+".jpg", crop_image);
cout << image_name <<"nr"<< "_"<<s<<".jpg" << " 1 0 0 "<< rect.width << " "<< rect.height << endl;

    ss.clear();
    tmp++;
    ss << tmp;
    ss >> s;  
    rect.y = ori_y;
    rect.x = std::min((int)(ori_x * 1.05), image.size().width - rect.width);
    crop_image = image(rect).clone();
    imwrite(store_path + image_name + "_nr"+"_"+s+".jpg", crop_image);
cout << image_name <<"nr"<< "_"<<s<<".jpg" << " 1 0 0 "<< rect.width << " "<< rect.height << endl;

    ss.clear();
    tmp++;
    ss << tmp;
    ss >> s;  
    rect.x = ori_x;
    rect.y = std::min((int)(ori_y * 1.05), image.size().height - rect.height);
    //cout << image.size().width << ' ' << image.size().height << ' ' << rect.x << ' ' << rect.y << ' ' << rect.width << ' ' << rect.height << endl;
    crop_image = image(rect).clone();
    imwrite(store_path + image_name + "_nr"+"_"+s+".jpg", crop_image);
cout << image_name <<"nr"<< "_"<<s<<".jpg" << " 1 0 0 "<< rect.width << " "<< rect.height << endl;

    tmp++;*/
    return tmp;
}


int main(int argc, char** argv) 
{
    // use: ./exe file_name store_folder_path > store_file_name
    if (argc != 3)
    {
       cout << "Wrong command." << endl;
       exit(1);
    }
    ifstream filestream;
    filestream.open(argv[1]);
    if ( !filestream.is_open()){
        cout << "open failed" << endl;
        cout << "in create pos samples, " << argv[1] << endl;
        exit(1);
    }
    string line;
    string image_last="ll";
    int count=0;
    while (getline(filestream, line)) 
    {
        string image_path;
        
        int num;
        istringstream iss(line);
        iss>>image_path>>num;
        //cout <<image_path<<endl;
        for(int i=0;i<num;i++){
            Rect rect;
            iss >> rect.x >> rect.y >> rect.width >> rect.height;
            //cout<<rect.height<<endl;
            if (rect.x>0&&rect.y>0&&rect.width>0&&rect.height>0)
            CropImage(image_path, rect, string(argv[2]),5*i);
        }


        /*if(image_path!=image_last){
                image_last=image_path;
                count =0;
                cout<<"b"<<endl;
                count =CropImage(image_path, rect, string(argv[2]), count);
        }
        else{
            cout<<"c"<<endl;
                count =CropImage(image_path, rect, string(argv[2]), count);
                cout<<"d"<<endl;
        }*/

    }
    filestream.close();
}

