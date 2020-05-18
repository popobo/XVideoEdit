#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//一号视频源
static VideoCapture cap1;
static bool isExit = false;

//打开一号视频源, open是另一个线程调用的，需要注意线程安全
bool XVideoThread::open(const string file)
{
	cout << "open" << file << endl;
	bool bRet;

	do 
	{
		mutex.lock();
		bRet = cap1.open(file);
		mutex.unlock();
		
		cout << bRet << endl;
	} while (0);

	
	return bRet;
}

XVideoThread::XVideoThread()
{
	start();
}


XVideoThread::~XVideoThread()
{
	mutex.lock();
	isExit = true;
	mutex.unlock();
}

void XVideoThread::run()
{
	Mat mat1;
	//5月18号，第一个坑死循环也会产生异常导致程序崩溃，将viewImage(mat1);等代码放在循环外头了
	for (;;)
	{
		mutex.lock();
		if (isExit)
		{
			mutex.unlock();
			break;
		}
		//判断视频是否打开
		if (!cap1.isOpened())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		//读取一帧视频，解码并做颜色转换
		if (!cap1.read(mat1) || mat1.empty())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		//显示图像
		viewImage(mat1);
		//一般要先释放掉锁在sleep，但这边为了析构时能及时退出就把解锁放在后面了
		msleep(40);
		mutex.unlock();
	}
	
}
