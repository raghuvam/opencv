
//#include "opencv2/opencv.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
cout << "displaying the image " << argv[1] << endl;

Mat img = imread(argv[1],1);

Mat imdec = imdecode(img,1);
namedWindow("image");

imshow("image",imdec);

return 0;


}



