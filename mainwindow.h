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
#include <time.h>
//#include <QMovie>
#include <qvideosurfaceformat.h>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <VideoPlayer.h>
#include <../../ASCUM_ARM/LOG_PROCESSOR/logprocessor.h>
#include <TMIinterpretator.h>
#include <QMessageBox>
#include <msgSys.h>
#include <qwt.h>
#include <qwt_thermo.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_engine.h>
#include <QCheckBox>
//    T getValByIndex();
class MyThread:public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    QTimer *Timer;
signals:
    void tick();
public slots:
    void timerTick();
    void stopTimer();
    void setTimerInterval(int ms);
    void restartTimer();
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
#endif

public:
    #define smallTableID 0x80000012
    #define bigTableID 0x80000011
    #define localizationTableID 0x00000001

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
    //form funcs
    QMessageBox newMessage;
    QVector <QwtThermo*> parameterBar;
    int initSlider(int);
    int initColoredScale(char*, int length);
    int initBigThermos(int qty);
    int initSmallThermos(int qty, QVector <QString>, QVector<long> maxs);
    //log funcs
    logProcessor *log;
    TMIinterpretator *interpreter;
    msgSys *msys;
    bool inverseTime=false;
    QString playingFile1,playingFile2;
    int openedFileIndex;
    QStringList logList;
    QStringList videoList;
    QString parname;
    int lastRecNum = 0;
    QVector <time_t> timeSegment;                                           // this qvector is used to navigate in all times using time
    QTimer *timer;
    QTimer *delayTimer;
    MyThread *thrd;
    QVector <QLabel*> thermoVals;
    bool playingModePlayer1=false;
    bool playingModePlayer2 = false;
    bool player1Paused = false;
    bool player2Paused = false;
    int LogFileError=1,VideoFileError=1;
    bool isVideo1Opened;
    bool isVideo2Opened;
    int tickCounter;
    int videoDelayms;
    char tmpFHPtr[40];
    int openLogFilesFolder(QStringList *);//also we have to set some kind of sorting here, but the best choice is to set that sorting in the function
    int openVideoFilesFolder(QStringList *);//also we have to set some kind of sorting here, but the best choice is to set that sorting in the function
    int openLogFile(int logIndex);                                          //fileIndex is index of file in the QStringList logList
    int readHeadTableData();
    int readTimeEdges(time_t *beginTime, time_t *endTime);                  // getting starting and ending times of the log to create one global tim axis
    int checkTimePointExistance(time_t);                                    // check if point with time value from global time axis is enabled
    int updateThermos(dataParams dp);
    int createFakeTimeScale();                                              // here is matching of timeSegment on qslider taking place
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
    int initThermoNames(QVector <QString> *);

    int checkVideoFilesExistance(QString path);
    int checkLogFilesExistance(QString path);
    int videoFileSelector(int camIndex, int lastOpenedFileIndex);
    int openVideoFile(QString filename1, QString filename2);
    int changeVideo1(QString filename);
    int changeVideo2(QString filename);
    void setButtonPanelEnabled(bool tf);

    //addition to struct dataParams
    int getDataType(int index);
    int getBeforeIndex(int videoIndex);
    int getTypeIndex(int index);
    int makeStructFromRecord(char *record, dataParams *);

    //config funcs
    QString logWorkingDir = "",videoWorkingDir = "";
    void setFolderWFiles(QString);
    void selectVideoFolder();
    void selectLogFolder();
    int createLogConfigFile(QString logpath);
    int createVideoConfigFile(QString videopath);
    int openLogConfigFile(QString *);
    int openVideoConfigFile(QString *);
    int updateConfigFile(QString);
private slots:
//    int getNextFileName();
//    int getNextFileSameName();
    void setPlayer1ModePlaying();
    void setPlayer2ModePlaying();
    void setPlayer1ModePaused();
    void setPlayer2ModePaused();
    void pausePlayer1();
    void playBothPlayers();
    void updateTime();
    void on_pushButton_clicked();
    void videoEnded();
    void on_action_2_triggered();
    void delayTimerTick();
    void on_playButton_clicked();
    void startDelayTimer();
    void stopDelayTimer();
    void on_stopButton_clicked();
    bool checkVideosSynchronized();

    void on_timeEdit_editingFinished();

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_nextTimeSegment_clicked();
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
