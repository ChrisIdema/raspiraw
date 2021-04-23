#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

char window_name[] = "opencv_raspiraw";

static Mat preview_img;


bool viewer_refresh()
{    
    if ((int)cv::getWindowProperty(window_name,cv::WND_PROP_AUTOSIZE)==-1){
        return true;
    }


    // tick=cv::getTickCount()-tick;
    // float f = tick*1E-6f;
    // tick=cv::getTickCount();

    // cv::putText(preview_img, cv::format("ms: %0.1f", f),cv::Point(20,20),cv::FONT_HERSHEY_SIMPLEX,0.6, cv::Scalar(255, 255, 255));

    imshow(window_name, preview_img);
    char esc = cv::waitKey(1);
    if(esc == 27){
        return true;
    }

    return false;
}

void opencv_raw_update(uint8_t* data,size_t len){
    //printf("%d\n",len);


    Mat test = Mat(Size(640,480), CV_8UC1,data);

    //memcpy(preview_img.data,data,len);

    cvtColor(test, preview_img, COLOR_BayerBG2BGR);

    viewer_refresh();
}

void init_viewer(){

    // preview_img=Mat(480,640,CV_8UC3);
    preview_img = Mat::zeros(480,640, CV_8UC3);
    //preview_img = Mat::zeros(320,400, CV_8UC3);
    

    namedWindow(window_name, WINDOW_AUTOSIZE); 
    moveWindow(window_name,0,0);

    viewer_refresh();

}
