#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QWidgetMultimedia.h"

class QWidgetMultimedia : public QMainWindow
{
	Q_OBJECT

public:
	QWidgetMultimedia(QWidget *parent = Q_NULLPTR);

private:
	Ui::QWidgetMultimediaClass ui;
};
