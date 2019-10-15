#include "MyWidget.h"
#include <qdebug.h>


MyWidget::MyWidget(QWidget * parent):QWidget(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
	btn1 = new MyButton(this);
	btn2 = new MyButton(this);
	btn3 = new MyButton(this);
	btn4 = new MyButton(this);
	btn5 = new MyButton(this);
	//子控件按钮的事件处理
	subBtnEvent();
	this->setFixedSize(200, 200);
	int wid_w = this->width();
	int wid_h = this->height();
	int btn_w = btn1->width();
	int btn_h = btn1->height();
	int offset = (wid_w - 94) / 2;
	int btnSize = (wid_w - 28) / 2;
	btn1->setRhombus(true);
	btn2->setRhombus(true);
	btn3->setRhombus(true);
	btn4->setRhombus(true);
	btn1->setFixedSize(btnSize, btnSize);
	btn2->setFixedSize(btnSize, btnSize);
	btn3->setFixedSize(btnSize, btnSize);
	btn4->setFixedSize(btnSize, btnSize);
	btn5->setFixedSize(80, 80);
	btn5->setBtnColor(QColor(0, 0, 0, 200));
	//默认打开浮动窗口时是小矩形形状
	this->setMask(QRect(53, 53, 80, 80));
	btn1->hide();
	btn2->hide();
	btn3->hide();
	btn4->hide();
	
	btn1->move(wid_w / 2 - btn_w / 2, 0);
	btn2->move(0, wid_h / 2 - btn_h / 2 );
	btn3->move(wid_w / 2 - btn_w / 2, wid_h - btn_h);
	btn4->move(wid_w - btn_w, wid_h / 2 - btn_h / 2);
	btn5->move(offset, offset );
	connect(btn1, &MyButton::clicked, [=]() {emit btn1Clicked(); });
	connect(btn2, &MyButton::clicked, [=]() {emit btn2Clicked(); });
	connect(btn3, &MyButton::clicked, [=]() {emit btn3Clicked(); });
	connect(btn4, &MyButton::clicked, [=]() {emit btn4Clicked(); });
	connect(btn5, &MyButton::clicked, [=]() {emit btn5Clicked(); });
}

void MyWidget::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		QPoint x = this->pos();
		QPoint y = e->globalPos();
		z = y - x;
	}
	QWidget::mousePressEvent(e);
}
void MyWidget::mouseMoveEvent(QMouseEvent* e)
{
	if (z != QPoint())
	{
		QPoint y = e->globalPos();
		QPoint x = y - z;
		this->move(x);
	}
	QWidget::mouseMoveEvent(e);
}
void MyWidget::mouseReleaseEvent(QMouseEvent* e)
{
	z = QPoint();
	QWidget::mouseReleaseEvent(e);
}
void MyWidget::enterEvent(QEvent* e)
{
	Q_UNUSED(e);
	isEnter = true;
	this->setMask(QRegion(this->rect()));
	btn1->show();
	btn2->show();
	btn3->show();
	btn4->show();
	this->update();
}
void MyWidget::leaveEvent(QEvent* e)
{
	Q_UNUSED(e);
	isEnter = false;
	this->setMask(QRect(53,53,80,80));
	btn1->hide();
	btn2->hide();
	btn3->hide();
	btn4->hide();
	this->update();
}

void MyWidget::subBtnIsPressed(QMouseEvent* e)
{
	this->mousePressEvent(e);
}
void MyWidget::subBtnIsMoved(QMouseEvent* e)
{
	this->mouseMoveEvent(e);
}
void MyWidget::subBtnIsRelease(QMouseEvent* e)
{
	this->mouseReleaseEvent(e);
}

void MyWidget::subBtnEvent()
{
	connect(btn1, &MyButton::mouseIsPressed, this, &MyWidget::subBtnIsPressed);
	connect(btn1, &MyButton::mouseIsMoved, this, &MyWidget::subBtnIsMoved);
	connect(btn1, &MyButton::mouseIsReleased, this, &MyWidget::subBtnIsRelease);

	connect(btn2, &MyButton::mouseIsPressed, this, &MyWidget::subBtnIsPressed);
	connect(btn2, &MyButton::mouseIsMoved, this, &MyWidget::subBtnIsMoved);
	connect(btn2, &MyButton::mouseIsReleased, this, &MyWidget::subBtnIsRelease);

	connect(btn3, &MyButton::mouseIsPressed, this, &MyWidget::subBtnIsPressed);
	connect(btn3, &MyButton::mouseIsMoved, this, &MyWidget::subBtnIsMoved);
	connect(btn3, &MyButton::mouseIsReleased, this, &MyWidget::subBtnIsRelease);

	connect(btn4, &MyButton::mouseIsPressed, this, &MyWidget::subBtnIsPressed);
	connect(btn4, &MyButton::mouseIsMoved, this, &MyWidget::subBtnIsMoved);
	connect(btn4, &MyButton::mouseIsReleased, this, &MyWidget::subBtnIsRelease);

	connect(btn5, &MyButton::mouseIsPressed, this, &MyWidget::subBtnIsPressed);
	connect(btn5, &MyButton::mouseIsMoved, this, &MyWidget::subBtnIsMoved);
	connect(btn5, &MyButton::mouseIsReleased, this, &MyWidget::subBtnIsRelease);
}

MyWidget::~MyWidget()
{
}
