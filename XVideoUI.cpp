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
}

void XVideoUI::open()
{
	bool boRet = false;
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
		if (!(boRet = XVideoThread::getObject()->open(fileName)))
		{
			QMessageBox::information(this, "", name + "open failed");
			break;
		}
		
		//QMessageBox::information(this, "", name);
	} while (false);

	
	return;
}
