// get Background mean pixels of a video to BackgroundImage.jpg

#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
 #include <opencv2/core/core.hpp>
 #include <opencv2/opencv.hpp>

#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{

cout << "Help for next time can be used with arguments like: (./exe video.avi 100),  (./exe videofile.avi No_Of_skip_Frame)" << endl;

	    Mat frame, frame_threshold1,frame_threshold2;
	      // set input video
	  std::string videoName = argv[1];
	  VideoCapture cap(videoName);
	// Exit if video is not opened
	    if(!cap.isOpened())
	    {
		cout << "Could not read video file" << endl;
		return 1;
		
	    }
	    

	//cap.set(CV_CAP_PROP_POS_FRAMES, 3000);
	cap >> frame;

	    cv::namedWindow("Video Capture",WINDOW_NORMAL);
	    cv::resizeWindow("Video Capture", 600,800);
	    
	 

	cv::Mat frame32f,oldframe,diff;
	int i=0;
	int skip=40; // No of Frame to be skiped

	 if (argc >= 3)// if other parameter shold be the number of skiped frames 
	    {
		std::istringstream iss( argv[2] );
		if (!(iss >> skip))
		{
		    	cerr << "Invalid Int number in argo.2" << argv[2] << '\n';
			return 1;
		}
	    }

	int count=0;
	cv::Mat resultframe = cv::Mat::zeros(frame.size().height,frame.size().width ,CV_32FC3);
	while((char)waitKey(1)!='q')
	{
		//cap.set(CV_CAP_PROP_POS_FRAMES, 3000); should use this instead of skip 
		cap>>frame;
		if(frame.empty())
		    break;

		if(i%skip==0){
		frame.convertTo(frame32f,CV_32FC3);
		resultframe +=frame32f;
		count++;
		cout<<"add frame"<< endl;
		imshow("Video Capture",frame);
		}
		i++;
		oldframe=frame.clone();
	}
	
	resultframe *= (1.0/count); // sum / count
	normalize(resultframe,resultframe,0,1,CV_MINMAX); // normalize to 1

	cv::medianBlur(resultframe, resultframe, 3); // blure it
	//cv::medianBlur(resultframe, resultframe, 3);
	resultframe.convertTo(resultframe, CV_8UC3, 255.0); // to 3 chanales

	cv::imwrite("BackgroundImage.jpg",resultframe);// output file backgroundImage
	imshow("Video Capture",resultframe);

	waitKey(0);
	return 0;
  }
