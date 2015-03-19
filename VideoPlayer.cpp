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
//VideoPlayer::VideoPlayer(QWidget *parent)
//    : QMainWindow(parent),
//      ui(new Ui::DemoPlayer),
//      _media(0)
//{

//}

void VideoPlayer::defineVideo(QObject *parent, QWidget *videoparent1/*, QWidget *videoparent2*/)
{

    QStringList args;
    args.append("--no-video-title-show");
    args.append("--sub-filter=marq");
    _instance = new VlcInstance(args,parent);
    int x1,y1,x2,y2;
//    _instance_2 = new VlcInstance(VlcCommon::args(),parent);
    _player = new VlcMediaPlayer(_instance);

//    _player_2 = new VlcMediaPlayer(_instance_2);
    video = new VlcWidgetVideo(_player,videoparent1);
    video->setMediaPlayer(_player);
    _audioinstance = new VlcInstance(VlcCommon::args(),parent);
    //this->setWindowFlags(Qt::SubWindow);
//    _player = new VlcMediaPlayer(_instance);
    _audioplayer = new VlcMediaPlayer(_audioinstance);
//    video_2 = new VlcWidgetVideo(videoparent2);
//    video->setGeometry(0, -30, 470, 360);
    QSize tmpSize;
    qDebug() << "videoparent1" << videoparent1->objectName();
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
    video->show();
    someVideo = new VlcVideo(_player);
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
    //VlcVideo myvid;

   // qDebug() << "media" << _media->
//    video->show();

//    qDebug() << "size" << someVideo->size();
    _player->open(_media);
    QString audiofile =file;
    audiofile.chop(3);
    audiofile.append("wav");
    QFile audio;
    audio.setFileName(audiofile);
    if(!audio.exists())
        qDebug() << "no such file";

    qDebug() << audiofile;
    _audioplayer->stop();
    _audio = new VlcMedia(audiofile,true,_audioinstance);
//     qDebug() << _audioplayer->currentMedia()->currentLocation();
    qDebug() << _audio->trackType();
    if(audio.exists())
    {
        qDebug() << "YES IT EXISTS!!!!";
        _audioplayer->open(_audio);
        _audioplayer->audio()->setVolume(100);
        qDebug() << _audioplayer->currentMedia()->currentLocation();
        _audioplayer->togglePause();
    }
    else
    {
        _audioplayer->stop();

    }

//    _player->video()->showMarquee("12312123132313213213213213213213213213213213213213123",10,100,1000,255,45,0xff0000,100);
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
    someVideo = new VlcVideo(_player);
    qDebug() << "video info"<< someVideo->aspectRatio() << someVideo->scale() << someVideo->track();

    /*_player->video()->*///showText("111111",1000,40,1000);
//    showText("123");
//    filename = file;
    return 0;
}
void VideoPlayer:: showText(QString t, int timeout, int fontsize, int refresh)
{
    _player->video()->showMarquee(t,400,100,timeout,255,fontsize,0xFFFF00,refresh);
    qDebug() << t;

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
    _audioplayer->stop();
//    setAudioState(Vlc::Stopped);
    return 0;
}
void VideoPlayer::setAudioState(int state)
{
//    enum State {
//        Idle,
//        Opening,
//        Buffering,
//        Playing,
//        Paused,
//        Stopped,
//        Ended,
//        Error
//    };
    switch(state)
    {
        case Vlc::Playing:
            _audioplayer->play();
            break;
        case Vlc::Paused:
            _audioplayer->pause();
            break;
        case Vlc::Stopped:
            _audioplayer->stop();
            break;
        default:
            break;
    }
}

int VideoPlayer::pause()
{
    qDebug() << _audioplayer->state();

//    if(!ispaused)
//    {
        _player->pause();
        if((_audioplayer->state()!=Vlc::Stopped)|(_player->state()!=Vlc::Stopped))
            _audioplayer->pause();
        ispaused = true;
        return 0;
//    }
//    else
//    {
//        _player->play();
//        if(_audioplayer->state()!=Vlc::Stopped)
//            _audioplayer->play();
//        ispaused = false;
//        return 1;
//    }
//    qDebug() << _audioplayer->state();
//    qDebug() << _audioplayer->currentMedia()->currentLocation();


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
int VideoPlayer::getAudioIconState()
{
    int state=0;
    switch (_audioplayer->state())
    {
        case Vlc::Playing:
            state = 2;
            break;
        case Vlc::Paused:
            state = 1;
            break;
        case Vlc::Stopped:
            state = 0;
            break;
        default:
            state = 0;
            break;
    }
    qDebug() << "current audio state is" << state;
    return state;
}

int VideoPlayer::getAudioState()
{
    return _audioplayer->state();
}

int VideoPlayer::getVideoState()
{
    return _player->state();
}

void VideoPlayer::togglePause()
{
    _player->togglePause();
    qDebug() << _audioplayer->state();
//    qDebug() << _audioplayer->state();
//    qDebug() << _audioplayer->currentMedia()->currentLocation();
    if((_audioplayer->state()!=Vlc::Stopped)|(_player->state()!=Vlc::Stopped))
        _audioplayer->togglePause();
//    setAudioState(_player->state());
}
void VideoPlayer::play()
{
    _player->play();
    qDebug() << _audioplayer->state();
//    qDebug() << _audioplayer->currentMedia()->currentLocation();
//    VlcMedia *tmpmedia = _audioplayer->currentMedia();
//    qDebug() << tmpmedia->currentLocation();
//    QString tmpstr = _audioplayer->currentMedia()->currentLocation();
    if(_audioplayer->state()!=Vlc::Stopped)
        _audioplayer->play();
//    setAudioState(Vlc::Playing);
}

void VideoPlayer::setAudioMuted(bool tf)
{
    if((_audioplayer->state()==Vlc::Playing)|(_audioplayer->state()==Vlc::Paused)|(_audioplayer->state()==Vlc::Opening)|(_audioplayer->state()==Vlc::Buffering))
    {
        if(tf)
            _audioplayer->audio()->setVolume(0);
        else
            _audioplayer->audio()->setVolume(100);
    }
}

void VideoPlayer::setAudioVolume(int vol)
{
    if((_audioplayer->state()!=Vlc::Stopped)|(_player->state()!=Vlc::Stopped))
        _audioplayer->audio()->setVolume(vol);
}
