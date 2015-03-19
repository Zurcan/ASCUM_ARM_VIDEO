#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLayout>
#include <NcFramelessHelper.h>
#include <QtMultimedia/QMediaObject>
#include <QtGui>
#include <QTableWidget>
//#include <QtMultimedia/QAudioDeviceInfo>
//#include <QtMultimedia/QVideoDeviceSelectorControl>
//#include <QtMultimedia/QAudioBuffer>
//#include <QMultimedia>
//#include <QtMultimediaWidgets/QVideoWidget>
//#include <QtMultimedia>
//#include <QtMultimedia/QVideoFrame>
//#include <QtMultimedia/QMediaPlayer>
#include <time.h>
//#include <QMovie>
//#include <qvideosurfaceformat.h>
//#include <QMediaPlaylist>
#include <QFileDialog>
#include <QStyledItemDelegate>
#include <VideoPlayer.h>
#include <../../ASCUM_ARM/LOG_PROCESSOR/logprocessor.h>
#include <TMIinterpretator.h>
#include <QMessageBox>
#include <msgSys.h>
#include <qwt.h>
#include <qwt_thermo.h>
#include <qwt_text_label.h>
#include <QLineEdit>
#include <QLine>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
//#include <qwt_scale_draw.h>
//#include <qwt_scale_engine.h>
#include <QCheckBox>
#include <QEventLoop>
#include <math.h>
#include <QMap>
#include <QTextCodec>
#include <QMutex>
#include <qwt_scale_div.h>
#include <qwt_scale_map.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_draw.h>
#include <../../flyingFrame/FlyingFrame.h>
//#include <FlyingFrame.h>
//#include <qwt_math.h>
//#include <qwt_painter.h>
//#include <qpen.h>
//#include <qpainter.h>
//#include <qmatrix.h>
//#include <qwt_global.h>
//#include <qwt_text_label.h>
//#include <qwt_dyngrid_layout.h>
#include <qwt_slider.h>
#include <QLine>
//    T getValByIndex();


class ThreadWorker:public QObject
{
    Q_OBJECT
public:
    ThreadWorker();
    virtual ~ThreadWorker();
    int tickCounter;
    QTimer *Timer;
    void startTimer(int step);
    void stopTimer();
    void initWorker();
public slots:
    void synchroTickFromThread(int);
    void timerTick();
//    void ticksFromThread(int);
signals:
    void ticksToThread(int);
    void finished();



};
class BackgroundDelegate : public QStyledItemDelegate
{
public:
    explicit BackgroundDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const
    {
        // Fill the background before calling the base class paint
        // otherwise selected cells would have a white background
        QVariant background = index.data(Qt::BackgroundRole);
        if (background.canConvert<QBrush>())
            painter->fillRect(option.rect, background.value<QBrush>());

        QStyledItemDelegate::paint(painter, option, index);

        // To draw a border on selected cells
        if(option.state & QStyle::State_Selected)
        {
            painter->save();
            QPen pen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
            int w = pen.width()/2;
            painter->setPen(pen);
            painter->drawRect(option.rect.adjusted(w,w,-w,-w));
            //painter->drawRect(0,100,200,300);
            painter->restore();
        }
    }
};
//class VideoSlider: public QwtSlider
//{
//    Q_OBJECT
//public:
//     VideoSlider( QWidget *parent/*,
////                        Qt::Orientation = Qt::Horizontal,
//             //                        ScalePos = NoScale, BackgroundStyles = Trough */);
//     ~VideoSlider();
////protected:
////   virtual void drawHandle( QPainter *painter,const QRect &sliderRect, int pos ) const;
////private:
////    class PrivateData;
////    PrivateData *d_data;
//};

class MapTimeScaleDraw: public QwtScaleDraw
{
public:
MapTimeScaleDraw(QString fmt) : format(fmt) { }


virtual QwtText label(double v) const
{
    QwtText retVal;
    QDateTime upTime = QDateTime::fromTime_t(timeArr[(int)v]).toUTC();

   if(v==0)
   {
       retVal = upTime.toString("hh:mm:ss");
//       retVal = upTime
       return retVal;
   }

   else return upTime.toString(format);
}
void setTimeArr(time_t *t,int l)
{
    timeArr = t;
    timeArrLength = l;
}
void setTimeArrayDelta(int val)
{
    timeArrDelta = val;
    qDebug() << "timeArrDelta"<<val;
}

private:
const QString format;
time_t *timeArr;
int timeArrLength;
int timeArrDelta;

//void setLabelAlignment( Qt::Alignment );
protected:
virtual void drawLabel(QPainter *painter, double value) const;

};

