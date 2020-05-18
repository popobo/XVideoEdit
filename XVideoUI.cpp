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
	//���ر�����
	setWindowFlags(Qt::FramelessWindowHint);
}

void XVideoUI::open()
{
	bool boRet = false;
	QString name;
	string fileName;
	do
	{
		//QString::fromLocal8Bit ��ֹ��������
		name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��ѡ����Ƶ�ļ�"));
		if (name.isEmpty())
		{
			break;
		}
		//��ֹѡ�������ļ�ʱ����
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
