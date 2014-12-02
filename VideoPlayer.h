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
#include <vlc-qt/MediaList.h>
#include <vlc-qt/Video.h>
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
//    VlcMediaPlayer *_player_2;
     VlcMedia *_media;
    VlcVideo *someVideo;
//    explicit VideoPlayer(QWidget *parent = 0);
    void defineVideo(QObject *, QWidget *);
    int openLocal(QString);
    int stop();
    int pause();
    int moveToTime(int);
    int getCurrentTime();
    int changeGeometry(QRect rect);
    int getVideoLength();
    float getPosition();
    int setPlayerPosition(float pos);

    QSize getVideoSize();
    QRect getGeometry();
    QString getCurrentMediaLocation();
    ~VideoPlayer();


private:
    VlcWidgetVideo *video;
//    VlcWidgetVideo *video_2;
    VlcInstance *_instance;
//    VlcInstance *_instance_2;

//    VlcMedia *_media_2;
    bool ispaused;

//    void openUrl();

//    Ui::DemoPlayer *ui;


};
//variables



//functions



#endif // VIDEOPLAYER_H
