#include <VideoPlayer.h>
#include <QString>
#include <QDebug>
#include <QFile>
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
    int x1,y1,x2,y2;
//    _instance_2 = new VlcInstance(VlcCommon::args(),parent);
    _player = new VlcMediaPlayer(_instance);
    someVideo = new VlcVideo(_player);
//    _player_2 = new VlcMediaPlayer(_instance_2);
    video = new VlcWidgetVideo(videoparent1);
//    video_2 = new VlcWidgetVideo(videoparent2);
//    video->setGeometry(0, -30, 470, 360);
    QSize tmpSize;
    videoparent1->geometry().getCoords(&x1,&y1,&x2,&y2);
//    qDebug() << videoparent1->geometry();
    tmpSize = videoparent1->geometry().size();
    QRect tmpgeometry;
//    tmpgeometry = videoparent1->geometry();
    tmpgeometry.setSize(tmpSize);
    tmpgeometry.setCoords(x1,y1,x2,y2);

    video->setGeometry(tmpgeometry);
//    qDebug() << video->geometry();
//    video->setGeometry(video->geometry().setCoords(x1,y1,x2,y2));
//    video_2->setGeometry(0, 0, 380, 360);
    _player->setVideoWidget(video);
//    _player_2->setVideoWidget(video_2);
//    QObject::connect(_player,SIGNAL(end()),VideoPlayer,SLOT(endSlot()));
//    connect(_player->tim)
}

//void VideoPlayer::VlcMediaPlayer:timerEve

int VideoPlayer::changeGeometry(QRect rect)
{
    video->setGeometry(rect);
    return 0;
}

QSize VideoPlayer::getVideoSize()
{
    return video->size();
}

QRect VideoPlayer::getGeometry()
{

    return video->geometry();
}

QString VideoPlayer::getCurrentMediaLocation()
{

    return _media->currentLocation();
}

int VideoPlayer::openLocal(QString file)
{

    if (file.isEmpty())
        return 1;
    QFile somefile;
    somefile.setFileName(file);

//    qDebug() <<"size of file" << file << "is " << somefile.size();
    if(somefile.size()<10000)
    {
        _player->stop();
//        qDebug() << "quiting openLocal";

        return 2;
    }
    _media = new VlcMedia(QString::fromLocal8Bit(file.toLocal8Bit()), true, _instance);
//    video->show();
//    someVideo = new VlcVideo(_player);
//    qDebug() << "size" << someVideo->size();
    _player->open(_media);

//    _player->play();
//    _media->
    if(_player->state()==7)
    {
//        _player->stop();
        return 2;
    }
    while(_player->state()==1)
    {
//        if(_player->state()==7)
//            return 2;
    }
    _player->play();
    if(_player->state()==7)
    {
//            _player->stop();

        return 2;
    }
    while(_player->state()!=3)
    {
        if(_player->state()==7)
        {
//            _player->stop();
            return 2;
        }
    }
    _player->togglePause();
    if(_player->state()==7)
    {
//            _player->stop();
        return 2;
    }
    while(_player->state()!=4)
    {
        if(_player->state()==7)
        {
//            _player->stop();
            return 2;
        }
    }
//    qDebug() << "state" << _player->state();
//    qDebug() << "length" << _player->length();
    _player->togglePause();

//    _player->play();
//    ispaused = false;

//    filename = file;
    return 0;
}
void VideoPlayer:: showText(QString t)
{
    someVideo->showMarquee("123123",0,0,5,255,20,0xFFFFFF,5);

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