class TableWidget:public QTableWidget
{
    Q_OBJECT
public:
    TableWidget();

};

class MyThread:public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
//    MyThread();
    QEventLoop *loop;
    int timerTicks;
    ThreadWorker *worker;
signals:
    void tickOut(int);
    void tickIn(int);
public slots:
//    void setTimerZero();
//    void timerTick();
//    void stopTimer();
//    void setTimerInterval(int ms);
//    void restartTimer();
    void getTicksFromWorker(int);
    void synchroTick(int ms);
private:
    void run();

};

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT
#define GLOBALMODE //ifndef its debug else -release
//    NcFramelessHelper *fh1;
//    NcFramelessHelper *fh2;
    QWidget *videoScreen1;
    QWidget *videoScreen2;
    QHBoxLayout *videoLayout1;
    QHBoxLayout *videoLayout2;
    QPushButton *logButton;
    QPushButton *videoButton;
    QCheckBox *logCheck;
    QCheckBox *videoCheck;

//    QMediaPlayer *videoPlayer1;
//    QMediaPlayer *videoPlayer2;
#ifdef GLOBALMODE
    VideoPlayer *vplayer;
    VideoPlayer *vplayer2;
    QwtSlider *sli;

#endif

public:
    #define smallTableID 0x80000012
    #define bigTableID 0x80000011
    #define localizationTableID 0x00000001
    #define camOffsetsTableID 0x80000081
    #define mainTimerInterval 10
    explicit MainWindow(QWidget *parent = 0);

    struct dataParams
    {
        QVector <time_t> time;                          //10
        QVector <double> doubleTypes;                   //34
        QVector <int> intTypes;                         //27 errors are ints too
        QVector <float> floatTypes;                     //7
        QVector <bool> flagTypes;                       //8
        QVector <int> paramsSequence;                   //contains parameter types in ints that are actual interp consts
        QVector <int> paramsVisibleArr;                 //contains parameter's displaying status 0 - invisible 1 - visible
        QVector <time_t> powOnTime;                     //4
        QVector <unsigned char> timeFract;              //0
        QVector <int> error;                            //but better if errors will be in the next variable #2727 is error


    }par;

    void openLocal();
//    void createSmallThermos();
    int fillHeadTable();
    ~MainWindow();

private:
    int tmpMaxDelay=0;
    int tmpAverage=0;
    int tmpQuantity=0;
    int tmp0MaxDelay = 0;
    int threadedTime = 0;
    int lastIndex1 = 1;
    int lastIndex2 = 2;
    int timeSegmentIterator=0;
    int maxCamOffset;
    int secondsCounter;
    int realSecondsCounter;
    int delayMs;
    int lastDelay;
    int flowingOffset;
    int stateTimerTickCounter=0;
    int tickCounter;
    int videoDelayms;
    int logVideoDelta;
    int logVideoDeltaCounter;
    int lastRecNum = 0;
    int openedFileIndex;
    int LogFileError=1,VideoFileError=1;
    int getTimeTickCounter;
    int widget1X;
    int widget1Y;
    int lastVal;
    int delayMsToSet = 0;
    int sound1IconState = 0;//current state of sound on screen1 it may be in 3 states 0 - no soundtrack, 1 = soundtrack muted, 2 = soundtrack playing
    int sound2IconState = 0;//same as above

    bool firstPass = true;
    bool videoOnly = true;
    bool offsetsAvailable = true;
    bool player1Playing=false;
    bool player2Playing = false;
    bool player1Paused = false;
    bool player2Paused = false;
    bool player1Opening = false;
    bool player2Opening = false;
    bool playButtonPressed = false;
    bool isVideo1Opened;
    bool isVideo2Opened;
    bool playersStatesSynchronized = false;
    bool isSliderPressed=false;
    bool isFolderOpened;
    bool readyToPlay = false;
    bool accepted = false;
    bool canMoveSeeker = false;
    bool seekerIsBusy = false;

    char tmpFHPtr[40];
    int pageIndex;
    QThread *mythread;
    MyThread *someThread;
    ThreadWorker *worker;
    QMutex mutex;

    QTimer *timer;
    QTimer *delayTimer;
    QTimer *stateTimer;
    QTimer *waitEndStateTimer;
    QTimer *simpleDelayTimer;
    QTimer *getTimeTimer;
    QTimer *threadTimer;
    QTimer *showCameraNameTimer;

    QRect currentWidget1Geometry;
    QRect currentWidget2Geometry;
    QSize baseVideo1Size;
    QRect baseVideo1Geometry;
    QSize baseVideo2Size;
    QRect baseVideo2Geometry;
    QLine *line1,*line2,*line3,*line4;


    //form funcs
    QMessageBox newMessage;
    QVector <QwtThermo*> parameterBar;
    QVector <QCheckBox*> checkBoxes;
    QVector <QLineEdit*> thermoVals;
    int initSlider(int);
    int initColoredScale();
    int initBigThermos(int qty);
    int initSmallThermos(int qty, QVector <QString>, QVector<long> maxs, QVector<int> dataSequence);
    void setButtonsEnable(bool tf);
    //log funcs
    logProcessor *log;
    TMIinterpretator *interpreter;
    MapTimeScaleDraw *mapTimeScale;
