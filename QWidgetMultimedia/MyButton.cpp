#include "MyButton.h"


MyButton::MyButton(QWidget * parent) : QPushButton(parent)
{
	this->resize(100, 100);
	this->installEventFilter(this);
	//this->setMouseTracking(true);
	//this->setAttribute(Qt::WA_TransparentForMouseEvents);

}

void MyButton::paintEvent(QPaintEvent * e)
{
	Q_UNUSED(e);
	QPainter painter(this);
	int w = this->width();
	int h = this->height();
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setWidth(2);
	pen.setColor(QColor(154, 154, 154));
	painter.setPen(pen);
	painter.setBrush(btnColor);
	if (isRhombus)
	{
		QPoint points[4] = { QPoint(w / 2,0),
					   QPoint(w,h / 2),
					   QPoint(w / 2,h),
					   QPoint(0,h / 2) };
		QVector<QPoint> vPoint;
		for (int i = 0; i < 4; i++)
		{
			vPoint << points[i];
		}
		painter.drawConvexPolygon(points, 4);
		this->setMask(QRegion(QPolygon(vPoint)));

		}
	else
	{
		painter.drawRect(this->rect());
		/*QPixmap pix(":/icon/image/music.jpg");
		painter.drawPixmap(this->rect(), pix);
		this->setMask(QRegion(this->rect()));*/
	}
}

void MyButton::resizeEvent(QResizeEvent * e)
{
	Q_UNUSED(e);
	this->update();
}

void MyButton::setImage(QPixmap pix)
{
	this->setIcon(QIcon(pix));
	this->setIconSize(QSize(80, 80));
}

bool MyButton::eventFilter(QObject * obj, QEvent * ev)
{
	//��갴���¼� ������ǰ����͸����ڵ� ��갴���¼�
	if (ev->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent * e = static_cast<QMouseEvent*>(ev);
		this->mousePressEvent(e);
		emit mouseIsPressed(e);
		return true;
	}
	//��갴�º��ƶ��� ���������ڵ�����ƶ��¼�
	if (ev->type() == QEvent::MouseMove)
	{
		//��갴�º��ƶ���
		mouseMoved = true;
		QMouseEvent * e = static_cast<QMouseEvent*>(ev);
		emit mouseIsMoved(e);
		return true;
	}
	//����ͷ��¼� ������ǰ����͸����ڵĶ�Ӧ�¼�
	if (ev->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent * e = static_cast<QMouseEvent*>(ev);
		if (!mouseMoved)//�����갴�º�û���ƶ� �򴥷���ǰ��������ͷ��¼� 
		{
			this->mouseReleaseEvent(e);
		}
		else {			//�ָ����״̬
			mouseMoved = false;
		}
		emit mouseIsReleased(e);
		return true;
	}


	return QPushButton::eventFilter(obj,ev);
}

/*void MyButton::mousePressEvent(QMouseEvent* e)
{

}*/

/*void MyButton::mouseMoveEvent(QMouseEvent* e)
{

}*/

/*void MyButton::mouseReleaseEvent(QMouseEvent* e)
{

}*/

void MyButton::enterEnevt(QEvent* e)
{
	
}

void MyButton::leaveEvent(QEvent* e)
{

}

MyButton::~MyButton()
{
}
