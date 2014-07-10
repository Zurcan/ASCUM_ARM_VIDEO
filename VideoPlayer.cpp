#include <VideoPlayer.h>
#include <QString>
//#include <vlc-qt/Common.h>
//#include <vlc-qt/Instance.h>
//#include <vlc-qt/Media.h>
//#include <vlc-qt/MediaPlayer.h>
//#include <vlc-qt/WidgetVideo.h>
//#include <vlc-qt/VideoFrame.h>
//#include <vlc-qt/WidgetSeek.h>
void VideoPlayer::defineVideo(QObject *parent, QWidget *videoparent1/*, QWidget *videoparent2*/)
{

    _instance = new VlcInstance(VlcCommon::args(),parent);

//    _instance_2 = new VlcInstance(VlcCommon::args(),parent);
    _player = new VlcMediaPlayer(_instance);
//    _player_2 = new VlcMediaPlayer(_instance_2);
    video = new VlcWidgetVideo(videoparent1);
//    video_2 = new VlcWidgetVideo(videoparent2);
    video->setGeometry(0, -30, 470, 360);
//    video_2->setGeometry(0, 0, 380, 360);
    _player->setVideoWidget(video);
//    _player_2->setVideoWidget(video_2);
//    QObject::connect(_player,SIGNAL(end()),VideoPlayer,SLOT(endSlot()));
}



int VideoPlayer::changeGeometry(QRect rect)
{
    video->setGeometry(rect);

    return 0;
}

QString VideoPlayer::getCurrentMediaLocation()
{

    return _media->currentLocation();
}

int VideoPlayer::openLocal(QString file)
{

    if (file.isEmpty())
        return 1;
    _media = new VlcMedia(QString::fromLocal8Bit(file.toLocal8Bit()), true, _instance);
    video->show();
    _player->open(_media);
    _player->play();
    ispaused = false;
//    filename = file;
    return 0;
}

int VideoPlayer::setPlayerPosition(float pos)
{
    _player->setPosition(pos);
    return 0;
}

float VideoPlayer::getPosition()
{
    return _player->position();
}

int VideoPlayer::stop()
{
    _player->stop();

    return 0;
}

int VideoPlayer::pause()
{


    if(!ispaused)
    {
        _player->pause();
        ispaused = true;
        return 0;
    }
    else
    {
        _player->play();
        ispaused = false;
        return 1;
    }


}

int VideoPlayer::getVideoLength()
{


    return _player->length();
}

int VideoPlayer::moveToTime(int time)
{
    if(time<=_player->length())
    {
        _player->setTime(time);
        return 0;
    }
    else return 1;
}

int VideoPlayer::getCurrentTime()
{


   return _player->time();
}
