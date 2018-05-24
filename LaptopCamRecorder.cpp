#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include <time.h>

using namespace cv;

class Timer {

public:
	float start = 0.0f;
	float end = 0.0f;
	time_t objectStartTime;

	Timer(float durationInSec) {
		this->start = 0.0f;
		this->end = durationInSec;
		objectStartTime = time(0);
	}
	
	void Tick() {
		start = time(0) - this->objectStartTime;
	}

	bool IsFinished() {
		return this->start >= this->end;
	}

	void Set(int start, int end) {
		this->start = start;
		this->end = end;
	}

	void Reset() {
		this->start = 0;
		objectStartTime = time(0);
	}
};





int main()
{
	Mat frame;
	VideoCapture vid(0);
	bool oneFrameRead = false;
	int snapshotCounter = 0;
	Timer snapshotTimer(1);
	Timer programDurationTimer(10);

	if (!vid.isOpened()) 
	{
		return -1;
	}
	
	try
	{
		while (vid.read(frame))
		{
			programDurationTimer.Tick();
			snapshotTimer.Tick();
			if (snapshotTimer.IsFinished())
			{
				imshow("Webcam", frame);
				if (waitKey(1000 / 20) >= 0)
					break;

				snapshotCounter++;
				std::string fileName = "" + std::to_string(snapshotCounter) + ".jpg";
				imwrite(fileName, frame);
				std::cout << "SNAPSHOT[" + std::to_string(snapshotCounter) +"] TAKEN AND SAVED" << std::endl;
				snapshotTimer.Reset();
			}
			if (programDurationTimer.IsFinished()) 
			{
				std::cout << "PROGRAM FINISHED SUCCESSFULLY AFTER : " + (int)programDurationTimer.end << std::endl;
				return 1;
			}
		}
	}
	catch (std::string text)
	{
		std::cout << "EXCEPTION : " + text << std::endl;
	}

	
	


	int a;
	std::cin >> a;
	return 1;

}

