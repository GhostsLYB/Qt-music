#pragma once
#include <qpushbutton.h>
#include <qwidget.h>
#include <qpainter.h>
#include <QPaintEvent>
#include <qcolor.h>
#include <qpixmap.h>

class MyButton : public QPushButton
{
	Q_OBJECT
private:
	bool isRhombus = false;//是否是菱形，默认不是菱形，是矩形；
	bool mouseMoved = false;//标记鼠标按下后是否有移动
	QColor btnColor = QColor(0, 0, 0, 100);
protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);
	//void mousePressEvent(QMouseEvent*);
	//void mouseMoveEvent(QMouseEvent*);
	//void mouseReleaseEvent(QMouseEvent*);
	
	void enterEnevt(QEvent*);
	void leaveEvent(QEvent*);
signals:
	void mouseIsPressed(QMouseEvent*);
	void mouseIsMoved(QMouseEvent*);
	void mouseIsReleased(QMouseEvent*);
public:
	void setRhombus(bool b) { isRhombus = b; }
	bool isRhonbus() { return isRhombus; }
	void setBtnColor(QColor c) { btnColor = c; }
	QColor getBtnColor() { return btnColor; }
	void setImage(QPixmap);
public:
	MyButton(QWidget * parent = 0);
	~MyButton();
};

