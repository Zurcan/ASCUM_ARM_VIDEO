#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLayout>
#include <NcFramelessHelper.h>
#include <QMultimedia>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia>
#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QMediaPlayer>
#include <QMovie>
#include <qvideosurfaceformat.h>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <VideoPlayer.h>

//#include <QGlib/Connect>
//#include <QGlib/Error>
//#include <QGst/Pipeline>
//#include <QGst/ElementFactory>
//#include <QGst/Bus>
//#include <QGst/Message>
//#include <QGst/Query>
//#include <QGst/ClockTime>
//#include <QGst/Event>
//#include <QGst/StreamVolume>
//#include <QGst/Ui/VideoWidget>

//#include <gst/gst.h>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    NcFramelessHelper *fh1;
    NcFramelessHelper *fh2;
    QWidget *videoScreen1;
    QWidget *videoScreen2;
    QHBoxLayout *videoLayout1;
    QHBoxLayout *videoLayout2;
    QMediaPlayer *videoPlayer1;
    QMediaPlayer *videoPlayer2;
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    VlcVideoDelegate *videoWidget;
    VlcWidgetVideo *video;
    VlcInstance *_instance_2;
    VlcMedia *_media_2;
    VlcMediaPlayer *_player_2;
    VlcVideoDelegate *videoWidget_2;
    VlcWidgetVideo *video_2;
    VlcVideoFrame *frame;

public:

    int initSlider(int);
    int initColoredScale(char*, int length);
    explicit MainWindow(QWidget *parent = 0);
    void openAndPlayVideo();
    int testSomeVideo();
    int gstTest();
    void openLocal();
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
