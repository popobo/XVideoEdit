#pragma once
#include <QThread>
#include <string>

using namespace std;
class XVideoThread: public QThread
{
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

protected:
	XVideoThread();
};

