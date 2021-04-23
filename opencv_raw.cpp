#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

char window_name[] = "opencv_raspiraw";

extern "C" void init_viewer(){
    // if (settings->previewType==0)
    //     return;
	// frame=Mat(settings->small_h,settings->small_w,CV_8UC3);
	// frameWide=Mat(settings->wide_h,settings->wide_w,CV_8UC3);

    // imgPreview=Mat(settings->small_h*settings->previewSize, settings->small_w*settings->previewSize, CV_8UC3);
    // imgPreviewWide=Mat(settings->wide_h*settings->previewSize, settings->wide_h*settings->previewSize, CV_8UC3);
    // if (settings->previewType==3) {
    //     imgWindow=Mat(settings->small_h, settings->small_w*settings->previewSize, CV_8UC3);
    // } else {
    //     imgWindow=Mat(settings->small_h*settings->previewSize, settings->small_w*settings->previewSize, CV_8UC3);
    // }

    namedWindow(window_name, WINDOW_AUTOSIZE); 
    moveWindow(window_name,0,0);

}
