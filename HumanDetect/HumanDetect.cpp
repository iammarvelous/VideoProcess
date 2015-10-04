#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

fstream detectout;


vector<Rect> HumanBodyDetect(Mat img)
{
    // 1. Define Hog Object
    HOGDescriptor hog; // Use default mode
    // 2. Set SVM Classifier
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());   // Use default detector
    // 3. Detect on image
    vector<Rect> regions;
    hog.detectMultiScale(img, regions, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 1);
    return regions;
}

void WriteFile(vector<Rect> regions, int countframe)
{
    if (detectout.is_open())
    {
        detectout << countframe;
        for (size_t i=0; i < regions.size(); i++)
        {
            detectout << "\t" << regions[i].height
                      << "\t" << regions[i].width
                      << "\t" << regions[i].x
                      << "\t" << regions[i].y; 
            //rectangle(frame,regions[i],Scalar(0, 0, 255),2);
        }
        detectout << "\n";

    }
    else
    {
        cerr << "Error: Cannot open file!!!" << endl;
    }

}

int main()
{
    detectout.open("detectout.txt",ios::out);
    VideoCapture cap("/Users/yzl5709/Desktop/S09E01.mp4");
    if (!cap.isOpened())
    {
        cout << "!!! Failed to open file!" << endl;
        return -1;
    }
    
    Mat frame;
    int countframe = 0;
    while(1)
    {
        if (!cap.read(frame))
            break;
        ++countframe;
        if (frame.empty())
        {
            cerr << "read frame failed"<< endl;
        }
        WriteFile(HumanBodyDetect(frame), countframe);
        
    }
    detectout.close();
    return 0;
}
