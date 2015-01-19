#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define SAT(c) \
   if (c & (~255)) { if (c < 0) c = 0; else c = 255; }



using namespace std;
using namespace cv;

Mat yuv2rgb(char filename[]);

int height =720;
int width = 1280;

//canny edge detection variables
int lowThreshold = 35;
int ratio = 3;
int kernel_size =3;

cv::Mat cannyEdgeDetector(cv::Mat& imgEnc)
{
cv::Mat imgEdges,imgGrey,imgResized;

cv::cvtColor( imgEnc, imgGrey, CV_RGB2GRAY );

cv::blur( imgGrey, imgEdges, Size(3,3));

cv::Canny( imgEdges, imgEdges, lowThreshold, lowThreshold*ratio, kernel_size);

return imgEdges;
}



int main(int argc,char** argv)
{
cout << "displaying the image " << argv[1] << endl;



namedWindow("image",WINDOW_AUTOSIZE);
namedWindow("edges",WINDOW_AUTOSIZE);

Mat image = yuv2rgb(argv[1]);

imshow("image",image);
imshow("edges",cannyEdgeDetector(image));


cv::waitKey(0);

return 0;

}

Mat yuv2rgb(char filename[])
{

uint8_t *src = (uint8_t *)malloc(sizeof(uint8_t *)*height*width*2);
uint8_t *dst = (uint8_t *)malloc(sizeof(uint8_t *)*height*width*3);

FILE *stream;

stream = fopen(filename,"r");
fread(src,height*width*2,1,stream);

fclose(stream);
fflush(stream);

Mat image(720,1280,CV_8UC3);

////
   uint8_t *s, *d;
   int l, c;
   int r, g, b, cr, cg, cb, y1, y2;
   int h=0;
   int w=0;
   l = height;

   s = src;
   d = dst;
   while (l--) {
  	 c = width >> 1;
      while (c--) {
         y1 = *s++;
         cb = ((*s - 128) * 454) >> 8;
         cg = (*s++ - 128) * 88;
         y2 = *s++;
         cr = ((*s - 128) * 359) >> 8;
         cg = (cg + (*s++ - 128) * 183) >> 8;

         r = y1 + cr;
         b = y1 + cb;
         g = y1 - cg;
         SAT(r);
         SAT(g);
         SAT(b);

image.at<cv::Vec3b>(h,w)[0] = r;
image.at<cv::Vec3b>(h,w)[1] = g;
image.at<cv::Vec3b>(h,w)[2] = b;
w++;
         r = y2 + cr;
         b = y2 + cb;
         g = y2 - cg;
         SAT(r);
         SAT(g);
         SAT(b);
image.at<cv::Vec3b>(h,w)[0] = r;
image.at<cv::Vec3b>(h,w)[1] = g;
image.at<cv::Vec3b>(h,w)[2] = b;
w++;
      }
h++;
w=0;
   }
////

return image;
}
