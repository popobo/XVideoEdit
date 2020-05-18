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

	//打开一号视频源文件	
	bool open(const string file);

	~XVideoThread();

	//线程入口函数
	void run();

signals:
	//发送信号时，传送的参数会放入一个队列中，直到对应的槽函数处理后，才会把变量释放掉，如果队列阻塞太久可能导致内存溢出
	void viewImage(cv::Mat mat);

protected:
	std::mutex mutex;
	XVideoThread();
};
