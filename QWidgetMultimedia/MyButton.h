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
	bool isRhombus = false;//�Ƿ������Σ�Ĭ�ϲ������Σ��Ǿ��Σ�
	bool mouseMoved = false;//�����갴�º��Ƿ����ƶ�
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

