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

	//�źźͲ۽��й���
	//ע��Mat���ͣ�ʹ֮�ܹ����źźͲ�֮����д���
	//5��18�ţ��ڶ����ӣ�SIGNAL��SLOT�еĲ������Ͷ������б�������cv::Mat mat, ������Ҳ�����Ӧ�Ĳۺ������źź���
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
		//QString::fromLocal8Bit ��ֹ��������
		name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��ѡ����Ƶ�ļ�"));
		if (name.isEmpty())
		{
			break;
		}
		//��ֹѡ�������ļ�ʱ����
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
