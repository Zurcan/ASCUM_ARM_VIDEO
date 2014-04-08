#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
//includes
#include <QTimeEdit>
#include <QThread>
#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/WidgetVideo.h>
#include <vlc-qt/VideoFrame.h>
#include <vlc-qt/WidgetSeek.h>

namespace video {
class VideoPlayer;
}

//class VlcCommon;
//class VlcInstance;
//class VlcMedia;
//class VlcMediaPlayer;
//class VlcWidgetSeek;
//class VlcWidgetVideo;
//class QString;
//class QWidget;
//class QObject;
//class Common;

class VideoPlayer
{
//Q_OBJECT
public:

    VlcMediaPlayer *_player;
    VlcMediaPlayer *_player_2;


//    explicit VideoPlayer(QWidget *parent = 0);
    void defineVideo(QObject *, QWidget *, QWidget *);
    int openLocal(QString);
    int stop();
    int pause();
    int moveToTime(int);
    int getCurrentTime();

    ~VideoPlayer();

//private slots:
private:
    VlcWidgetVideo *video;
    VlcWidgetVideo *video_2;
    VlcInstance *_instance;
    VlcInstance *_instance_2;
    VlcMedia *_media;
    VlcMedia *_media_2;
    bool ispaused;
//    void openUrl();

//    Ui::DemoPlayer *ui;


};
//variables



//functions



#endif // VIDEOPLAYER_H
