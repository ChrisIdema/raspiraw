#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <fstream>

using namespace cv;

char window_name[] = "opencv_raspiraw";

static Mat preview_img;

//  ""./raspiraw -t 30000 --nopreview --processing_yuv -md 7 -g 100 --fps 90"
//this gets 

bool viewer_refresh()
{    
    if ((int)cv::getWindowProperty(window_name,cv::WND_PROP_AUTOSIZE)==-1){
        return true;
    }

    static int64 tick_old=0;
    auto tick=cv::getTickCount();
    float f = (tick-tick_old)*1E-6f;
    tick_old=tick;

    cv::putText(preview_img, cv::format("ms: %5.1f", f),cv::Point(20,20),cv::FONT_HERSHEY_SIMPLEX,0.6, cv::Scalar(0, 255, 0),2);

    imshow(window_name, preview_img);
    char esc = cv::waitKey(1);
    if(esc == 27){
        return true;
    }

    return false;
}

void opencv_raw_update(uint8_t* data,size_t len){
    //printf("%d\n",len);

    // memcpy(preview_img.data,data,len);
    
    // static int counter = 0;

    // if(counter<10){
    //     counter++;
    // }
    // else if(counter==10){
    //     counter++;
    // }
    // else{
    
    //     std::ofstream outfile;
    //     outfile.open("raw.bin", std::ios::binary | std::ios::out);
    //     outfile.write((const char*)data,len);
    // }


    //Mat input = Mat(Size(320,240), CV_8UC3,data);
    //Mat input = Mat::zeros(480,320, CV_8UC3);
    //memcpy(input.data,data,len);

    //cvtColor(input, preview_img, COLOR_BayerBG2BGR);

    //cvtColor(input, preview_img, COLOR_YUV2BGR);

    // BGR input:
    // Mat bgr =Mat(480,640,CV_8UC3,data);    
    // resize(bgr, preview_img,Size(320,240),0,0,INTER_NEAREST);

    // // YUV_422 input mode 7:
    // Mat yuv =Mat(720,640,CV_8UC1,data);
    // Mat bgr =Mat(480,640,CV_8UC3);
    // cvtColor(yuv, bgr, COLOR_YUV2BGR_I420);
    

    // YUV_422 input mode 5:
    Mat yuv =Mat(1104,1312,CV_8UC1,data);
    Mat bgr =Mat(736,1312,CV_8UC3);
    cvtColor(yuv, bgr, COLOR_YUV2BGR_I420);
    
    resize(bgr, preview_img,Size(320,240),0,0,INTER_NEAREST);

    viewer_refresh();
}

void init_viewer(){

    preview_img=Mat(240,320,CV_8UC3);
    //preview_img = Mat::zeros(480,640, CV_8UC3);

    

    namedWindow(window_name, WINDOW_AUTOSIZE); 
    moveWindow(window_name,0,0);

    viewer_refresh();

}
