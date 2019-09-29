#pragma execution_character_set("utf-8")
#include "Widget15_1.h"
#include <qdebug.h>
Widget15_1::Widget15_1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("音乐播放器");
	this->setFixedSize(500,350);
	this->setCentralWidget(ui.groupBox);
	setBtnProperty();
	//加载主题风格
	QFile f(":/qss/theme.qss");
	if (f.open(QFile::ReadOnly))
		qApp->setStyleSheet(f.readAll());
	else
		QMessageBox::warning(this, "waring", "Theme file theme.qss open fail!");
	
	slider = new QSlider(this);
	slider->setOrientation(Qt::Horizontal);
	slider->setFixedWidth(200);
	labName = new QLabel(this);
	labTime = new QLabel(this);
	labName->setFixedWidth(200);
	labTime->setFixedWidth(100);
	ui.statusBar->addWidget(labName);
	ui.statusBar->addWidget(slider);
	ui.statusBar->addWidget(labTime);
	player = new QMediaPlayer(this);
	playList = new QMediaPlaylist(this);
	player->setPlaylist(playList);
	playList->setPlaybackMode(QMediaPlaylist::Loop);
	//player->setMuted(true); //静音
	//音量
	ui.horizontalSlider->setMaximum(100);
	ui.horizontalSlider->setMinimum(0);
	ui.horizontalSlider->setValue(player->volume());
	connect(ui.listWidget, &QListWidget::currentItemChanged, this, &Widget15_1::onCurrentItemChanged);
	//添加 移除 清空
	connect(ui.pushButton, &QPushButton::clicked, this, &Widget15_1::on_pushButon_clicked);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &Widget15_1::on_pushButon_2_clicked);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &Widget15_1::on_pushButon_3_clicked);
	// 暂停	播放 停止
	connect(ui.pushButton_4, &QPushButton::clicked, this, &Widget15_1::on_pushButon_4_clicked);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &Widget15_1::on_pushButon_5_clicked);
	connect(ui.pushButton_6, &QPushButton::clicked, this, &Widget15_1::on_pushButon_6_clicked);
	//上一首 下一首
	connect(ui.pushButton_7, &QPushButton::clicked, this, &Widget15_1::on_pushButon_7_clicked);
	connect(ui.pushButton_8, &QPushButton::clicked, this, &Widget15_1::on_pushButon_8_clicked);
	//状态显示
	connect(player, &QMediaPlayer::stateChanged, this, &Widget15_1::onStateChanged);
	connect(player, &QMediaPlayer::positionChanged, this, &Widget15_1::onPositionChanged);
	connect(player, &QMediaPlayer::durationChanged, this, &Widget15_1::onDurationChanged);
	//音量变化
	connect(ui.horizontalSlider, &QSlider::valueChanged, this, &Widget15_1::sliderValueChanged);
	connect(player, &QMediaPlayer::volumeChanged, this, &Widget15_1::onVolumeChanged);
	//播放进度
	connect(slider, &QSlider::valueChanged, this, &Widget15_1::progressChanged);
	connect(slider, &QSlider::sliderPressed, [=]() {sliderDown = true; });
	connect(slider, &QSlider::sliderReleased, [=]() {sliderDown = false; });
	//退出
	connect(ui.btnQuit, &QPushButton::clicked, [=]() {
		close(); 
		});
}

