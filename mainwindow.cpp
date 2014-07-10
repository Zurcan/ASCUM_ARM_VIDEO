#include "mainwindow.h"
#include "ui_myform.h"

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{

}

void MyThread::run()
{
    Timer = new QTimer;
    QEventLoop loop(this);
    Timer->start(25);
    connect(Timer,SIGNAL(timeout()),this,SLOT(timerTick()));
    exec();
}

void MyThread::timerTick()
{

   // qDebug() << QDateTime::currentDateTime();
    //here we have to emit some signal
    emit tick();

}

void MyThread::setTimerInterval(int ms)
{
    Timer->setInterval(ms);
}

void MyThread::stopTimer()
{
    Timer->stop();
}

void MyThread::restartTimer()
{
    Timer->start();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    videoButton = new QPushButton("");
    videoCheck = new QCheckBox("");
    logButton = new QPushButton("");
    logCheck = new QCheckBox("");
    videoButton->setMaximumWidth(25);
    videoButton->setMinimumWidth(25);
    videoButton->setMaximumHeight(25);
    videoButton->setMinimumHeight(25);
    videoButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    logButton->setMaximumWidth(25);
    logButton->setMinimumWidth(25);
    logButton->setMaximumHeight(25);
    logButton->setMinimumHeight(25);
    logButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    videoCheck->setEnabled(false);
    logCheck->setEnabled(false);
    ui->horizontalLayout_5->addWidget(logButton);
    ui->horizontalLayout_5->addWidget(ui->lineEdit_2);
    ui->horizontalLayout_5->addWidget(logCheck);
    ui->horizontalLayout_5->addWidget(videoButton);
    ui->horizontalLayout_5->addWidget(ui->lineEdit);
    ui->horizontalLayout_5->addWidget(videoCheck);
    ui->lineEdit->setText("Выберите директорию с видео файлами");
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setText("Выберите директорию с лог-файлами");
    ui->lineEdit_2->setEnabled(false);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
       ui->nextTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
           ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
               ui->previousTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
                    ui->frameBackwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
                        ui->nextFrameButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
//               GLOBALMODE = debmode;
    ui->Thermo->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
    ui->Thermo_2->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateTime()));
    #ifdef GLOBALMODE
    videoLayout1 = new QHBoxLayout;
    vplayer = new VideoPlayer;
    delayTimer = new QTimer(this);
    vplayer->defineVideo(this,ui->widget);
    ui->widget->setLayout(videoLayout1);
    videoLayout2 = new QHBoxLayout;
    vplayer2 = new VideoPlayer;
    vplayer2->defineVideo(this,ui->widget_2);
    connect(delayTimer,SIGNAL(timeout()),this,SLOT(delayTimerTick()));
    connect(videoButton,SIGNAL(clicked()),this,SLOT(on_action_4_triggered()));
    connect(logButton,SIGNAL(clicked()),this,SLOT(on_action_triggered()));
    connect(vplayer->_player,SIGNAL(timeChanged(int)),this,SLOT(setVideoTime()));
    connect(vplayer->_player, SIGNAL(end()),this,SLOT(videoEnded()));
    connect(vplayer2->_player, SIGNAL(end()),this,SLOT(videoEnded()));
    connect(vplayer->_player,SIGNAL(playing()),this,SLOT(setPlayer1ModePlaying()));
    connect(vplayer2->_player,SIGNAL(playing()),this,SLOT(setPlayer2ModePlaying()));
    connect(vplayer->_player,SIGNAL(paused()),this,SLOT(setPlayer1ModePaused()));
    connect(vplayer2->_player,SIGNAL(paused()),this,SLOT(setPlayer2ModePaused()));

//    connect(vplayer->_player,SIGNAL(paused()),vplayer2->_player,SLOT(pause()));
//    connect(vplayer2->_player,SIGNAL(paused()),vplayer->_player,SLOT(pause()));
//    ui->horizontalLayout_6->setEnabled(false);
    #endif
//    this->setEnabled(false);
//    ui->menuBar->setEnabled(true);
//    ui->menu->setEnabled(true);
    initSlider(24);
    char videos[24];
    for (int i = 0; i < sizeof(videos);i++)
        videos[i]=i%2;
    initColoredScale(videos,sizeof(videos));
//    loadConfigFile();
//    QString tmpstr;
    setButtonPanelEnabled(false);
//    openLogConfigFile(&logWorkingDir);
//    openVideoConfigFile(&videoWorkingDir);
//    openVideoFilesFolder(&videoList);
//    qDebug() << videoList;

    log = new logProcessor;
    interpreter = new TMIinterpretator;
    msys = new msgSys;
    isVideo1Opened = false;
    isVideo2Opened = false;

//    thread.exec();
//    thread.run();
//    for(int i = 0; i < 8; i++)
//    {
//        QPushButton *tmpButton = new QPushButton(QString::number(i,10));
//        ui->gridLayout_2->addWidget(tmpButton,i/4,i%4);
//    }

//    qDebug() << getValByIndex(i++);
//    qDebug() << getValByIndex(i++);
//    qDebug() << getValByIndex(i++);
//    //qDebug() << QString::fromUtf8(workingDir.toLocal8Bit());
//    workingDir = tmpstr;

}
//template <typename T>
//T MainWindow::getValByIndex();
//    {
//        T ret = 10;
//        return ret;
//    }

int MainWindow::videoFileSelector(int camIndex, int lastOpenedFileIndex) // returns index of filename in videolist to be opened as videofile
{
    //if lastOpenedFileIndex is -1, it means that no file was opened before
    int nextFileIndex=0;

    QString lastFile = "";
    QString camName = ""; //if camindex is 0, it means that no camera is selected
    //check if playing file is finished
    int jumpindex =0;
//    if(vplayer->)
    //check if camIndex didn't changed

    if(!camIndex)
        return -1;
    else
    {
        camName.append((char)camIndex+0x30);
        qDebug() << "camName"<<camName;
    }
    if(lastOpenedFileIndex!=-1)
    {
        lastFile = videoList[lastOpenedFileIndex];
        qDebug() << lastFile;
     //check if camIndex didn't changed
//        QByteArray tmparr = lastFile.toLocal8Bit();
        int tmpIndexOfMkv = lastFile.indexOf(".mkv");
        int beforeindex = (int)lastFile.toLocal8Bit()[tmpIndexOfMkv-1]-0x30;
        int deltaindex=0;
//        beforeindex = (int)tmparr[3];
        qDebug() << beforeindex;
//        if(beforeindex!=camIndex)//it means that camera is changed so we need to calculate delta index
//        {
            deltaindex = beforeindex-camIndex;
            qDebug() << deltaindex;
//        }
        if(lastOpenedFileIndex+5>=videoList.size())
            return -2;
        else
            return lastOpenedFileIndex+5+deltaindex+jumpindex;
    }
    return camIndex-1+jumpindex;
}

int MainWindow::initSlider(int topVal)
{

    return 0;
}


int MainWindow::initColoredScale(char *existingVideos, int length)
{

    QPalette palette = ui->tableWidget->palette();
    palette.setColor(QPalette::Base, Qt::green);
    for(int i = 0; i < length; i++)
    {
        QWidget *coloredBlock = new QWidget;//::setAutoFillBackground(true);
        coloredBlock->setAutoFillBackground(true);
        if(existingVideos[i])coloredBlock->setPalette(palette);
        ui->tableWidget->setCellWidget(0,i,coloredBlock);
    }
    return 0;
}


MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::initThermoMaxs(QVector <long> *thermoMaxs)
{

//    if(!thermoMaxs->isEmpty())
//        thermoMaxs->clear();
    int retval = 0;
    for(int i = 0; i < interpreter->interpreterRecordsCount; i++)
    {

            if((interpreter->TInterpItemArray[i].typ&0xffff) == 34 )
            {
                retval++;
                qDebug() << interpreter->TInterpItemArray[i].max;
                thermoMaxs->append(interpreter->TInterpItemArray[i].max);
            }

    }

    qDebug() << "there are maxs qty" << retval;
//    for (int i = 0; i < thermoMaxs->size(); i++)
//        qDebug() << thermoMaxs[i];
    return retval;
}

int MainWindow::initThermoNames(QVector<QString> *thermoNames)
{
    int retval = 0;
    for(int i = 0; i < interpreter->interpreterRecordsCount; i++)
    {

            if((interpreter->TInterpItemArray[i].typ&0xffff) == 34 )
            {
                retval++;
                qDebug() << interpreter->TInterpItemArray[i].name;
                thermoNames->append(interpreter->TInterpItemArray[i].name);
            }

    }
    return retval;
}

int MainWindow::getDataType(int index)
{

    return par.paramsSequence[index];
}

int MainWindow::getTypeIndex(int index)//returns type dependent index of given global struct index
{
    int retval=0;
    for(int i = 0; i < index+1; i++)
    {
        if(getDataType(index)==par.paramsSequence[i])
            retval++;
    }
    return retval;
}

int MainWindow::makeStructFromRecord(char *record,/*int recsize,*/ dataParams* dp)//lets do it
{
    time_t recTime;
    int recIndex=0;
//    qDebug() << "next step";
    //dp = new dataParams;
    dp->doubleTypes = QVector <double>(0);
    dp->error = QVector <int>(0);
    dp->flagTypes = QVector <bool>(0);
    dp->floatTypes = QVector <float>(0);
    dp->intTypes = QVector <int>(0);
    dp->paramsSequence = QVector<int>(0);
    dp->paramsVisibleArr = QVector<int>(0);
    dp->powOnTime = QVector<time_t>(0);
    dp->time = QVector<time_t>(0);
    dp->timeFract = QVector<unsigned char>(0);
    for (int i = 0; i < interpreter->interpreterRecordsCount; i++)
    {
        recIndex=interpreter->TInterpItemArray[i].offset;       //get next interp record to decode value from row record data
        switch(interpreter->TInterpItemArray[i].typ&0xffff)
        {

        case 0: //timeFracts
        {
//            QVariant tmpVar = backIndex;
            //timeFractExistFlag = true;
            //timeFract[backIndex] = interpreter->fieldChar(record[recIndex]);
            dp->timeFract.append(interpreter->fieldChar(&record[recIndex]));
            dp->paramsSequence.append(0);
            dp->paramsVisibleArr.append(0);
            break;
        }
        case 34 ://it's double
        {
            double tmpDbl;
            tmpDbl = interpreter->fieldDouble(&record[recIndex]);
            dp->doubleTypes.append((double)tmpDbl);
            dp->paramsSequence.append(34);
            dp->paramsVisibleArr.append(1);
//            qDebug() << tmpDbl;
            break;
        }
        case 7:
        {
            float tmpFloat, tmpMinFloat, tmpMaxFloat;
            int tmpIntFloat;
            tmpFloat = interpreter->fieldFloat(&record[recIndex]);
            //qDebug << tmpFloat;
            if(tmpFloat==tmpFloat)
            {
                tmpMinFloat = interpreter->TInterpItemArray[i].min/pow(10,interpreter->TInterpItemArray[i].mask_);
                tmpMaxFloat = interpreter->TInterpItemArray[i].max/pow(10,interpreter->TInterpItemArray[i].mask_);
                if((tmpMinFloat==0)&&(tmpMaxFloat==0));
                else
                {
                    if(tmpFloat!=tmpMinFloat)
                    {
                        if(tmpFloat<tmpMinFloat)tmpFloat = tmpMinFloat;
                        if(tmpFloat>=tmpMaxFloat)tmpFloat = tmpMaxFloat;
                    }
                }
                int tmpMask = interpreter->TInterpItemArray[i].mask_;
                tmpFloat = tmpFloat*pow(10,tmpMask);
                tmpIntFloat = tmpFloat;
                tmpFloat = tmpIntFloat/pow(10,tmpMask);
                //qDebug << tmpFloat;
                //Y[i-2/*-tmpInvisibleVarDecrease*/][backIndex] =  tmpFloat; //round((double)tmpFloat);
                dp->floatTypes.append(tmpFloat);
                dp->paramsSequence.append(7);
                dp->paramsVisibleArr.append(1);
            }
            else
            {
               // Y[i-2/*-tmpInvisibleVarDecrease*/][backIndex] =0;
                dp->floatTypes.append(0);
                dp->paramsSequence.append(7);
                dp->paramsVisibleArr.append(1);
//                tmpFloat=0;
            }
            break;
        }
        case 10 :
        {
            ////qDebug << interpreter->TInterpItemArray[i].name;
            recTime = (time_t)interpreter->fieldInt(&record[recIndex]);
            recTime = mktime(gmtime(&recTime));
            //                                                //qDebug << recTime;
            if(interpreter->TInterpItemArray[i].name!="PowOnTime")
            {
                dp->time.append(recTime);
                dp->paramsSequence.append(10);
                dp->paramsVisibleArr.append(0);
            }
            else
            {
                //qDebug << interpreter->TInterpItemArray[i].name;
            }
            break;
        }
        case 4://powOnTime
        {

//            powOnTimeArrayExistFlag = true;
            recTime = (time_t)interpreter->fieldInt(&record[recIndex]);
            recTime = mktime(gmtime(&recTime));
           // powOnTimeArray[backIndex] = recTime;//(int)((uint)recTime-(uint)firstPointDateTime);
            dp->powOnTime.append(recTime);
            dp->paramsSequence.append(4);
            dp->paramsVisibleArr.append(0);
            break;
        }
        case 8 :
        {


               // dateChangedArrExistFlag = true;
               // qDebug() << "DateChg";
                //dateTimeChangeIndex = i;


                    dp->flagTypes.append(interpreter->fieldFlag(&record[recIndex], &interpreter->TInterpItemArray[i].mask_));
                    dp->paramsSequence.append(8);
                    dp->paramsVisibleArr.append(1);


            break;
        }
        case 27:
        {
            //                                                //qDebug << interpreter->TInterpItemArray[i].name;
            int tmpErrVal = interpreter->fieldInt(&record[recIndex]);
            dp->error.append(tmpErrVal);
            dp->paramsSequence.append(27);
            dp->paramsVisibleArr.append(1);
            break;
        }

        default:
        {
            break;
        }
        }

    }
//    qDebug() << record;
    return 0;
}


int MainWindow::fillHeadTable()
{
    return 0;
}

int MainWindow::initBigThermos(int qty)
{
    qty = 2;
//    QwtThermo *big1 = new QwtThermo;
//    QwtThermo *big2 = new QwtThermo;
//    big1->widthMM()=100;
//    big1->heightMM() = 10;

    return 0;
}

