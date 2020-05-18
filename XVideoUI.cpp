#include "XVideoUI.h"
#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include "XVideoThread.h"

using namespace std;

XVideoUI::XVideoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//隐藏标题栏
	setWindowFlags(Qt::FramelessWindowHint);

	//信号和槽进行关联
	//注册Mat类型，使之能够在信号和槽之间进行传递
	//5月18号，第二个坑，SIGNAL和SLOT中的参数类型都不能有变量名如cv::Mat mat, 否则会找不到对应的槽函数或信号函数
	qRegisterMetaType<cv::Mat>("cv::Mat");
	QObject::connect(XVideoThread::getObject(),
					SIGNAL(viewImage(cv::Mat)),
					ui.src1Video,
					SLOT(setImage(cv::Mat)));
}

void XVideoUI::open()
{
	QString name;
	string fileName;
	do
	{
		//QString::fromLocal8Bit 防止中文乱码
		name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择视频文件"));
		if (name.isEmpty())
		{
			break;
		}
		//防止选择中文文件时出错
		fileName = name.toLocal8Bit().data();
		if (!XVideoThread::getObject()->open(fileName))
		{
			QMessageBox::information(this, "", name + "open failed");
			break;
		}
		
		//QMessageBox::information(this, "", name);
	} while (false);

	
	return;
}