void Widget15_1::setBtnProperty()
{
	ui.pushButton -> setProperty("isFunBtn", true);
	ui.pushButton_2 -> setProperty("isFunBtn", true);
	ui.pushButton_3 -> setProperty("isFunBtn", true);
	ui.btnQuit -> setProperty("isFunBtn", true);

	ui.pushButton_4->setProperty("isStatusBtn", true);
	ui.pushButton_5->setProperty("isStatusBtn", true);
	ui.pushButton_6->setProperty("isStatusBtn", true);
	ui.pushButton_7->setProperty("isStatusBtn", true);
	ui.pushButton_8->setProperty("isStatusBtn", true);
}
void Widget15_1::on_pushButon_clicked()
{
	QStringList strList = QFileDialog::getOpenFileNames(this, "添加音乐", "E:\\CloudMusic", "MP3音乐(*.mp3)");
	if (strList.isEmpty())
		return;
	for (int i = 0; i < strList.count(); i++)
	{
		QString str = strList.at(i);
		QFileInfo fileInfo(str);
		qDebug() << str << "\n" << fileInfo.fileName();
		playList->addMedia(QUrl::fromLocalFile(str));
		QListWidgetItem * item = new QListWidgetItem(fileInfo.fileName());
		ui.listWidget->addItem(item);
		
	}
	if (player->state() != QMediaPlayer::PlayingState)
	{
		playList->setCurrentIndex(0);
		ui.listWidget->setCurrentRow(0);
		player->play();
		
	}
	int v = player->volume();
	player->setVolume(50);
	v = player->volume();
	ui.pushButton_2->setEnabled(true);
	ui.pushButton_3->setEnabled(true);
}
void Widget15_1::on_pushButon_2_clicked()
{
	int curindex = ui.listWidget->currentRow();
	QListWidgetItem * item = ui.listWidget->takeItem(curindex);
	delete item;
	playList->removeMedia(curindex);
}
void Widget15_1::on_pushButon_3_clicked()
{
	ui.listWidget->clear();
	playList->clear();
	ui.pushButton_2->setEnabled(false);
	ui.pushButton_3->setEnabled(false);
}
void Widget15_1::onCurrentItemChanged(const QListWidgetItem * item)
{
	if (item == NULL)
		return;
	int row = ui.listWidget->currentRow();
	QString musicName = item->text();
	labName->setText(musicName);
	if (row == 0)
		ui.pushButton_7->setEnabled(false);
	if (row == ui.listWidget->count() - 1)
		ui.pushButton_8->setEnabled(false);
	playList->setCurrentIndex(row);
	player->play();
}
void Widget15_1::on_pushButon_4_clicked()
{
	player->pause();
}
void Widget15_1::on_pushButon_5_clicked()
{
	player->play();
}
void Widget15_1::on_pushButon_6_clicked()
{
	player->stop();
}
void Widget15_1::on_pushButon_7_clicked()
{
	ui.listWidget->setCurrentRow(ui.listWidget->currentRow() - 1);
	playList->previous();
}
void Widget15_1::on_pushButon_8_clicked()
{
	ui.listWidget->setCurrentRow(ui.listWidget->currentRow() + 1);
	playList->next();
}
void Widget15_1::onStateChanged(QMediaPlayer::State state)
{
	bool b = state == QMediaPlayer::PlayingState;
	ui.pushButton_4->setEnabled(b);
	ui.pushButton_5->setEnabled(!b);
	ui.pushButton_6->setEnabled(b);
}
void Widget15_1::onPositionChanged(qint64 position)
{
	slider->setValue(position);
	int msc = position / 1000;
	int mm = msc / 60;//分钟
	int ss = msc % 60;//秒
	positionTime = QString("%1:%2").arg(mm).arg(ss);
	if(!sliderDown)
		labTime->setText(positionTime + "/" + durationTime);
}
void Widget15_1::onDurationChanged(qint64 duration)
{
	slider->setMaximum(duration);
	slider->setValue(duration);
	int msc = duration / 1000;
	int mm = msc / 60;//分钟
	int ss = msc % 60;//秒
	durationTime = QString("%1:%2").arg(mm).arg(ss);
	labTime->setText(positionTime + "/" + durationTime);
	//QMediaContent content = player->currentMedia();
	int curindex = playList->currentIndex();
	ui.listWidget->setCurrentRow(curindex);
}
void Widget15_1::onVolumeChanged(int value)
{
	ui.horizontalSlider->setValue(value);
}
void Widget15_1::sliderValueChanged(int value)
{
	player->setVolume(value);
}
void Widget15_1::progressChanged(int value)
{
	if(sliderDown)
		player->setPosition(value);
}

Widget15_1::~Widget15_1()
{
}