bool MainWindow::createTimeSegment(QStringList *listOfLogs)
{
    int something = 2;
    time_t one,two;

    for(int i = 0; i < something;i++)//something gets from listOfLogs
    {

        if(i<2)
        {
            if(i==0)
            {
                openLogFile(2);
                readHeadTableData();
                readTimeEdges(&one, &two);//one = first, two = second

            }
        }
        if(two<one)
            inverseTime = true;
        if(inverseTime)
        {
            if(!timeSegment.size())
                timeSegment.append(two);
            else
                timeSegment.append(one);
        }
        else
        {
            if(!timeSegment.size())
                timeSegment.append(one);
            else
                timeSegment.append(two);
        }

        qDebug() << "created time segment" <<QDateTime::fromTime_t(timeSegment[i]);
    }
    //char tmprec[100];
//    dataParams *tmpDP = new dataParams;
//    lastRecNum = getRecordNumClosestToTime(timeSegment.first()+40,0,0);
//    qDebug() << getRecordNumClosestToTime(timeSegment.first()+40,0,0);
//    qDebug() << makeStructFromRecord(log->record,tmpDP);

//    if(!tmpDP->doubleTypes.isEmpty())
//        qDebug() << tmpDP->doubleTypes;
//    qDebug() << tmpDP->error;
//    qDebug() << tmpDP->flagTypes;
//    qDebug() << tmpDP->floatTypes;
//    qDebug() << tmpDP->intTypes;
//    qDebug() << tmpDP->paramsSequence;
//    qDebug() << tmpDP->paramsVisibleArr;
//    qDebug() << tmpDP->powOnTime;
//    qDebug() << tmpDP->time;
//    qDebug() << tmpDP->timeFract;

    return true;
}

int MainWindow::createFakeTimeScale()
{
    qDebug() << "creatinFakeTimeScale";
    int sliderScaleVal = (int)timeSegment.last()-(int)timeSegment.first();

    qDebug() <<"sliderscaleval" <<    sliderScaleVal;
    if(sliderScaleVal<0)
    {
        sliderScaleVal = (int)timeSegment.first()-(int)timeSegment.last();
        inverseTime = true;
    }
    ui->horizontalSlider->setMaximum(sliderScaleVal);
    qDebug() << "sliderscaleval" << sliderScaleVal;
    int sliderPageCount = 100;
    if (sliderScaleVal < sliderPageCount)
        sliderPageCount = sliderScaleVal;
    ui->horizontalSlider->setPageStep(sliderScaleVal/sliderPageCount);
    return 0;
}

int MainWindow::initSmallThermos(int qty, QVector <QString> names, QVector <long> maxs)
{
    QHBoxLayout thermoLayout[4];
    for(int i = 0; i < qty; i++)
    {
        parameterBar.insert(i,new QwtThermo(this));

        parameterBar[i]->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
        if(maxs[i]>0)
            parameterBar[i]->setMaxValue(maxs[i]);
        else
            parameterBar[i]->setMaxValue(2000);
        QLabel *tmptext = new QLabel(names[i]);
//        thermoLayout[i%4].addWidget(&tmptext);
//        thermoLayout[i%4].addWidget(parameterBar[i]);
        thermoVals.append(new QLabel("0"));
        ui->gridLayout_2->addWidget(parameterBar[i],2*(int)(i/4)+1,i%4,Qt::AlignLeft);
        ui->gridLayout_2->addWidget(tmptext,2*(int)(i/4),i%4, Qt::AlignLeft);
        ui->gridLayout_2->addWidget(thermoVals[i],2*(int)(i/4),i%4, Qt::AlignRight);
//        parameterBar[i] = new QwtThermo(this);
//        parameterBar.insert(i,parameterBar[i]);
//        ui->verticalLayout_3->addWidget(parameterBar[i],0,0);
//        parameterBar[i].setParent(ui->verticalLayout_3);
    }
    for(int i = 0; i < 4; i++)
    {
//        ui->horizontalLayout_5->addLayout(&thermoLayout[i]);
    }
    return 0;
}

//config
int MainWindow::createVideoConfigFile(QString videopath)
{

    if(videopath.isEmpty())
        return 2;
    QString currentVideoDir = QApplication::applicationDirPath()+"/videoconfig";
    //qDebug() << currentdir;
    //qDebug() << path;
    if(QFile(currentVideoDir).exists())//if file is not empty removing it, same is update func
        QFile(currentVideoDir).remove();
    QFile *newVideoConf = new QFile(currentVideoDir);
    newVideoConf->open(QIODevice::ReadWrite);
    newVideoConf->write(videopath.toLocal8Bit());
    videoWorkingDir = videopath;
    newVideoConf->close();

    return 0;
}

int MainWindow::createLogConfigFile(QString logpath)
{
    if (logpath.isEmpty())
        return 1;
    QString currentLogDir = QApplication::applicationDirPath()+"/logconfig";
    //qDebug() << currentdir;
    //qDebug() << path;
    if(QFile(currentLogDir).exists())//if file is not empty removing it, same is update func
        QFile(currentLogDir).remove();
    QFile *newLogConf = new QFile(currentLogDir);
    newLogConf->open(QIODevice::ReadWrite);
    newLogConf->write(logpath.toLocal8Bit());
    logWorkingDir = logpath;
    newLogConf->close();


    return 0;
}

int MainWindow::openLogConfigFile(QString *retstr)
{

    retstr->clear();
    QString currentdir = QApplication::applicationDirPath()+"/logconfig";
    //qDebug() << currentdir;
    QFile *conf = new QFile;
    conf->setFileName(currentdir);
    if(conf->open(QIODevice::ReadWrite))
    {
        retstr->append(QTextCodec::codecForLocale()->toUnicode(conf->readAll()));//необходимо представление стринга в юникоде, иначе QDir не понимает
        //qDebug() << retstr;
        conf->close();
        return 0;
    }
    else
        //qDebug() << "NULL";
        conf->close();
        return 1;
}

int MainWindow::openVideoConfigFile(QString *retstr)
{

    retstr->clear();
    QString currentdir = QApplication::applicationDirPath()+"/videoconfig";
    //qDebug() << currentdir;
    QFile *conf = new QFile;
    conf->setFileName(currentdir);
    if(conf->open(QIODevice::ReadWrite))
    {
        retstr->append(QTextCodec::codecForLocale()->toUnicode(conf->readAll()));//необходимо представление стринга в юникоде, иначе QDir не понимает
        //qDebug() << retstr;
        conf->close();
        return 0;
    }
    else
        //qDebug() << "NULL";
        conf->close();
        return 1;
}

int MainWindow::updateConfigFile(QString path)
{

}

void MainWindow::setFolderWFiles(QString path)
{
    logWorkingDir = path;
//    createConfigFile(path);
}

