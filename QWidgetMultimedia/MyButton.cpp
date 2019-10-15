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
	//鼠标按下事件 触法当前对象和父窗口的 鼠标按下事件
	if (ev->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent * e = static_cast<QMouseEvent*>(ev);
		this->mousePressEvent(e);
		emit mouseIsPressed(e);
		return true;
	}
	//鼠标按下后移动了 触发父窗口的鼠标移动事件
	if (ev->type() == QEvent::MouseMove)
	{
		//鼠标按下后移动了
		mouseMoved = true;
		QMouseEvent * e = static_cast<QMouseEvent*>(ev);
		emit mouseIsMoved(e);
		return true;
	}
	//鼠标释放事件 触法当前对象和父窗口的对应事件
	if (ev->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent * e = static_cast<QMouseEvent*>(ev);
		if (!mouseMoved)//如果鼠标按下后没有移动 则触发当前对象鼠标释放事件 
		{
			this->mouseReleaseEvent(e);
		}
		else {			//恢复标记状态
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