//    VideoSlider *vslider;
    msgSys *msys;
    bool inverseTime=false;
    QString playingFile1,playingFile2;
    QStringList logList;
    QStringList videoList;
    QMap <QString, int> videosFullInfo;  //consists of video file name + cam offset; each camera each timeSegment has different offset, so it's a good idea, i guess, to create such QMap
    QString parname;
    unsigned char beginTimeFract,endTimeFract;
    unsigned char camQty;
    int videoTimeGlobalIterator;

    QVector <time_t> timeSegment;                 // this qvector is used to navigate in all times using time; it is so because it's easy to navigate through it using simple iterator (each 2 members are 1 segment)
    QVector <int> camOffsets;                     // on the other hand it is very usable to navigate exectly through members, because time navigation is not safe due to time overlay is possible
    QVector <short> timeFracts;
    QVector <int> videoTimes;
    QVector <int> logEndTimes;
    QVector <int> offsetsCounter;
//    QVector <float> columnWidthes;                //relative to total time length column width
//    QVector <int> pageVector;                     //consists of ints each of it means what pageIndex is in current cell
//    QVector <int> pageFlagVector;                 //consists of ints each of it means what behaviour should be at current cell processing 0 - play video 1 - show parameters 2 - ok do nothing 3 - error do nothing
//    QVector <int> pageEndTimes;                 //contains start times of each cell
//    QVector <QWidget> coloredBars;

//    FlyingFrame *myFrame;
//    MyThread *thrd;
    struct dataPage
    {
        time_t timeEdge1;
        time_t timeEdge2;
        short TimeFract1;
        short TimeFract2;
        time_t logTimeEdge2;
        QVector <int> videoTimeEdges;           // maximal video length
        QMap <QString,bool> videoVector;        //video and its availability
        QString logName;
        int camOffsetAmount;
        QVector <int> camTimeOffsets;
    };

    struct tableCell
    {
        time_t beginTime;
        time_t endTime;
        int cellType;
        float relativeWidth;
        int currentPage;
        int colWidth;
        int donor;              //0=not donor not acceptor, 1 = donor, 2 = acceptor;

    };
    QVector <tableCell> timeCells;
    QVector <dataPage> dataMap;
    int timeCellIndex;

    int openLogFilesFolder(QStringList *);//also we have to set some kind of sorting here, but the best choice is to set that sorting in the function
    int openVideoFilesFolder(QStringList *);//also we have to set some kind of sorting here, but the best choice is to set that sorting in the function
    int openLogFile(QString filename);                                          //fileIndex is index of file in the QStringList logList
    int readHeadTableData();
    int readTimeEdges(time_t *beginTime, time_t *endTime/*, unsigned char *beginTimeFract, unsigned char *endTimeFract*/);                  // getting starting and ending times of the log to create one global tim axis
    int checkTimePointExistance(time_t);                                    // check if point with time value from global time axis is enabled
    int updateThermos(dataParams dp);
    int createFakeTimeScale(int mode, int column);                                              // here is matching of timeSegment on qslider taking place
    bool checkFileHeaderCRC(QString filename);
    bool createTimeSegment(QStringList *listOfLogs);                        //here is creating of timeSegment vector
    bool checkfunc(time_t *, time_t *);
    int disassembleLogRecord();
    QTime getVideoTime();                                                   //gets current time of the video with ms to compare with logTime
    time_t getNextLogTime(int currentRecord);                               //gets next record's time
    int getRecordNumClosestToTime(time_t currentTime, int timeFract, int lastRecord);//returns number of record closest to given time also we can recieve record
    int checkIsThereTimeFract(time_t);                                      //search for time fracts returns quantity of timeFracts
    int findTimeSegment(int);
    int initThermoMaxs(QVector <long> *);
    int initThermoNames(QVector <QString> *, QVector<int> *dataSequence);
    int setPlay();
    int setPause();
    int checkVideoFilesExistance(QString path);
    int checkLogFilesExistance(QString path);
    int videoFileSelector(int camIndex, int lastOpenedFileIndex);
    int openVideoFile(QString filename1, QString filename2);
    int changeVideo1(QString filename);
    int changeVideo2(QString filename);
    void moveToNextTimeFrame();
    void setButtonPanelEnabled(bool tf);
    int createDataMap();
    int createFullListOfVideos(int offsetsQty);

    //addition to struct dataParams
    int getDataType(int index);
    int getBeforeIndex(int videoIndex);
    int getTypeIndex(int index);
    int makeStructFromRecord(char *record, dataParams *);
    bool synchronizePlayersStates();

    //config funcs
    QString logWorkingDir = "",videoWorkingDir = "";
    void setFolderWFiles(QString);
    void setHSliderPosOnButtonPress(QMouseEvent *me);
    void selectVideoFolder();
    void selectLogFolder();
    int createLogConfigFile(QString logpath);
    int createVideoConfigFile(QString videopath);
    int openLogConfigFile(QString *);
    int openVideoConfigFile(QString *);
    int updateConfigFile(QString);
    void moveToAnotherTimeSegment(int);
    void getCellAndTimeToMoveTo(int, int );
    void getDelayMsToSet(int, int );
