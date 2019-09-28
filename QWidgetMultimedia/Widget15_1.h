#pragma once

#include <QMainWindow>
#include "ui_Widget15_1.h"
#include <qmultimedia.h>
#include <qlabel.h>
#include <qslider.h>
#include <qmediaplayer.h>
#include <qmediaplaylist.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <QListWidget>
#include <QFile>
#include <qmessagebox.h>

class Widget15_1 : public QMainWindow
{
	Q_OBJECT

public:

	bool sliderDown = false;
	Widget15_1(QWidget *parent = Q_NULLPTR);
	~Widget15_1();
	void on_pushButon_clicked();
	void on_pushButon_2_clicked();
	void on_pushButon_3_clicked();
	void onCurrentItemChanged(const QListWidgetItem *);
	void on_pushButon_4_clicked();
	void on_pushButon_5_clicked();
	void on_pushButon_6_clicked();
	void on_pushButon_7_clicked();
	void on_pushButon_8_clicked();
	void onStateChanged(QMediaPlayer::State state);

	void onPositionChanged(qint64 position);
	void onDurationChanged(qint64 duration);

	void onVolumeChanged(int);
	void sliderValueChanged(int);
	void progressChanged(int);

private:
	Ui::Widget15_1 ui;

	QMediaPlayer * player;
	QMediaPlaylist * playList;

	QSlider * slider;
	QLabel * labName;
	QLabel * labTime;
	QString positionTime = "";
	QString durationTime = "";
	
};
