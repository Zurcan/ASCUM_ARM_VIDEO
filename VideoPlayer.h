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
#include <vlc-qt/Audio.h>
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

class VideoPlayer//: public QMainWindow
{
//Q_OBJECT
public:
   // explicit VideoPlayer(QWidget *parent = 0);
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
    void setAudioState(int state);
    void togglePause();
    void play();
    void showText(QString t,int timeout, int fontsize,int refresh);
    int getAudioIconState();//returns soundtrack state it may be 3 vals: 0 - track is disabled , 1 - track is muted, 2 - track is enabled
    int getAudioState();
    int getVideoState(); //returns video player vlc state
    void setAudioMuted(bool);
    void setAudioVolume(int);
    QSize getVideoSize();
    QRect getGeometry();
    QString getCurrentMediaLocation();
    ~VideoPlayer();


private:
    VlcWidgetVideo *video;
//    VlcWidgetVideo *video_2;
    VlcInstance *_instance;
    VlcInstance *_audioinstance;
    VlcMedia *_audio;
    VlcMediaPlayer *_audioplayer;

//    VlcMedia *_media_2;
    bool ispaused;
    int volume = 100;

//    void openUrl();

//    Ui::DemoPlayer *ui;


};
//variables



//functions



#endif // VIDEOPLAYER_H
