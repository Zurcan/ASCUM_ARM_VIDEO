#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "gst/gst.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
       ui->nextTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
           ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
               ui->previousTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
//    videoScreen1 = new QWidget(this);
//    videoScreen2 = new QWidget(this);
//    NcFramelessHelper fh;
//    fh1 = new NcFramelessHelper;
//    fh2 = new NcFramelessHelper;
    videoLayout1 = new QHBoxLayout;
//    videoLayout2 = new QHBoxLayout;
////    videoScreen1->setLayout(videoLayout1);
//    videoScreen2->setLayout(videoLayout2);
//    fh1->activateOn(videoScreen1);
//    fh2->activateOn(videoScreen2);
//    videoScreen1->setGeometry(330,490,250,180);

//    videoScreen2->setGeometry(330,490,250,180);
//    QPalette tmpPalette;
//    tmpPalette.setColor(QPalette::Foreground,Qt::darkGray);
//    videoScreen1->setPalette(tmpPalette);
//    videoScreen2->setPalette(tmpPalette);
//    videoScreen1->setWindowFlags( Qt::Tool |Qt::FramelessWindowHint);
//    videoScreen2->setWindowFlags(  Qt::Tool |Qt::FramelessWindowHint);//add Qt::WindowStaysOnTopHint  if need on top of everything
//    videoScreen2->show();
//    videoScreen1->show();

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    frame = new VlcVideoFrame;
    video = new VlcWidgetVideo(ui->widget);
    video->setGeometry(0, 0, 380, 360);

    _player->setVideoWidget(video);
    ui->widget->setLayout(videoLayout1);
    initSlider(24);
    char videos[24];
    for (int i = 0; i < sizeof(videos);i++)
        videos[i]=i%2;
    initColoredScale(videos,sizeof(videos));
}

void MainWindow::openLocal()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
    if (file.isEmpty())
        return;
    _media = new VlcMedia(file, true, _instance);
    video->show();
    _player->open(_media);
    _player->play();
}

void MainWindow::openAndPlayVideo()
{
    videoPlayer1 = new QMediaPlayer;
    videoPlayer2 = new QMediaPlayer;
    QVideoWidget *wVideo1 = new QVideoWidget(videoScreen1);
    videoLayout1->addWidget(wVideo1);
    QVideoWidget *wVideo2 = new QVideoWidget(videoScreen2);
    videoLayout2->addWidget(wVideo2);
    videoPlayer1->setVideoOutput(wVideo1);
    wVideo1->setGeometry(videoLayout1->geometry());
    wVideo1->show();
    videoPlayer2->setVideoOutput(wVideo2);
    wVideo2->setGeometry(videoLayout2->geometry());
    wVideo2->show();
     QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
     videoPlayer1->setMedia(QUrl::fromLocalFile(fileName));
     videoPlayer2->setMedia(QUrl::fromLocalFile(fileName));
     videoPlayer1->play();
     videoPlayer2->play();
}

int MainWindow::initSlider(int topVal)
{
;
    return 0;
}
int MainWindow::initColoredScale(char *existingVideos, int length)
{
    QPalette palette = ui->tableWidget->palette();
    palette.setColor(QPalette::Base, Qt::green);
    for(int i = 0; i < length; i++)
    {
        QWidget *coloredBlock = new QWidget;//::setAutoFillBackground(true);
        coloredBlock->setAutoFillBackground(true);
        if(existingVideos[i])coloredBlock->setPalette(palette);
        ui->tableWidget->setCellWidget(0,i,coloredBlock);
    }
    return 0;
}

int MainWindow::gstTest()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    openAndPlayVideo();

}

void MainWindow::on_action_2_triggered()
{
    openLocal();
}