void MainWindow::selectVideoFolder()
{

    QString videodir = QFileDialog::getExistingDirectory(this, tr("Выбор директории видеофайлов"),QDir::homePath());
//    QString readVideoDir;
//    if(!openVideoConfigFile(&readVideoDir))
//        createVideoConfigFile(videodir);
    //qDebug() << readDir;
//    if(!openLogConfigFile(&readDir))
//        createConfigFile(logdir,videodir);
//    videoWorkingDir = readVideoDir;


//    qDebug() << checkVideoFilesExistance(videoWorkingDir);
    if(checkVideoFilesExistance(videodir)==0)
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("В выбранной вами папке видеофайлов не обнаружено! Пожалуйста, попробуйте еще раз.");
        newMessage.exec();
        VideoFileError = 2;
    }
    else
    {
        VideoFileError = 0;
        videoWorkingDir = videodir;
         qDebug() << videoWorkingDir;
         ui->lineEdit->setText(videoWorkingDir);
         videoCheck->setChecked(true);
         openVideoFilesFolder(&videoList);
         qDebug() << videoList;
    }
    if((VideoFileError==0)&(LogFileError==0))
    {
        setButtonPanelEnabled(true);

    }
}
void MainWindow::selectLogFolder()
{
    QString logdir = QFileDialog::getExistingDirectory(this, tr("Выбор директории лог-файлов"),QDir::homePath());


    if(checkLogFilesExistance(logdir)==0)//if no .alg files found show error
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("В выбранной вами папке лог-файлов не обнаружено! Пожалуйста, попробуйте еще раз.");
        newMessage.exec();
        LogFileError = 2;
    }
    else                        //else do all the next things
    {
        logWorkingDir = logdir;
        qDebug() << logWorkingDir;
        ui->lineEdit_2->setText(logWorkingDir);
        logCheck->setChecked(true);
        LogFileError = 0;
    }
    if((VideoFileError==0)&(LogFileError==0))
    {
        setButtonPanelEnabled(true);

    }
}

int MainWindow::checkLogFilesExistance(QString path)
{
    QDir filesDir(path);
    QStringList list;
    int algCounter = 0;
    list = filesDir.entryList(QDir::Files,QDir::Type);
    for(int i = 0; i<list.size() ; i++)
    {
        if(list.at(i).indexOf(".alg")!=-1)
        {
//            qDebug() << list.at(i).indexOf(".alg");
            algCounter++;
        }

    }
    return algCounter;

}

int MainWindow::checkVideoFilesExistance(QString path)
{
    QDir filesDir(path);
    QStringList list;
    int aviCounter = 0;
    list = filesDir.entryList(QDir::Files,QDir::Type);
    for(int i = 0; i<list.size() ; i++)
    {
        if(list.at(i).indexOf(".mkv")!=-1)
        {
//            qDebug() << list.at(i).indexOf(".avi");
            aviCounter++;
        }

    }
    return aviCounter;
}

//work with files
void MainWindow::updateTime()//i don't like this func
{
    tickCounter++;
    if(tickCounter%25==0)//second passed
    {
        ui->horizontalSlider->setValue(ui->horizontalSlider->value()+1);
        tickCounter=1;
        dataParams *tmpDP = new dataParams;
//        qDebug() << timeSegment.first();
//        qDebug() << timeSegment.last();
//        qDebug() << ui->horizontalSlider->value();
        lastRecNum = getRecordNumClosestToTime(timeSegment.first()+ui->horizontalSlider->value(),0,0);
//        if(lastRecNum==-1)
//            lastRecNum = 0;
        qDebug() << QDateTime::fromTime_t(timeSegment.first()+ui->horizontalSlider->value());
//        qDebug() <<"this is recNumber" << lastRecNum;
//        qDebug() << QString::number(lastRecNum,10);

        makeStructFromRecord(log->record,tmpDP);
//        qDebug() << tmpDP->doubleTypes;
//        qDebug() << tmpDP->timeFract.at(0);
        updateThermos(*tmpDP);
//        qDebug() << tmpDP->doubleTypes.at(4);
        int tmpTime1 = vplayer->getCurrentTime();
        int tmpTime2 = vplayer2->getCurrentTime();
        float tmpPos1 = vplayer->getPosition();
        float tmpPos2 = vplayer2->getPosition();
        qDebug() <<"vplayer2 current time" << tmpTime1 << "vplayer1 current time"<< tmpTime2;
        qDebug() <<"vplayer2 current time" << tmpPos1 << "vplayer1 current time"<< tmpPos2;
        vplayer->_player->play();
        vplayer2->_player->play();
        while(checkVideosSynchronized()==true){}
        vplayer->_player->play();
        vplayer2->_player->play();
//        if(tmpPos1!=tmpPos2)
//        {
//            if(tmpPos1>tmpPos2)
//                vplayer->moveToTime(vplayer2->getPosition());
//            else
//                vplayer2->moveToTime(vplayer->getPosition());
//        }

    }
    else
    {
        dataParams *tmpDP = new dataParams;
//        qDebug() << timeSegment.first();
//        qDebug() << timeSegment.last();
//        qDebug() << ui->horizontalSlider->value();
        lastRecNum = getRecordNumClosestToTime(timeSegment.first()+ui->horizontalSlider->value(),tickCounter*10,0);//we need to define timeFract here
//        qDebug() <<"this is recNumber" << lastRecNum;

//        qDebug() << "timefract" << tickCounter;
//        qDebug() << QString::number(lastRecNum,10);
        makeStructFromRecord(log->record,tmpDP);
//        qDebug() << tmpDP->doubleTypes;
//        qDebug() << tmpDP->timeFract.at(0);
        updateThermos(*tmpDP);
//        qDebug() << tmpDP->doubleTypes.at(4);

    }

}

int MainWindow::updateThermos(dataParams dp)
{
//    qDebug() << "doubleTypes size" << dp.doubleTypes.size();
    for(int i = 0; i < dp.doubleTypes.size(); i++)
    {
        parameterBar[i]->setValue(dp.doubleTypes[i]);
        thermoVals[i]->setText(QString::number(dp.doubleTypes[i],10,2));
    }
    return 0;
}

int MainWindow::getRecordNumClosestToTime(time_t currentTime, int timeFract, int lastRecord /*char *rec*/) //search record number using time
{
   // char rec[100];
    long tmpErr = log->selectSegment(bigTableID);
    int recIndex=0;
    bool timeFractSearchFlag = false;
    time_t recTime;
    time_t beforeTime;
//    qDebug() << QDateTime::fromTime_t(currentTime);
    if(tmpErr==0)
    {
        char* buffArr = (char*)malloc(log->segmentHeader.size);
            log->readSegment(buffArr, log->segmentHeader.size );
            interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
            interpreter->setInterpretationTable(buffArr,interpreter->interpreterRecordsCount);
            log->setValueLDPtr(SIZE_OF_FILEHEADER);
        long tmpErr1 = log->selectSegment(bigTableID&0x7fffffff);
        if(!tmpErr1)
        {
            int tmpRecordCount = log->segmentHeader.size/log->segmentHeader.recordSize;
            int recPosition=log->logDataPointer;
            int recPositionCompareVal = recPosition;
                 recIndex =0;
                 for (int index = lastRecord; index < tmpRecordCount; index++)
                 {

                     log->readRecord(tmpRecordCount,log->segmentHeader.recordSize, recPositionCompareVal);
                     for (int i = 0; i < interpreter->interpreterRecordsCount; i++)
                     {
                         recIndex=interpreter->TInterpItemArray[i].offset;
                         if(interpreter->TInterpItemArray[i].level)
                         {

                             switch(interpreter->TInterpItemArray[i].typ&0xffff)
                             {
                             case 10 :
                             {
                                 recTime = (time_t)interpreter->fieldInt(&log->record[recIndex]);
                                 recTime = mktime(gmtime(&recTime));
                                 if(interpreter->TInterpItemArray[i].name!="PowOnTime")
                                 {
                                     //check time going direction
                                     if(currentTime==recTime)
                                     {
                                         beforeTime = recTime;
                                         timeFractSearchFlag = true;//set flag of searching timefract

                                     }
                                     else
                                     {
                                         if(inverseTime)
                                         {
                                            if(currentTime>recTime)
                                                 return index;

                                         }
                                         else
                                         {

                                             if(currentTime<recTime)
                                                 return index;

                                         }
                                     }



                                  }
                                 else
                                 {

                                 }
                                         break;
                             }
                             case 0:
                             {
                                 if(timeFractSearchFlag)
                                 {
                                     unsigned char tmpTimeFract;

                                        tmpTimeFract = interpreter->fieldChar(&log->record[recIndex]);

                                        if(inverseTime)
                                        {
                                            if((int)timeFract>=(int)tmpTimeFract)
                                               return index;
                                        }
                                        else
                                        {
                                            if((int)timeFract<=(int)tmpTimeFract)
                                                return index;
                                        }

                                 }
                             }
                             }
                         }
                     }
                 }
        }
    }

    return -1;
}


