#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//一号视频源
static VideoCapture cap1;

//打开一号视频源
bool XVideoThread::open(const string file)
{
	cout << "open" << file << endl;
	bool bRet;

	do 
	{
		bRet = cap1.open(file);
	} while (0);

	
	return bRet;
}

XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{
}

void XVideoThread::run()
{
}