private slots:
//    int getNextFileName();
//    int getNextFileSameName();
    void clearParTable();
    void resizeEvent(QResizeEvent *);
    void waitEndStateTimerTick();
    void getThreadedTicks(int);
    void correctFramePosition();
    void correctCellSeekerPosition(int newPos);
    void terminateAll();
    int checkFolderName(QString);
    void toggleSoundState(int count);
    void setSoundIconState(int,int);
    void updateSoundMode();
    void setSoundIcons();
//    void waitVideo2EndMode();
    void simpleDelayTimerTick();
    void setPlayer1ModePlaying();
    void setPlayer2ModePlaying();
    void setPlayer1ModePaused();
    void setPlayer2ModePaused();
    void setPlayer1State();
    void setPlayer2State();
    void setSliderPosition();
    bool checkVideosSynchronized();
    void setPlayer1ModeOpening();
    void setPlayer2ModeOpening();
    void pausePlayer1();
    void playBothPlayers();
    void updateTime();
    void on_pushButton_clicked();
    void video1Ended();
    void video2Ended();
    void on_action_2_triggered();
    void delayTimerTick();
    void on_playButton_clicked();
    void startDelayTimer();
    void stopDelayTimer();
    void on_stopButton_clicked();
    void on_timeEdit_editingFinished();
    void stateTimerTick();
    void on_timeEdit_userTimeChanged(const QTime &time);
    int readCamOffsetsAndTimeEdges(time_t *beginTime, time_t *endTime, unsigned char *beginTimeFract, unsigned char *endTimeFract,int globalIterator);
    void on_nextTimeSegment_clicked();
    void getTimeTimerTick();
    void createCellVector();            // creating table widget cell begin and end times X=begin Y=end

#ifdef GLOBALMODE
    void setVideoTime();
#endif

    void on_action_triggered();

    void on_previousTimeSegment_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_action_4_triggered();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_horizontalSlider_sliderMoved(int position);

    void on_frameBackwardButton_clicked();

    void on_nextFrameButton_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_sliderPressed();
    void on_timeEdit_timeChanged(const QTime &time);

    void on_tableWidget_cellChanged(int row, int column);

//    void on_tableWidget_clicked(const QModelIndex &index);

    void on_horizontalSlider_actionTriggered(int action);

//    void on_tableWidget_cellClicked(int row, int column);
//    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

//    void on_tableWidget_cellClicked(int row, int column);

    void on_screen1SoundButton_clicked();

    void on_screen2SoundButton_clicked();

protected:
    void paintEvent(QPaintEvent *);

public slots:
        bool eventFilter(QObject *, QEvent *);
signals:

    void sendTicksToWorker(int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
