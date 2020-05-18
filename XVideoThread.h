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

	//��һ����ƵԴ�ļ�	
	bool open(const string file);

	~XVideoThread();

	//�߳���ں���
	void run();

protected:
	XVideoThread();
};