int MainWindow::readTimeEdges(time_t *beginTime, time_t *endTime)
{
    long tmpErr = log->selectSegment(bigTableID);
    int recIndex=0;
    time_t recTime;
    if(tmpErr==0)
    {
        char* buffArr = (char*)malloc(log->segmentHeader.size);
            log->readSegment(buffArr, log->segmentHeader.size );
            interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
            interpreter->setInterpretationTable(buffArr,interpreter->interpreterRecordsCount);
            log->setValueLDPtr(SIZE_OF_FILEHEADER);
        long tmpErr1 = log->selectSegment(bigTableID&0x7fffffff);
        if(!tmpErr1)
        {
            int tmpRecordCount = log->segmentHeader.size/log->segmentHeader.recordSize;
            qDebug() <<"количество записей"<< tmpRecordCount;
            int recPosition=log->logDataPointer;
            int recPositionCompareVal = recPosition;
//            QVector <long> thMaxs(0);
//            initSmallThermos(initThermoMaxs(&thMaxs));
                 recIndex =0;
                 for (int index = 0; index < 2; index++)
                 {

                     log->readRecord(tmpRecordCount,log->segmentHeader.recordSize, recPositionCompareVal);
                     for (int i = 0; i < interpreter->interpreterRecordsCount; i++)
                     {
                         recIndex=interpreter->TInterpItemArray[i].offset;
                         if(interpreter->TInterpItemArray[i].level)
                         {

                             switch(interpreter->TInterpItemArray[i].typ&0xffff)
                             {
                             case 10 :
                             {
                                 recTime = (time_t)interpreter->fieldInt(&log->record[recIndex]);
                                 recTime = mktime(gmtime(&recTime));
                                 if(interpreter->TInterpItemArray[i].name!="PowOnTime")
                                 {
                                     //check time going direction
                                         if(index==0)
                                         {
                                             *beginTime = recTime;
                                             log->setValueLDPtr(log->logDataPointer+(tmpRecordCount-2)*log->segmentHeader.recordSize);//sending ldPointer at the end of recordcount
                                         }
                                         else
                                         {
                                             *endTime = recTime;
                                         }

                                  }
                                 else
                                 {

                                 }
                                         break;
                             }

                             }
                         }
                     }
                 }
        }
    }

    return 0;
}

int MainWindow::openLogFilesFolder( QStringList *listOfLogs)
{
//    QFile fileToOpen;
    listOfLogs->clear();
    QString pathToFileDir = logWorkingDir;
    QDir filesDir(pathToFileDir);
    //qDebug() << filesDir.path();
    if(!filesDir.exists())
        return 1;
    filesDir.setSorting(QDir::Time);
    qDebug() << filesDir.entryList();
    //qDebug() << filesDir.entryList().at(2);
    listOfLogs->append(filesDir.entryList());
    return 0;
}

int MainWindow::openVideoFilesFolder(QStringList *listOfVideos)
{
//    QFile fileToOpen;
    listOfVideos->clear();

    QString pathToFileDir = videoWorkingDir;
    qDebug() << videoWorkingDir;
    QDir filesDir(pathToFileDir);
    //qDebug() << filesDir.path();
    if(!filesDir.exists())
        return 1;
    filesDir.setSorting(QDir::Time|QDir::Reversed);
//    filesDir.setSorting(QDir::Reversed);
    //qDebug() << filesDir.entryList();
    //qDebug() << filesDir.entryList().at(2);
//    listOfVideos->append(filesDir.entryList(QDir::Files));
    for(int i = 0; i < filesDir.entryList(QDir::Files).size(); i++)
    {
        if(filesDir.entryList(QDir::Files).at(i).indexOf(".mkv")!=-1)
            listOfVideos->append(filesDir.entryList(QDir::Files).at(i));

    }
//    QStringList *tmpVideos = new QStringList;
//    tmpVideos->append(listOfVideos);
//    listOfVideos->clear();
//    qDebug() << "videolist" << listOfVideos;
    qSort(listOfVideos->begin(),listOfVideos->end());
//    qDebug() << "sortedlist" << listOfVideos;

    return 0;
}

int MainWindow::openLogFile(int logIndex)
{

    QString selectedLogFilePath;
    selectedLogFilePath.clear();
    qDebug() << logList;
    selectedLogFilePath = logWorkingDir+"/"+logList.at(logIndex);
  //  qDebug() << log->selectLogFile(selectedLogFilePath);
   // log->selectLogFile(selectedLogFilePath);
    qDebug() << checkFileHeaderCRC(selectedLogFilePath);
    openedFileIndex = logIndex;
    tickCounter = 0;
    timer->start(40);
//    thrd = new MyThread;
////    thrd->setTimerInterval(25);
//    connect(thrd,SIGNAL(tick()),this,SLOT(updateTime())); //it works too
//    thrd->start();
//    thrd->Timer->start(25);
//    thrd->run();
   // checkFileHeaderCRC(selectedLogFilePath);
    return 0;
}

bool MainWindow::checkfunc(time_t *a, time_t *b)
{
    int aaa = 100000;
    int bbb = 100060;
    *a = aaa;
    *b = bbb;
    return true;
}

int MainWindow::findTimeSegment(int sliderval)
{
    for(int i = 1; i < timeSegment.size();i++)
    {
        if((timeSegment[i]-timeSegment.first())>= sliderval)
            return i;
    }
    return -1;
}

bool MainWindow::checkFileHeaderCRC(QString filename)
{

    log->selectLogFile(filename);
    log->checkSegmentsExistance();
    log->readFileHeader();
    int maxSegCount = log->getSegmentsCount();
    unsigned long CRCtmpFH = 0;
    log->tmpFile.seek(0);
    log->tmpFile.read(tmpFHPtr,SIZE_OF_FILEHEADER);
    tmpFHPtr[32]=SIZE_OF_FILEHEADER;
    tmpFHPtr[33]=0;
    tmpFHPtr[34]=0;
    tmpFHPtr[35]=0;
    tmpFHPtr[36]=0;
    tmpFHPtr[37]=0;
    tmpFHPtr[38]=0;
    tmpFHPtr[39]=0;
    CRCtmpFH = log->CRC32updater(tmpFHPtr,SIZE_OF_FILEHEADER,0xffffffff);
    CRCtmpFH = CRCtmpFH^0xffffffff;
    for(int segCount = 0; segCount < maxSegCount; segCount++)
    {
        long tmpID = log->setTmpID();
        log->selectSegment(tmpID);
        log->logDataPointer+=log->segmentHeader.size;
        CRCtmpFH = CRCtmpFH^log->segmentHeader.CRC32;
    }
    if(CRCtmpFH!=log->fileHeader.selfCRC32)
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
        newMessage.exec();
        return false;
    }
    return true;
}

