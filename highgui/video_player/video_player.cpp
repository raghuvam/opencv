
#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void videoInfo(VideoCapture &vid)
{
	cout << "Video Info: " << endl;

	cout << "Frame rate: " << vid.get(CV_CAP_PROP_FPS) << endl ;

	cout << "Frame width: " << vid.get(CV_CAP_PROP_FRAME_WIDTH) << endl ;

	cout << "Frame height: " << vid.get(CV_CAP_PROP_FRAME_HEIGHT) << endl ;

}

int main (int argc, char** argv)
{

	cout << "video player program" << endl;

	char* video_name = argv[1];


	


	VideoCapture source(video_name);
	
	if(!source.isOpened())	
	{
		cout << "Couldn't open the source video" << endl;
	}
	
	videoInfo(source);

	namedWindow("video_player",CV_WINDOW_OPENGL);
	startWindowThread();

	Mat Frame;

	while (1)
	{
		source >> Frame;

		imshow("video_player",Frame);

		waitKey(30);

	}




	return 0;
}

