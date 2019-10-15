#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <qpainter.h>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include "MyButton.h"
//#include <qpixmap.h>

class MyWidget :
	public QWidget
{
	Q_OBJECT
private:
	bool isEnter = false;
	QPoint z = QPoint();
	MyButton *btn1;
	MyButton *btn2;
	MyButton *btn3;
	MyButton *btn4;
	MyButton *btn5;
protected:
	
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);

	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
signals:
	void btn1Clicked();
	void btn2Clicked();
	void btn3Clicked();
	void btn4Clicked();
	void btn5Clicked();
private slots:
	void subBtnIsPressed(QMouseEvent*);
	void subBtnIsMoved(QMouseEvent*);
	void subBtnIsRelease(QMouseEvent*);
public:
	MyWidget(QWidget * parent = 0);
	void subBtnEvent();
	~MyWidget();
};

