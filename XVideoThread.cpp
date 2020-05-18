#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//һ����ƵԴ
static VideoCapture cap1;
static bool isExit = false;

//��һ����ƵԴ, open����һ���̵߳��õģ���Ҫע���̰߳�ȫ
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
	//5��18�ţ���һ������ѭ��Ҳ������쳣���³����������viewImage(mat1);�ȴ������ѭ����ͷ��
	for (;;)
	{
		mutex.lock();
		if (isExit)
		{
			mutex.unlock();
			break;
		}
		//�ж���Ƶ�Ƿ��
		if (!cap1.isOpened())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		//��ȡһ֡��Ƶ�����벢����ɫת��
		if (!cap1.read(mat1) || mat1.empty())
		{
			mutex.unlock();
			msleep(5);
			continue;
		}
		//��ʾͼ��
		viewImage(mat1);
		//һ��Ҫ���ͷŵ�����sleep�������Ϊ������ʱ�ܼ�ʱ�˳��Ͱѽ������ں�����
		msleep(40);
		mutex.unlock();
	}
	
}
