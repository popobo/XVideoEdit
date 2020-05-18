#pragma once
#include <QThread>
#include <string>
#include "opencv2/core.hpp"

using namespace std;
class XVideoThread: public QThread
{

	Q_OBJECT

public:
	static XVideoThread *getObject()
	{
		static XVideoThread videoThread;
		return &videoThread;
	}

	//��һ����ƵԴ�ļ�	
	bool open(const string file);

	~XVideoThread();

	//�߳���ں���
	void run();

signals:
	//�����ź�ʱ�����͵Ĳ��������һ�������У�ֱ����Ӧ�Ĳۺ�������󣬲Ż�ѱ����ͷŵ��������������̫�ÿ��ܵ����ڴ����
	void viewImage(cv::Mat mat);

protected:
	std::mutex mutex;
	XVideoThread();
};
