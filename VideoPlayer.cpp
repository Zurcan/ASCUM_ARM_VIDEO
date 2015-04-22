#include <VideoPlayer.h>
#include <QString>
#include <QDebug>
#include <QFile>


void VideoPlayer::defineVideo(QObject *parent, QWidget *videoparent1/*, QWidget *videoparent2*/)
{

    QStringList args;
    args.append("--no-video-title-show");
    args.append("--sub-filter=marq");
    args.append("--file-caching=120000");
    args.append("--clock-synchro=0");
    args.append("--clock-jitter=0");
    args.append("--sout-smem-time-sync");
    _instance = new VlcInstance(args,parent);
    int x1,y1,x2,y2;
    _player = new VlcMediaPlayer(_instance);
    video = new VlcWidgetVideo(_player,videoparent1);
    video->setMediaPlayer(_player);
    _audioinstance = new VlcInstance(VlcCommon::args(),parent);
    _audioplayer = new VlcMediaPlayer(_audioinstance);
    QSize tmpSize;
    qDebug() << "videoparent1" << videoparent1->objectName();
    videoparent1->geometry().getCoords(&x1,&y1,&x2,&y2);
    tmpSize = videoparent1->geometry().size();
    QRect tmpgeometry;
    tmpgeometry.setSize(tmpSize);
    tmpgeometry.setCoords(x1,y1,x2,y2);
    video->setGeometry(tmpgeometry);
    _player->setVideoWidget(video);
    video->show();
    someVideo = new VlcVideo(_player);
}

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
    if(somefile.size()<10000)
    {
        _player->stop();
        return 2;
    }
    _media = new VlcMedia(QString::fromLocal8Bit(file.toLocal8Bit()), true, _instance);
    _player->open(_media);
    QString audiofile =file;
    audiofile.chop(3);
    audiofile.append("wav");
    QFile audio;
    audio.setFileName(audiofile);
    if(!audio.exists())
        qDebug() << "no such file";
    _audioplayer->stop();
    _audio = new VlcMedia(audiofile,true,_audioinstance);
    if(audio.exists())
    {
        _audioplayer->open(_audio);
        _audioplayer->audio()->setVolume(100);
        _audioplayer->togglePause();
    }
    else
    {
        _audioplayer->stop();

    }
    if(_player->state()==7)
    {
        return 2;
    }
    while(_player->state()==1)
    {
//            return 2;
    }
    _player->play();
    if(_player->state()==7)
    {
        return 2;
    }
    while(_player->state()!=3)
    {
        if(_player->state()==7)
        {
            return 2;
        }
    }
    _player->togglePause();
    if(_player->state()==7)
    {
        return 2;
    }
    while(_player->state()!=4)
    {
        if(_player->state()==7)
        {
            return 2;
        }
    }
    _player->togglePause();
    someVideo = new VlcVideo(_player);
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
        _player->pause();
        if((_audioplayer->state()!=Vlc::Stopped)|(_player->state()!=Vlc::Stopped))
            _audioplayer->pause();
        ispaused = true;
        return 0;
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
    if((_audioplayer->state()!=Vlc::Stopped)|(_player->state()!=Vlc::Stopped))
        _audioplayer->togglePause();
    if(_player->state()==Vlc::Playing)
        ispaused = false;
    else if(_player->state()==Vlc::Paused)
        ispaused = true;
}
void VideoPlayer::play()
{
    _player->play();
    if(_audioplayer->state()!=Vlc::Stopped)
        _audioplayer->play();
    ispaused = false;
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

void VideoPlayer::setPlayerTime(int ptime)
{
    _player->setTime(ptime);

}

void VideoPlayer::setAudioVolume(int vol)
{
    if((_audioplayer->state()!=Vlc::Stopped)|(_player->state()!=Vlc::Stopped))
        _audioplayer->audio()->setVolume(vol);
}

bool VideoPlayer::isSoundEnabled()
{
    if((_audioplayer->state()==Vlc::Stopped)|(_audioplayer->state()==Vlc::Idle)|(_audioplayer->state()==Vlc::Error)|(_audioplayer->state()==Vlc::Ended))
        return false;
    else return true;
}