int checkTimePointExistance(time_t)
{

    return 0;
}

int MainWindow::readHeadTableData()//here we read head table - its header and its data
{
    int tmpID= 0;
//    int cycleID = 0;
    int tmpLogDataPointer =0;
    for(int i = 0; i < log->segIDs.size(); i++)
    {
        //qDebug << log->segIDs[i];
    }
    if(log->fileHeader.fileSize != log->tmpFile.size())//check file size
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Файл журнала регистратора поврежден.");
        newMessage.exec();
    }
    int tmpErr = log->selectSegment(localizationTableID);
    char tmpBuff[log->segmentHeader.size];
    log->readSegment(tmpBuff, sizeof(tmpBuff));
    msys->parseMessages(tmpBuff);
    if(tmpErr!=0)
    {
        QVariant tmp2=tmpErr;
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Файл журнала регистратора поврежден."+tmp2.toString());
        newMessage.exec();
    }
    tmpErr = log->selectSegment(smallTableID);
    if(tmpErr==0)
    {
          /*
           *At this point we have calculated CRC of head table segment interpretator, and datapointer
           *pointed to the interpreter, but not to its header, so we can get from interpreter names of head
           */
                char buffArr1[log->segmentHeader.size];
//                char* buffArr1 = (char*)malloc(log->segmentHeader.size);
                //qDebug() << log->segmentHeader.size;
                log->readSegment(buffArr1, log->segmentHeader.size );
                interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
                interpreter->setInterpretationTable(buffArr1,interpreter->interpreterRecordsCount);
                int index=0;
                for(int i =0; i <interpreter->interpreterRecordsCount; i++)
                {

                    if(interpreter->TInterpItemArray[i].level!=0)
                    {
//                            verticalHeaderName = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
//                            ui->tableWidget->verticalHeaderItem(i-1)->setText(verticalHeaderName);

                        int col1 = 0;
//                        int col2 = 1;
                        //qDebug()<< QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
                        parname = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);//QTextCodec::codecForLocale()->toUnicode(interpreter->TInterpItemArray[i].name);
                        QLabel *labe1 = new QLabel(parname);
                        //qDebug() << parname;
                        labe1->setAlignment(Qt::AlignCenter);
//                        labe1->text().append(parname);
//                        QLabel *labe2 = new QLabel("textBlock2");
                        ui->tableWidget_2->setCellWidget(index/2,col1+(index%2)*2,labe1);
                        ui->label_3->text().clear();
                        ui->label_3->text().append(parname);
//                        ui->tableWidget_2->setCellWidget(index/2,col2+(index%2)*2,labe2);
                        index++;

                    }


                }
               /*
                *from here we start to processing data from small table
                */
                  if(log->selectSegment(smallTableID&0x7fffffff))
                  {
                      QVariant tmpVal = tmpErr;
                      newMessage.setWindowTitle("Ошибка!");
                      newMessage.setText("Файл журнала регистратора поврежден. " + tmpVal.toString());
                      newMessage.exec();
                  }
                            QString tmpField = " ";
                            int recIndex = 0;
                            QVariant recFloat;

                            log->readRecord(log->segmentHeader.recordSize, log->segmentHeader.size, log->logDataPointer);
                            for (int i = 0; i < interpreter->interpreterRecordsCount; i++)
                            {
                                recIndex=interpreter->TInterpItemArray[i].offset;
                                if(interpreter->TInterpItemArray[i].level)
                                {
                                    switch(interpreter->TInterpItemArray[i].typ)
                                    {

                                            case 34 :
                                            {
                                                double tmpDbl;
                                                tmpDbl = interpreter->fieldDouble(&log->record[recIndex]);
                                                //qDebug() << interpreter->TInterpItemArray[i].name;
//                                                //qDebug() << tmpDbl;
                                                QVariant tmpVal = tmpDbl;
                                                tmpField = tmpVal.toByteArray();
                                                //qDebug() << interpreter->TInterpItemArray[i].mask_;
                                                //qDebug << tmpDbl;
                                                break;

                                            }

                                            case 7:
                                    {
                                          float tmpFloat, tmpMinFloat, tmpMaxFloat;
                                          int tmpIntFloat;
                                          tmpFloat = interpreter->fieldFloat(&log->record[recIndex]);
                                              if(tmpFloat==tmpFloat)
                                                {
                                                tmpMinFloat = interpreter->TInterpItemArray[i].min/pow(10,interpreter->TInterpItemArray[i].mask_);
                                                tmpMaxFloat = interpreter->TInterpItemArray[i].max/pow(10,interpreter->TInterpItemArray[i].mask_);
                                                if((tmpMinFloat==0)&&(tmpMaxFloat==0));
                                                else
                                                {
                                                    if(tmpFloat!=tmpMinFloat)
                                                    {
                                                        if(tmpFloat<tmpMinFloat)tmpFloat = tmpMinFloat;
                                                        if(tmpFloat>=tmpMaxFloat)tmpFloat = tmpMaxFloat;
                                                    }
                                                }
                                                tmpFloat = tmpFloat*pow(10,interpreter->TInterpItemArray[i].mask_);
                                                tmpIntFloat =(int)tmpFloat;
                                                if(tmpFloat>0)
                                                {
                                                    if(tmpIntFloat!=0)
                                                    {
                                                        if((tmpFloat-tmpIntFloat)!=0)
                                                        {
                                                            if((tmpFloat-tmpIntFloat)>0.5)tmpIntFloat++;
                                                        }
                                                    }
                                                }
                                                if(tmpFloat<0)
                                                {
                                                    if(tmpIntFloat!=0)
                                                    {
                                                        if((tmpFloat-tmpIntFloat)!=0)
                                                        {
                                                            if(abs(tmpFloat-tmpIntFloat)>0.5)tmpIntFloat--;
                                                        }
                                                    }
                                                }
                                                tmpFloat = (float)(tmpIntFloat/pow(10,interpreter->TInterpItemArray[i].mask_));

                                                recFloat = tmpFloat;
                                                tmpField = recFloat.toByteArray();
                                              }
                                              else
                                                  tmpField = "Неиспр.";
                                              break;
                                    }

                                               default:
                                            {
                                                tmpField.append("Недоступно");
                                                break;
                                            }
                                    }
                                    int col2 = 1;
                                    QTableWidgetItem *tmpItem;
                                    tmpItem = new QTableWidgetItem;
                                    tmpItem->setText(QString::fromStdString(tmpField.toStdString()));
                                    tmpField = "";
                                    ui->tableWidget_2->setItem((i-2)/2, col2+(i%2)*2, tmpItem );
                                }
                            }

    }
    else
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
        newMessage.exec();
        //qDebug << "error in linguo section";
//        isOpened=false;
//        openNewMainWindow();
        this->close();
    }

}

//actions buttons etc
void MainWindow::on_action_triggered()
{
    selectLogFolder();
}

