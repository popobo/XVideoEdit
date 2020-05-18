#include "XVideoWidget.h"
#include <QPainter>
#include "opencv2/imgproc.hpp"

using namespace cv;

XVideoWidget::XVideoWidget(QWidget *p): QOpenGLWidget(p)
{
}

void XVideoWidget::paintEvent(QPaintEvent * e)
{
	QPainter qPainter;
	qPainter.begin(this);
	qPainter.drawImage(QPoint(0, 0), qimg);
	qPainter.end();
}


XVideoWidget::~XVideoWidget()
{
}


void XVideoWidget::setImage(cv::Mat mat)
{
	if (qimg.isNull())
	{
		//��֤�����СΪ4�ı�����������������б��λ������
		uchar *buf = new uchar[width() * height() * 3];
		qimg = QImage(buf, width(), height(), QImage::Format_RGB888);
	}
	Mat des;
	cv::resize(mat, des, Size(qimg.size().width(), qimg.size().height()));
	cv::cvtColor(des, des, COLOR_BGR2RGB);
	memcpy(qimg.bits(), des.data, des.cols * des.rows * des.elemSize());
	update();//�����paintEvent
}