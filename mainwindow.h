#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLayout>
#include <NcFramelessHelper.h>
#include <QtMultimedia/QMediaObject>
#include <QtGui>
#include <QTableWidget>
#include <time.h>
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
#include <qwt_slider.h>
#include <QLine>


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
               const QModelIndex &index) const;

};


class MapTimeScaleDraw: public QwtScaleDraw
{
    public:
    MapTimeScaleDraw(QString fmt) : format(fmt) { }
    virtual QwtText label(double v) const;
    void setTimeArr(time_t *t,int l);
    void setTimeArrayDelta(int val);
    private:
    const QString format;
    time_t *timeArr;
    int timeArrLength;
    int timeArrDelta;
    protected:
    virtual void drawLabel(QPainter *painter, double value) const;

};

//class MyThread:public QThread
//{
//    Q_OBJECT
//public:
//    explicit MyThread(QObject *parent = 0);
//    QEventLoop *loop;
//    int timerTicks;
//    ThreadWorker *worker;
//signals:
//    void tickOut(int);
//    void tickIn(int);
//public slots:
//    void getTicksFromWorker(int);
//    void synchroTick(int ms);
//private:
//    void run();

//};

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
    int currentCam1Index = 0;
    int currentCam2Index = 0;

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
    bool summaryIsHidden = false;
    bool currentStatsAreHidden = false;
    bool isPaused = false;
    bool pauseDelayFinished = false;

    char tmpFHPtr[40];
    int pageIndex;
    QThread *mythread;
//    MyThread *someThread;
    ThreadWorker *worker;
    QMutex mutex;

    QTimer *timer;
//    QTimer *delayTimer;
    QTimer *waitEndStateTimer;
//    QTimer *simpleDelayTimer;
    QTimer *getTimeTimer;
    QTimer *threadTimer;
    QTimer *showCameraNameTimer;
    QTimer *hideSummarySeamlessTimer;
    QTimer *syncroTimer;
    QTimer *pauseDelayTimer;

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
    int initColoredScale();
    int initBigThermos(int qty);
    int initSmallThermos(int qty, QVector <QString>, QVector<long> maxs, QVector<int> dataSequence);
    void setButtonsEnable(bool tf);
    //log funcs
    logProcessor *log;
    TMIinterpretator *interpreter;
    MapTimeScaleDraw *mapTimeScale;
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
    int hideSummaryCounter;
    QIcon *tmpIcon;

    QVector <time_t> timeSegment;                 // this qvector is used to navigate in all times using time; it is so because it's easy to navigate through it using simple iterator (each 2 members are 1 segment)
    QVector <int> camOffsets;                     // on the other hand it is very usable to navigate exectly through members, because time navigation is not safe due to time overlay is possible
    QVector <short> timeFracts;
    QVector <int> videoTimes;
    QVector <int> logEndTimes;
    QVector <int> offsetsCounter;

    struct cameraButton
    {
        QPushButton *camButton;
        bool enabled;
        bool active;
    };
    QVector <cameraButton> camButtons1;
    QVector <cameraButton> camButtons2;
    QGridLayout *camButtonsLayout1;
    QGridLayout *camButtonsLayout2;


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

    struct savedVStats
    {
        int video1Status;
        int video2Status;
        bool mythreadStatus; //true means running, false means exit
        bool dataUpdated;
    };

    QVector <tableCell> timeCells;
    QVector <dataPage> dataMap;
    savedVStats savedVideoStats;
    int timeCellIndex;
    int keyboardKey;

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
    int disassembleLogRecord();
    QTime getVideoTime();                                                   //gets current time of the video with ms to compare with logTime
    time_t getNextLogTime(int currentRecord);                               //gets next record's time
    int getRecordNumClosestToTime(time_t currentTime, int timeFract, int lastRecord);//returns number of record closest to given time also we can recieve record
    int checkIsThereTimeFract(time_t);                                      //search for time fracts returns quantity of timeFracts
    int initThermoMaxs(QVector <long> *);
    int initThermoNames(QVector <QString> *, QVector<int> *dataSequence);
    int setPlay();
    int setPause();
    int checkVideoFilesExistance(QString path);
    int checkLogFilesExistance(QString path);
    int openVideoFile(QString filename1, QString filename2);
    void moveToNextTimeFrame();
    void setButtonPanelEnabled(bool tf);
    int createDataMap();
    int createFullListOfVideos(int offsetsQty);
    int calculateMaxOffset();

    //addition to struct dataParams
    int makeStructFromRecord(char *record, dataParams *);

    //config funcs
    QString logWorkingDir = "",videoWorkingDir = "";
    void setHSliderPosOnButtonPress(QMouseEvent *me);
    void selectVideoFolder();
    void selectLogFolder();
    int createLogConfigFile(QString logpath);
    int createVideoConfigFile(QString videopath);
    void moveToAnotherTimeSegment(int, int state1, int state2);
    void getCellAndTimeToMoveTo(int, int );
    void getDelayMsToSet(int, int );
    void setCameraButtonsToDefault();
    void makeUpSlider();
    void updateCamWidgetsState();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
private slots:
    int updateCameraButtons1(int number);
    int updateCameraButtons2(int number);
    void setCamera1(int index,int state);
    void setCamera2(int index, int state);
    void pushCameraButton();
    void clearParTable();
    void resizeEvent(QResizeEvent *);
    void correctFramePosition();
    void correctCellSeekerPosition(int newPos);
    void terminateAll();
    int checkFolderName(QString);
    void toggleSoundState(int count);
    void setSoundIconState(int,int);
    void updateSoundMode();
    void setSoundIcons();
    void hideSummaryTimerTick();
    void syncroTimerTimeout();
    void pauseDelayTimerTimeout();
    void prepareVideoMarque();

    void setSliderPosition();

    void updateTime();

    void on_pushButton_clicked();

    void on_action_2_triggered();

    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_timeEdit_editingFinished();

    int readCamOffsetsAndTimeEdges(time_t *beginTime, time_t *endTime, unsigned char *beginTimeFract, unsigned char *endTimeFract,int globalIterator);

    void createCellVector();            // creating table widget cell begin and end times X=begin Y=end

    void on_action_triggered();

    void on_action_4_triggered();

    void on_nextFrameButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_horizontalSlider_sliderPressed();
    void on_timeEdit_timeChanged(const QTime &time);

    void on_tableWidget_cellChanged(int row, int column);

    void on_horizontalSlider_actionTriggered(int action);

    void on_screen1SoundButton_clicked();

    void on_screen2SoundButton_clicked();

    void on_hideSummary_clicked();


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