void MainWindow::on_pushButton_clicked()
{
//    openAndPlayVideo();
    QVector <long> thMaxs(0);
    QVector <QString> thNames(0);
    openLogFilesFolder(&logList);

    if(timeSegment.isEmpty())
        //qDebug()<< "empty!";
    createTimeSegment(&logList);
    createFakeTimeScale();
    initThermoNames(&thNames);
    initSmallThermos(initThermoMaxs(&thMaxs),thNames,thMaxs);
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(1);
//    qDebug() << videoWorkingDir+"/"+videoList[0];
//    connect(vplayer->_player,SIGNAL(playing()),this,SLOT(pausePlayer1()));
    openVideoFile(videoList[3],videoList[3]);

//    vplayer->moveToTime(vplayer2->getCurrentTime());
//    qDebug() <<"vplayer2 current time" << vplayer2->getCurrentTime()<< "vplayer1 current time"<< vplayer->getCurrentTime();

}

void MainWindow::setPlayer1ModePlaying()
{
    playingModePlayer1 = true;
}

void MainWindow::setPlayer2ModePlaying()
{
    playingModePlayer2 = true;
}
void MainWindow::setPlayer1ModePaused()
{
    player1Paused = true;
}
void MainWindow::setPlayer2ModePaused()
{
    player2Paused = true;
}

void MainWindow::pausePlayer1()
{
//    videoDelayms++;
//    if(isVideo1Opened)
//    {
//       vplayer->_player->pause();
////       disconnect(vplayer->_player,SIGNAL(playing()),this,SLOT(pausePlayer1()));
//       qDebug() << "can i pause that player?";
//    }
//    if(isVideo2Opened)
//    {
//        vplayer2->_player->pause();
//        qDebug() << "and that one";
//    }
//    connect(vplayer2->_player,SIGNAL(playing()),this, SLOT(playBothPlayers()));
}

void MainWindow::playBothPlayers()
{
//    vplayer->pause();
////    vplayer2->pause();
//    disconnect(vplayer2->_player,SIGNAL(playing()),this,SLOT(playBothPlayers()));
    if(isVideo1Opened)
        vplayer->_player->pause();
    if(isVideo2Opened)
        vplayer2->_player->pause();
//    if((isVideo1Opened)&(isVideo2Opened))
//    {
//      vplayer->_player->play();
//      vplayer2->_player->play();
//    }
    qDebug()<<"both players slot";
}

void MainWindow::on_action_2_triggered()
{


}


int MainWindow::openVideoFile(QString filename1, QString filename2)
{
#ifdef GLOBALMODE
    int result1=0,result2=0;
    int time;
    timer->stop();
    isVideo1Opened = false;
    isVideo2Opened = false;
    playingModePlayer1 = false;
    playingModePlayer2 = false;
    player1Paused = false;
    player2Paused = false;
    videoDelayms=0;
//   playingFile1 = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
   if(ui->comboBox->currentIndex()!=0)
   {
        playingFile1 = filename1;
        result1 = vplayer->openLocal(videoWorkingDir+"/"+playingFile1);
        delayTimer->start(1);
//        vplayer->_player->pause();
        isVideo1Opened = true;



   }
   if(ui->comboBox_2->currentIndex()!=0)
   {

        playingFile2 = filename2;
        result2 = vplayer2->openLocal(videoWorkingDir+"/"+playingFile2);
//        delayTimer->start(1);
//        connect(vplayer2->_player,SIGNAL(playing()),this,SLOT(pausePlayer1()));
//        vplayer2->_player->pause();
        isVideo2Opened = true;

   }
//   if((!result1)|(!result2))
//   {

//   }
#endif
   return 0;
}

void MainWindow::delayTimerTick()
{
    videoDelayms++;
    delayTimer->start(1);
    if((isVideo1Opened)&(playingModePlayer1))
        vplayer->_player->pause();
    if((isVideo2Opened)&(playingModePlayer2))
        vplayer2->_player->pause();
    if((isVideo1Opened)&(isVideo2Opened))
    {
        if((player1Paused)&(player2Paused))
        {
            videoDelayms = 0;
            delayTimer->stop();
            int tmpTime1 = vplayer->getCurrentTime();
            int tmpTime2 = vplayer2->getCurrentTime();
            if(tmpTime1>tmpTime2)
                vplayer->_player->setTime(tmpTime2);
//                vplayer->moveToTime(tmpTime2);
            if(tmpTime1<tmpTime2)
                vplayer2->_player->setTime(tmpTime1);
//                vplayer2->moveToTime(tmpTime1);
            qDebug() << "delay ticks"<<videoDelayms;
            player1Paused = false;
            player2Paused = false;

            vplayer->_player->play();
            vplayer2->_player->play();
            while(checkVideosSynchronized()==true){}
            vplayer->_player->play();
            vplayer2->_player->play();
        }
    }
//    qDebug() << "playingModePlayer1" << playingModePlayer1;
//    qDebug() << "playingModePlayer2" << playingModePlayer2;
//    qDebug() << "delay tick"<<isVideo1Opened<<isVideo2Opened;
//    qDebug() << "delay ticks"<<videoDelayms;
}

void MainWindow::stopDelayTimer()
{
//    delayTimer->stop();
//    qDebug() <<"delaytime" << videoDelayms;

//   disconnect(vplayer->_player,SIGNAL(playing()),this,SLOT(startDelayTimer()));
//   disconnect(vplayer2->_player,SIGNAL(playing()),this,SLOT(stopDelayTimer()));
}

void MainWindow::startDelayTimer()
{

}

bool MainWindow::checkVideosSynchronized()
{
    vplayer->_player->pause();
    vplayer2->_player->pause();
    if((player1Paused)&(player2Paused))
    {
    float tmpPos1 = vplayer->_player->position();
    float tmpPos2 = vplayer2->_player->position();
    if(tmpPos1>tmpPos2)
        vplayer->_player->setPosition(tmpPos2);
    if(tmpPos1<tmpPos2)
        vplayer2->_player->setPosition(tmpPos1);
    return true;
    }
    return false;

}

int MainWindow::changeVideo1(QString filename)
{
    qDebug() << "changing video #1";
    int result1=0;
//   playingFile1 = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
   if(ui->comboBox->currentIndex()!=0)
   {
        vplayer->stop();
        playingFile1 = filename;
//        isVideo1Opened = false;
        result1 = vplayer->openLocal(videoWorkingDir+"/"+playingFile1);
        delayTimer->start(1);
   }
   return result1;
}

int MainWindow::changeVideo2(QString filename)
{
    qDebug() << "changing video #2";
    int result2=0;
//   playingFile1 = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
   if(ui->comboBox_2->currentIndex()!=0)
   {
        vplayer2->stop();
        playingFile2 = filename;
//        isVideo2Opened = false;
        result2 = vplayer2->openLocal(videoWorkingDir+"/"+playingFile2);
        delayTimer->start(1);
   }
   return result2;
}
void MainWindow::videoEnded()
{
    int index1=0,index2=0;
    for(int i = 0; i < videoList.size(); i++)
    {
        if(videoList[i]==playingFile1)
            index1=i;
        if(videoList[i]==playingFile2)
            index2=i;

    }
    qDebug() << "index1"<< index1<<" index2"<< index2;
    if((index1+5<videoList.size())&(index2+5<videoList.size()))
    {

//        delayTimer->start(1);
//        isVideo1Opened = false;
//        isVideo2Opened = false;
        openVideoFile(videoList[index1+5],videoList[index2+5]);
//        vplayer2->moveToTime(vplayer->getCurrentTime());
    }
}

