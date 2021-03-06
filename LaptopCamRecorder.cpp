#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include <time.h>

using namespace cv;
using namespace std;

class Timer {

public:
	float curTime = 0.0f;
	float end = 0.0f;
	time_t objectStartTime;

	Timer(float durationInSec) {
		this->curTime = 0.0f;
		this->end = durationInSec;
		objectStartTime = time(0);
	}
	
	void Tick() {
		curTime = time(0) - this->objectStartTime;
	}

	bool IsFinished() {
		return this->curTime >= this->end;
	}

	void Set(int start, int end) {
		this->curTime = start;
		this->end = end;
	}

	void Reset() {
		this->curTime = 0;
		objectStartTime = time(0);
	}
};




/*
* argv[0] = program name
* argv[1] = program duration
* argv[2] = snapshot delta time(int that tells how often should snapshot be taken)
*/
int main(int argc, char *argv[])
{
	if (argc != 3)
		return 0;

	int programLength = atoi(argv[1]);
	int takenSnapshotTimeInterval = atoi(argv[2]);
	cout << "ARG : " << takenSnapshotTimeInterval;
	cout << "\n ### Program started ###";
	cout << "\nTaking snapshot every " << takenSnapshotTimeInterval << " sec";
	cout << "\nProgram duration = " << programLength << " sec";
	


	Mat frame;
	VideoCapture vid(0);
	bool oneFrameRead = false;
	int snapshotCounter = 0;
	Timer snapshotTimer(takenSnapshotTimeInterval);
	Timer programDurationTimer(programLength);

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
				std::cout << "SNAPSHOT[" << std::to_string(snapshotCounter) << "],[TIME]=" << programDurationTimer.curTime << " TAKEN AND SAVED" << std::endl;
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

	

	cout << "\n### Program ended ###";
	return 1;

}