void MainWindow::on_playButton_clicked()
{
    if(timer->isActive())
        timer->stop();
    else
        timer->start(25);
#ifdef GLOBALMODE
    vplayer->pause();
    vplayer2->pause();
#endif
}

void MainWindow::on_stopButton_clicked()
{
#ifdef GLOBALMODE
    vplayer->stop();
    vplayer2->stop();
#endif
}

void MainWindow::setButtonPanelEnabled(bool tf)
{
    ui->frameBackwardButton->setEnabled(tf);
    ui->nextFrameButton->setEnabled(tf);
    ui->stopButton->setEnabled(tf);
    ui->nextTimeSegment->setEnabled(tf);
    ui->pushButton->setEnabled(tf);
    ui->playButton->setEnabled(tf);
    ui->previousTimeSegment->setEnabled(tf);
    ui->timeEdit->setEnabled(tf);
}

void MainWindow::on_timeEdit_editingFinished()
{

      QTime zerotime;
      zerotime.setHMS(0,0,0,0);
#ifdef GLOBALMODE
      vplayer->moveToTime(zerotime.secsTo(ui->timeEdit->time())*1000);
//      vplayer->moveToTime(zerotime.secsTo(ui->timeEdit->time())*1000);
#endif
}

void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
//    QTime zerotime;
//    zerotime.setHMS(0,0,0,0);
//    int tmp = zerotime.secsTo(ui->timeEdit->time());
//    //qDebug() << tmp;
}

void MainWindow::on_nextTimeSegment_clicked()
{
    videoFileSelector(ui->comboBox->currentIndex(), 0);
    int index1=0,index2=0;
    for(int i = 0; i < videoList.size(); i++)
    {
        if(videoList[i]==playingFile1)
            index1=i;
        if(videoList[i]==playingFile2)
            index2=i;

    }
    qDebug() << "index1"<< index1<<" index2"<< index2;
    if((index1+5<videoList.size())&(index2+5<videoList.size()))
    {
        openVideoFile(videoList[index1+5],videoList[index2+5]);
//        vplayer2->moveToTime(vplayer->getCurrentTime());
    }
}

#ifdef GLOBALMODE
void MainWindow::setVideoTime()//its my handmade slot
{

    int time = vplayer->getCurrentTime();
    int ms = time%1000;
    time = time/1000;
    QTime outtime;
    int h = time/3600;
    int m = (time/60)%60;
    int s = time%60;

    outtime.setHMS(h,m,s,ms);
    ui->timeEdit->setTime(outtime);

}
#endif
void MainWindow::on_previousTimeSegment_clicked()
{
//        //qDebug() << openConfigFile(&workingDir);
    int index1=0,index2=0;
    for(int i = 0; i < videoList.size(); i++)
    {
        if(videoList[i]==playingFile1)
            index1=i;
        if(videoList[i]==playingFile2)
            index2=i;

    }
    qDebug() << "index1"<< index1<<" index2"<< index2;
    if((index1-5>=0)&(index2-5>=0))
    {
        openVideoFile(videoList[index1-5],videoList[index2-5]);
//        if(vplayer->getCurrentTime()>vplayer2->getCurrentTime())
//           vplayer2->moveToTime(vplayer->getCurrentTime());
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int newOpenedFileIndex = findTimeSegment(value);
//    qDebug() << newOpenedFileIndex;
    if(openedFileIndex!=newOpenedFileIndex)
    {
        //openLogFile(newOpenedFileIndex);
    }
    else
    {

    }
}

void MainWindow::on_action_4_triggered()
{
    selectVideoFolder();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    qDebug() << "combo2" << index;
    if((index!=0)&(index==ui->comboBox->currentIndex()))
    {
        if(index==5)
            ui->comboBox_2->setCurrentIndex(index-1);
        else
            ui->comboBox_2->setCurrentIndex(index+1);
    }
//    qDebug()<< vplayer2->getCurrentMediaLocation();
//    if(vplayer->_media->currentLocation())
    if(isVideo2Opened)
    {
        if(ui->comboBox_2->currentIndex()!=0)
        {
            int videoListIndex=0;
            for(int i = 0; i < videoList.size(); i++)
            {
                if(videoList[i]==playingFile2)
                    videoListIndex=i;
        //        if(videoList[i]==playingFile2)
        //            index2=i;

            }
            qDebug() << "index1_changed"<< videoListIndex;
            int tmpPosOfMkv = playingFile2.indexOf(".mkv");
            qDebug() << "index of .mkv"<< tmpPosOfMkv;
            int beforeindex = (int)playingFile2.toLocal8Bit()[tmpPosOfMkv-1]-0x30;
            qDebug() << "beforeindex" << beforeindex;

            int deltaindex =  -ui->comboBox_2->currentIndex()+ getBeforeIndex(beforeindex);
            qDebug() <<"deltaindex" <<deltaindex;
            int tmptime = vplayer->getCurrentTime();
            changeVideo2(videoList[videoListIndex+deltaindex]);
            isVideo2Opened = true;
//            vplayer2->_player->setTime(tmptime);
        }
    }
//    else
//    {
//        ui->comboBox_2->setCurrentIndex(5-index);
//    }

}
int MainWindow::getBeforeIndex(int videoIndex)
{
    if(videoIndex==0)
        return 5;
    if(videoIndex==1)
        return 4;
    if(videoIndex==2)
        return 3;
    if(videoIndex==3)
        return 2;
    if(videoIndex==4)
        return 1;
    else return 0;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    qDebug() << "combo" << index;
    if((index!=0)&(index==ui->comboBox_2->currentIndex()))
    {
        if(index==5)
            ui->comboBox->setCurrentIndex(index-1);
        else
            ui->comboBox->setCurrentIndex(index+1);
    }
    if(isVideo1Opened)
    {
        if(ui->comboBox->currentIndex()!=0)
        {
            int videoListIndex=0;
            for(int i = 0; i < videoList.size(); i++)
            {
//                if(videoList[i]==playingFile1)
//                    videoListIndex=i;
                if(videoList[i]==playingFile1)
                    videoListIndex=i;

            }
            qDebug() << "index1_changed"<< videoListIndex;
            int tmpPosOfMkv = playingFile1.indexOf(".mkv");
            qDebug() << "index of .mkv"<< tmpPosOfMkv;
            int beforeindex = (int)playingFile1.toLocal8Bit()[tmpPosOfMkv-1]-0x30;
            qDebug() << "beforeindex" << beforeindex;
            int deltaindex =  -ui->comboBox->currentIndex()+ getBeforeIndex(beforeindex);
            qDebug() <<"deltaindex" <<deltaindex;
            int tmptime = vplayer2->getCurrentTime();
            changeVideo1(videoList[videoListIndex+deltaindex]);
            isVideo1Opened = true;
//            delayTimer->start(1);
//            vplayer->_player->setTime(tmptime);
        }
    }
//    else
//    {
//        ui->comboBox->setCurrentIndex(5-index);
//    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

}

void MainWindow::on_frameBackwardButton_clicked()
{
    if(tickCounter<=0)
        tickCounter = 25;
    tickCounter--;
    tickCounter--;

//    qDebug() << tickCounter;
    updateTime();
}

void MainWindow::on_nextFrameButton_clicked()
{
//    vplayer->s
    tickCounter++;
    updateTime();
}
