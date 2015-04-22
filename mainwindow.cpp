#include "mainwindow.h"
#include "ui_myform.h"


void MapTimeScaleDraw::drawLabel(QPainter *painter, double value) const
{
    QwtText lbl = tickLabel( painter->font(), value );
    if ( lbl.isEmpty() )
        return;
    QPointF pos = labelPosition( value );
        pos = labelPosition( value );
        if(value==timeArrLength-1)
            pos.setX(pos.x()-45);
        else if(value==timeArrLength-timeArrDelta)
            pos.setX(pos.x()-23);
    QSizeF labelSize = lbl.textSize( painter->font() );
    const QTransform transform = labelTransformation( pos, labelSize );
    painter->save();
    painter->setWorldTransform( transform, true );
    lbl.draw ( painter, QRect( QPoint( 0, 0 ), labelSize.toSize() ) );
    painter->restore();
}

QwtText MapTimeScaleDraw::label(double v) const
{
    QwtText retVal;
    QDateTime upTime = QDateTime::fromTime_t(timeArr[(int)v]).toUTC();

   if(v==0)
   {
       retVal = upTime.toString("hh:mm:ss");
       return retVal;
   }

   else return upTime.toString(format);
}
void MapTimeScaleDraw::setTimeArr(time_t *t,int l)
{
    timeArr = t;
    timeArrLength = l;
}
void MapTimeScaleDraw::setTimeArrayDelta(int val)
{
    timeArrDelta = val;
    qDebug() << "timeArrDelta"<<val;
}

//void MyThread::getTicksFromWorker(int ticks)//receiving signal from worker and emitting signal to app
//{
//    emit tickOut(ticks); //send ticks to out space
//}

//void MyThread::synchroTick(int ms)
//{
//    emit tickIn(ms);    //send ticks into worker
//}
//MyThread::MyThread(QObject *parent) :
//    QThread(parent)
//{

//}

//void MyThread::run()
//{

//}
void BackgroundDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
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
        painter->restore();
    }
}

ThreadWorker::~ThreadWorker()
{
    stopTimer();
}
ThreadWorker::ThreadWorker()
{

}

void ThreadWorker::synchroTickFromThread(int ms)
{
    tickCounter = ms;
}

void ThreadWorker::timerTick()
{
    tickCounter++;
    emit ticksToThread(tickCounter);
}

void ThreadWorker::startTimer(int step)
{
    Timer->start(step);
}

void ThreadWorker::stopTimer()
{
    Timer->stop();
}

void ThreadWorker::initWorker()
{
    Timer = new QTimer;
    tickCounter = 0;
    connect(Timer,SIGNAL(timeout()),SLOT(timerTick()),Qt::DirectConnection);

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->comboBox_2->setVisible(false);
    ui->screen1SoundButton->setVisible(false);
    ui->screen2SoundButton->setVisible(false);
    ui->nextTimeSegment->setVisible(false);
    ui->previousTimeSegment->setVisible(false);

    videoButton = new QPushButton(ui->mainToolBar);
    ui->nextFrameButton->setVisible(false);
    ui->frameBackwardButton->setVisible(false);
    ui->line->setVisible(false);
    ui->line_2->setVisible(false);
    ui->line_3->setVisible(false);
    ui->line_4->setVisible(false);
    ui->line_5->setVisible(false);
    ui->line_5->installEventFilter(this);
    ui->line_5->setAttribute( Qt::WA_TransparentForMouseEvents );

    ui->ScaleWidget->setVisible(false);
    ui->timeEdit->setDisabled(true);
    videoButton->setMaximumWidth(25);
    videoButton->setMinimumWidth(25);
    videoButton->setMaximumHeight(25);
    videoButton->setMinimumHeight(25);

    ui->mainToolBar->addWidget(videoButton);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ui->previousTimeSegment);
    ui->mainToolBar->addWidget(ui->frameBackwardButton);
    ui->mainToolBar->addWidget(ui->playButton);
    ui->mainToolBar->addWidget(ui->stopButton);
    ui->mainToolBar->addWidget(ui->nextFrameButton);
    ui->mainToolBar->addWidget(ui->nextTimeSegment);
    ui->mainToolBar->addWidget(ui->timeEdit);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ui->hideSummary);
    ui->hideCurrentStats->setEnabled(false);
    ui->hideCurrentStats->setVisible(false);

    videoButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->nextTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->previousTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->frameBackwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->nextFrameButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->screen1SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->screen1SoundButton->setEnabled(false);
    ui->screen2SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->screen2SoundButton->setEnabled(false);\

    tmpIcon = new QIcon(":new/p/hidePanel");
    ui->hideSummary->setIcon(*tmpIcon);
    ui->pushButton->setVisible(false);
    QString str = "12121212";
    timer = new QTimer(this);
    ui->progressBar->setVisible(false);
    dataMap.clear();
    timeFracts.clear();
    isFolderOpened= false;
    pageIndex=0;
    camQty = 0;
    videoLayout1 = new QHBoxLayout;
    vplayer = new VideoPlayer;
    getTimeTimer = new QTimer(0);
    waitEndStateTimer = new QTimer(this);
    showCameraNameTimer = new QTimer(this);
    hideSummarySeamlessTimer = new QTimer(this);
    syncroTimer = new QTimer(this);
    pauseDelayTimer = new QTimer(this);
    vplayer->defineVideo(/*ui->widget*/this,ui->widget);
    mythread = new QThread(this);
    ui->tableWidget_3->horizontalHeader()->setVisible(false);
    threadTimer = new QTimer(0);
    threadTimer->setInterval(10);
    threadTimer->moveToThread(mythread);
    ui->widget->setLayout(videoLayout1);
    videoLayout2 = new QHBoxLayout;
    vplayer2 = new VideoPlayer;
    vplayer2->defineVideo(ui->widget_2,ui->widget_2);

    connect(syncroTimer,SIGNAL(timeout()),this,SLOT(syncroTimerTimeout()));
    connect(threadTimer,SIGNAL(timeout()),SLOT(updateTime()));//,Qt::DirectConnection
    QObject::connect(mythread,SIGNAL(started()),threadTimer,SLOT(start()));
    QObject::connect(mythread,SIGNAL(finished()),threadTimer,SLOT(stop()));
    connect(videoButton,SIGNAL(clicked()),this,SLOT(on_action_4_triggered()));
    connect(hideSummarySeamlessTimer,SIGNAL(timeout()),this,SLOT(hideSummaryTimerTick()));
    connect(showCameraNameTimer,SIGNAL(timeout()),this,SLOT(prepareVideoMarque()));
    connect(pauseDelayTimer,SIGNAL(timeout()),this,SLOT(pauseDelayTimerTimeout()));

    ui->ScaleWidget->setAlignment(QwtScaleDraw::TopScale);
    ui->ScaleWidget->installEventFilter(this);
    secondsCounter = 0;
    realSecondsCounter = 0;
    delayMs = 0;
    logVideoDelta = 0;
    logVideoDeltaCounter = 0;
    lastDelay = 0;
    setButtonPanelEnabled(false);
    getTimeTickCounter =0;
    log = new logProcessor;
    interpreter = new TMIinterpretator;
    msys = new msgSys;
    isVideo1Opened = false;
    isVideo2Opened = false;
    ui->widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->widget_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    currentWidget1Geometry = ui->widget->geometry();
    currentWidget2Geometry = ui->widget_2->geometry();
    widget1X = currentWidget1Geometry.x();
    widget1Y = currentWidget1Geometry.y();
    baseVideo1Geometry = vplayer->getGeometry();
    baseVideo2Geometry = vplayer2->getGeometry();
    this->setWindowState(Qt::WindowMaximized);\
    ui->tableWidget->setItemDelegate(new BackgroundDelegate(this));
    ui->tableWidget->setStyleSheet("selection-background-color: rgba(128, 128, 128, 40);");
    timeCellIndex=0;
    camButtonsLayout1 = new QGridLayout();
    camButtonsLayout2 = new QGridLayout();
    ui->widget_3->setLayout(camButtonsLayout1);
    ui->widget_4->setLayout(camButtonsLayout2);
    camButtonsLayout1->setContentsMargins(3,3,3,3);
    camButtonsLayout2->setContentsMargins(3,3,3,3);
    makeUpSlider();
    this->clearFocus();
    ui->playButton->setFocus();
}

void MainWindow::correctCellSeekerPosition(int newPos)
{
    ui->tableWidget->lower();
    ui->ScaleWidget->lower();
    ui->line_5->setLineWidth(4);
    ui->line_5->setPalette(ui->ScaleWidget->palette());
    QRect tmp = ui->line_5->rect();
    QPoint ptmp;
    ptmp = ui->ScaleWidget->pos();
    ptmp.setX(ptmp.x()+ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn()));
    if(newPos>=0)
    {
        tmp.setX(ptmp.x()+newPos);
        tmp.setY(ptmp.y()+15);
        tmp.setWidth(3);
        tmp.setHeight(22);//-tmp.height());
        ui->line_5->setGeometry(tmp);
        ui->line_5->setVisible(true);
    }
}

void MainWindow::makeUpSlider()
{

    ui->horizontalSlider->setStyleSheet(
                "QSlider::groove:horizontal {"
                "border: 1px solid #bbb;"
                "background: white;"
                "height: 10px;"
               // "border-radius: 4px;"
                "}"

                "QSlider::sub-page:horizontal {"
                "background: white;"//qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,stop: 0 #00EE00, stop: 1 #00CD00);"
                "background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #00EE00, stop: 1 #00CD00);"
                "border: 1px solid #777;"
                " height: 10px;"
              //  " border-radius: 4px;"
                " }"

                "QSlider::add-page:horizontal {"
                "background: #fff;"
                " border: 1px solid #777;"
                "height: 10px;"
            //    "border-radius: 4px;"
                " }"

                "QSlider::handle:horizontal {"
                " background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #eee, stop:1 #ccc);"
                " border: 1px solid #777;"
                "width: 1px;"
                "margin-top: -2px;"
                " margin-bottom: -2px;"
              //  "border-radius: 4px;"
                " }"

                " QSlider::handle:horizontal:hover {"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #fff, stop:1 #ddd);"
                " border: 1px solid #444;"
               // "border-radius: 4px;"
                "}"

                "QSlider::sub-page:horizontal:disabled {"
                "background: #bbb;"
                "border-color: #999;"
                " }"

                "QSlider::add-page:horizontal:disabled {"
                "background: #eee;"
                "border-color: #999;"
                "}"

                "QSlider::handle:horizontal:disabled {"
                "background: #eee;"
                "border: 1px solid #aaa;"
               // "border-radius: 4px;"
                "}"
                                        );
}

void MainWindow::correctFramePosition()
{
//    ui->line->setVisible(true);
//    ui->line_2->setVisible(true);
//    ui->line_3->setVisible(true);
//    ui->line_4->setVisible(true);

//    QRect tmp = ui->line->rect();
//    QPoint ptmp = ui->horizontalSlider->pos();
//    //top line
//    tmp.setX(ptmp.x());
//    tmp.setY(ptmp.y()-tmp.height());
//    tmp.setSize(ui->line->rect().size());

//    ui->line->setGeometry(tmp);
//    //left line
//    tmp = ui->line_2->rect();
//    tmp.setX(ptmp.x()-1);
//    tmp.setY(ptmp.y()-1);
//    tmp.setHeight(ui->horizontalSlider->height());
//    tmp.setWidth(1);
//    ui->line_2->setGeometry(tmp);
//    //right line
//    tmp = ui->line_3->rect();
//    tmp.setX(ptmp.x()+ui->horizontalSlider->width());
//    tmp.setY(ptmp.y()-1);
//    tmp.setHeight(ui->horizontalSlider->height());
//    tmp.setWidth(1);
//    ui->line_3->setGeometry(tmp);
//    //bottom line
//    tmp = ui->line_4->rect();
//    tmp.setX(ptmp.x());
//    tmp.setY(ptmp.y()+ui->horizontalSlider->height()-ui->line->height()+1);
//    tmp.setSize(ui->line->rect().size());

//    ui->line_4->setGeometry(tmp);

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int X1, Y1, X2, Y2;
    currentWidget1Geometry = ui->widget->geometry();
    currentWidget2Geometry = ui->widget_2->geometry();
    baseVideo1Geometry.setSize(ui->widget->geometry().size());
    baseVideo1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
    currentWidget1Geometry.setCoords(X1,Y1,X2,Y2);
    vplayer->changeGeometry(currentWidget1Geometry);
    baseVideo2Geometry.setSize(ui->widget_2->geometry().size());
    baseVideo2Geometry.getCoords(&X1,&Y1,&X2,&Y2);
    currentWidget2Geometry.setCoords(X1,Y1,X2,Y2);
    float totalRelativeWidth=0;
    int totalColumnWidth = 0;
        vplayer2->changeGeometry(currentWidget2Geometry);
        if(dataMap.size()!=0)
        {
            for(int i = 0; i < ui->tableWidget->columnCount(); i++)
                totalColumnWidth+=(float)((ui->tableWidget->width())*timeCells[i].relativeWidth);
            if(ui->ScaleWidget->width()!=totalColumnWidth)
            {
                float correctGain=(float)(ui->ScaleWidget->width())/((float)(totalColumnWidth));
                totalColumnWidth=0;
                totalRelativeWidth=0;
                for(int i =0; i < timeCells.size();i++)
                {
                  ui->tableWidget->setColumnWidth(i,((float)ui->tableWidget->width()*timeCells[i].relativeWidth*(float)correctGain));
                  totalRelativeWidth+=timeCells[i].relativeWidth;
                  totalColumnWidth+=ui->tableWidget->columnWidth(i);
                  if(timeCells[i].donor==1)
                      ui->tableWidget->setColumnWidth(i,ui->tableWidget->columnWidth(i)-1);
                  if(timeCells[i].donor==2)
                      ui->tableWidget->setColumnWidth(i,ui->tableWidget->columnWidth(i)+1);
                }
            }
        }
        else
        {

        }
        correctCellSeekerPosition(((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->ScaleWidget->width());
        correctFramePosition();
}

int MainWindow::initColoredScale()
{
    int length = dataMap.size();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    for(int a = 0; a< timeCells.size(); a++)
    {
        ui->tableWidget->insertColumn(a);
        ui->tableWidget->setItem(0,a, new QTableWidgetItem);
        ui->tableWidget->item(0,a)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui->tableWidget->item(0,a)->setToolTip((QDateTime::fromTime_t(timeCells[a].beginTime).toUTC().time()).toString()+" - "+(QDateTime::fromTime_t(timeCells[a].endTime).toUTC().time()).toString());
        ui->tableWidget->setColumnWidth(a,timeCells[a].colWidth);
        switch(timeCells[a].cellType)
        {
            case 0:
                {
                  ui->tableWidget->item(0,a)->setBackground(Qt::green);
                  break;
                }
            case 1:
                {
                  ui->tableWidget->item(0,a)->setBackground(Qt::gray);
                  break;
                }
            case 2:
                {
                  ui->tableWidget->item(0,a)->setBackground(Qt::white);
                  break;
                }
            case 3:
                {
                  ui->tableWidget->item(0,a)->setBackground(Qt::red);
                  break;
                }
            default:
                break;
        }
    }
    if(length!=0)
    {
        QFont font;
        ui->ScaleWidget->setVisible(true);
        font.setStyleName("Courier");
        font.setBold(true);
        font.setPixelSize(10);
        ui->tableWidget->setFont(font);
        int timeScaleTickCounter = 23;
        int tmpTotalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
        time_t step = (int)(tmpTotalTime/(timeScaleTickCounter-1));
        time_t vals[tmpTotalTime];
        for(int i =0; i < tmpTotalTime-1; i++)
        {
            vals[i] = timeCells[0].beginTime+i;
        }
        vals[tmpTotalTime-1] = timeCells[timeCells.size()-1].endTime;
        QList<double> ticks[QwtScaleDiv::NTickTypes];
        QList<double> &majorTicks = ticks[QwtScaleDiv::MajorTick];
        QList<double> &minorTicks = ticks[QwtScaleDiv::MinorTick];
        int tmpStartTime = timeCells[0].beginTime%7200;
        for (int i = 0; i < tmpTotalTime ; i++)
        {
            if(i==0)
                majorTicks.append(i);
            if(i==tmpTotalTime-1)
                majorTicks.append(i);
            if ((tmpStartTime+i) % 7200 == 0)
            {
                majorTicks.append(i);
            }
            else if ((tmpStartTime+i)%3600==0)
            {
                minorTicks.append(i);
            }
        }
              if((minorTicks.count()>0)&(majorTicks.count()>1))
              {
                if(minorTicks.at(0)>majorTicks.at(1))
                    majorTicks.removeAt(1);
              }
              if((minorTicks.count()>1)&(majorTicks.count()>2))
              {
                if(minorTicks.at(minorTicks.size()-1)<majorTicks.at(majorTicks.size()-2))
                    majorTicks.removeAt(majorTicks.size()-2);
              }
        QwtScaleDiv mTimeScaleDiv = QwtScaleDiv(majorTicks.first(), majorTicks.last(), ticks);
        mapTimeScale = new MapTimeScaleDraw("hh:mm:ss");
        mapTimeScale->setTimeArrayDelta(tmpTotalTime-majorTicks[majorTicks.size()-2]);
        mapTimeScale->setTimeArr(vals,tmpTotalTime);
        mapTimeScale->setLabelAlignment(Qt::AlignRight);
        ui->ScaleWidget->setScaleDraw(mapTimeScale);
        ui->ScaleWidget->setContentsMargins(0,0,-43,0);//leveling scale labels alignment balance
        QwtScaleTransformation *tr= new QwtScaleTransformation(QwtScaleTransformation::Linear);
        ui->ScaleWidget->setScaleDiv(tr,mTimeScaleDiv);
    }
    else return 1;
    moveToAnotherTimeSegment(0,vplayer->getVideoState(),vplayer2->getVideoState());
    syncroTimer->start(1000);
    ui->tableWidget->selectColumn(0);
    updateCamWidgetsState();
    correctCellSeekerPosition(((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->ScaleWidget->width());
    ui->tableWidget->viewport()->installEventFilter(this);
    this->resize(this->size().width()-1,this->size().height()-1);
    this->resize(this->size().width()+1,this->size().height()+1);
    return 0;
}


MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::initThermoMaxs(QVector <long> *thermoMaxs)
{
    int retval = 0;
    for(int i = 0; i < interpreter->interpreterRecordsCount; i++)
    {
            if((interpreter->TInterpItemArray[i].typ&0xffff) == 34 )
            {
                if(QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name)=="LAS_Counter                    ")
                {
                    retval++;
                    thermoMaxs->append(interpreter->TInterpItemArray[i].max);
                }
            }
            if((interpreter->TInterpItemArray[i].typ&0xffff) == 8 )
            {
                QString tmpstr = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
                if((tmpstr == "LDS_Group1                     ")|(tmpstr == "LDS_Group2                     ")|(tmpstr == "LDS_Group3                     ")|(tmpstr == "LDS_Group4                     ")|(tmpstr == "LDS_Group5                     "))
                {
                    retval++;
                    thermoMaxs->append(interpreter->TInterpItemArray[i].max);
                }
            }
    }
    return retval;
}

int MainWindow::initThermoNames(QVector<QString> *thermoNames, QVector<int> *dataSequence)
{
    int retval = 0;
    log->selectSegment(bigTableID);
    char buffArr1[log->segmentHeader.size];
    log->readSegment(buffArr1, log->segmentHeader.size );
    interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
    interpreter->setInterpretationTable(buffArr1,interpreter->interpreterRecordsCount);
    for(int i = 0; i < interpreter->interpreterRecordsCount; i++)
    {
        if(interpreter->TInterpItemArray[i].level==1)
        {
            if((interpreter->TInterpItemArray[i].typ&0xffff) == 34 )//|(QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name)=="LAS_Counter                    "))
            {
                retval++;
                dataSequence->append(34);
                thermoNames->append(interpreter->TInterpItemArray[i].name);
            }
            QString tmpstr = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
            if(((interpreter->TInterpItemArray[i].typ&0xffff) == 8 ))
            {
                retval++;
                dataSequence->append(8);
                thermoNames->append(interpreter->TInterpItemArray[i].name);
            }
        }
    }
    return retval;
}

//int MainWindow::getDataType(int index)
//{

//    return par.paramsSequence[index];
//}

//int MainWindow::getTypeIndex(int index)//returns type dependent index of given global struct index
//{
//    int retval=0;
//    for(int i = 0; i < index+1; i++)
//    {
//        if(getDataType(index)==par.paramsSequence[i])
//            retval++;
//    }
//    return retval;
//}

int MainWindow::makeStructFromRecord(char *record,/*int recsize,*/ dataParams* dp)//lets do it
{
    int recIndex=0;
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
            case 34 ://it's double
            {
                double tmpDbl;
                if(QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name) =="LAS_Counter                    ")
                {
                    tmpDbl = interpreter->fieldDouble(&record[recIndex]);
                    dp->doubleTypes.append((double)tmpDbl);
                    dp->paramsSequence.append(34);
                    dp->paramsVisibleArr.append(1);
                }
                break;
            }
            case 8 :
            {
                bool flag = false;
                QString tmpstr = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
                if((tmpstr == "LDS_Group1                     ")|(tmpstr == "LDS_Group2                     ")|(tmpstr == "LDS_Group3                     ")|(tmpstr == "LDS_Group4                     ")|(tmpstr == "LDS_Group5                     "))
                {
                    flag = (bool)interpreter->fieldFlag(&record[recIndex],&interpreter->TInterpItemArray[i].mask_);
                    dp->flagTypes.append(interpreter->fieldFlag(&record[recIndex], &interpreter->TInterpItemArray[i].mask_));
                    dp->paramsSequence.append(8);
                    dp->paramsVisibleArr.append(1);
                }

                break;
            }
            default:
            {
                break;
            }
            }
    }
    return 0;
}


int MainWindow::fillHeadTable()
{
    return 0;
}

int MainWindow::initBigThermos(int qty)//
{
    qty = 2;
    QwtThermo *big1 = new QwtThermo;
    QwtThermo *big2 = new QwtThermo;
    ui->horizontalLayout_4->addWidget(big1);
    ui->horizontalLayout_4->addWidget(big2);
    big1->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
    big2->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
    return 0;
}

int MainWindow::createFullListOfVideos(int offsetsQty)
{
    camQty = offsetsQty;
    if((videoList.size()/offsetsQty)>=logList.size())
    {
        return 1;
    }
    videoList.clear();
    for(int i =0; i < logList.size();i++)
    {
        QString tmpstr;
        for(char j = 0; j < offsetsQty; j++)
        {
            tmpstr = logList.at(i);
            tmpstr.chop(4);
            tmpstr.append("_");
            tmpstr.append(j+0x30);
            tmpstr.append(".mkv");
            videoList.append(tmpstr);
        }

    }
    return 0;
}

int MainWindow::calculateMaxOffset()
{
    if(offsetsAvailable)
    {
        maxCamOffset = dataMap[pageIndex].camTimeOffsets.at(0);
        for(int j = 0; j < dataMap[pageIndex].camTimeOffsets.size(); j++)
        {
            if(dataMap[pageIndex].camTimeOffsets.at(j)>maxCamOffset)
                maxCamOffset = dataMap[pageIndex].camTimeOffsets.at(j);
        }
        return maxCamOffset;
    }
    maxCamOffset = 0;
    return -1;
}

bool MainWindow::createTimeSegment(QStringList *listOfLogs)
{
    int success = true;
    time_t one,two;
    videoTimes.clear();
    timeSegment.clear();
    camOffsets.clear();
    offsetsCounter.clear();
    ui->progressBar->setMaximum(listOfLogs->size()-1);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
    correctFramePosition();
    ui->mainToolBar->setEnabled(false);
        for(int i = 0; i < listOfLogs->size();i++)//something gets from listOfLogs
        {
            if(success)
            {
                    int tmpCount = ui->comboBox->count()-1;
                    if(tmpCount<0)
                        tmpCount = 0;
                    if(openLogFile(listOfLogs->at(i))==-1)//if(openLogFile(videoList.at(i*tmpCount))==-1)
                    {
                        return false;
                    }
                    if(readCamOffsetsAndTimeEdges(&one, &two,&beginTimeFract,&endTimeFract,i))
                    {
                        offsetsAvailable = false;
                        newMessage.setWindowTitle("Внимание!");
                        newMessage.setText("В логе "+logWorkingDir+"/"+ logList.at(i)+ " отсутствуют камерные задержки. " );
                        newMessage.exec();
                    }
                    else
                        offsetsAvailable = true;
                    if(offsetsAvailable)
                    {
                        maxCamOffset = camOffsets.at(0);
                        for(int j = 0; j < camOffsets.size(); j++)
                        {
                            if(camOffsets.at(j)>maxCamOffset)
                                maxCamOffset = camOffsets.at(j);
                        }
                    }
                    if(readHeadTableData()==0)
                    {
                        videoOnly = false;
                    }
                    else
                        videoOnly = true;
                  if(!videoOnly)
                  {
                    if(two<one)
                        inverseTime = true;
                    else inverseTime = false;
                    timeSegment.append(one);
                    timeSegment.append(two);
                  }
                  else
                  {
                      success = false;
                  }
            }
            ui->progressBar->setValue(i);
        }
        for(int a = 0; a< videoTimes.size();a++)
        {

        }
                    ui->progressBar->setVisible(false);
                    correctFramePosition();
    ui->mainToolBar->setEnabled(true);
    for(int j=0; j< timeSegment.size(); j++)
    {

    }

    return success;
}
/*
 *From each currently selected time segment this function makes movable slider wich user can freely operate with
 */
int MainWindow::createFakeTimeScale(int mode,int column)
{
    if(mode!=0)
    {
        vplayer->stop();
        vplayer2->stop();
        correctFramePosition();
    }
    mythread->exit();
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setMaximum(0);
    int sliderScaleVal = 0;
    switch(mode)
    {
        case 0:
                {
                    sliderScaleVal = timeCells[column].endTime- timeCells[column].beginTime;
                    break;
                }
        default:
                {
                    vplayer->stop();
                    correctFramePosition();
                    vplayer2->stop();
                    correctFramePosition();
                    sliderScaleVal = timeCells[column].endTime- timeCells[column].beginTime;
                    break;
                }
    }
        ui->horizontalSlider->setMaximum(sliderScaleVal);
        mythread->start();
        correctFramePosition();
    return 0;
}

int MainWindow::initSmallThermos(int qty, QVector <QString> names, QVector <long> maxs,QVector <int> dataSequence)
{
    QHBoxLayout thermoLayout[4];
    int doubleCounter=0, flagCounter=0;
    for(int i = 0; i < dataSequence.count(); i++)
    {
        switch(dataSequence[i])
        {

            case 34:
            {
                parameterBar.insert(doubleCounter,new QwtThermo(0));
                parameterBar[doubleCounter]->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
                if(maxs[doubleCounter]>0)
                    parameterBar[doubleCounter]->setMaxValue(maxs[doubleCounter]);
                else
                    parameterBar[doubleCounter]->setMaxValue(32);
                QLabel *tmptext = new QLabel(names[i]);
                thermoVals.append(new QLineEdit("0"));
                QRect tmpG = thermoVals.at(doubleCounter)->geometry();
                tmpG.setWidth(10);
                thermoVals.at(doubleCounter)->setBaseSize(10,5);
                thermoVals.at(doubleCounter)->setFrame(false);
                thermoVals.at(doubleCounter)->setGeometry(tmpG);
                thermoVals.at(doubleCounter)->setEnabled(false);
                thermoVals[doubleCounter]->setPalette(ui->tableWidget_3->palette());
                thermoVals.at(doubleCounter)->installEventFilter(this);
                ui->gridLayout_2->addWidget(parameterBar[doubleCounter],2*(int)(i/4)+1,i%4,Qt::AlignLeft);
                ui->gridLayout_2->addWidget(tmptext,2*(int)(i/4),i%4, Qt::AlignLeft);
                ui->gridLayout_2->addWidget(thermoVals[doubleCounter],2*(int)(i/4),i%4, Qt::AlignRight);
                doubleCounter++;
                break;
            }
            case 8:
            {
                checkBoxes.insert(flagCounter,new QCheckBox(names[i]));
                checkBoxes[flagCounter]->setEnabled(false);
                checkBoxes[flagCounter]->setStyleSheet("QCheckBox::disabled{color:black;}""QCheckBox::indicator:checked:disabled{background: black;}""QCheckBox::indicator:unchecked:disabled{border: 1px solid black;}");
                ui->gridLayout_2->addWidget(checkBoxes[flagCounter],2*(int)(i/4)+1,i%4,Qt::AlignLeft);
                flagCounter++;
            }
            default:
                break;
        }
    }
    for(int i = 0; i < 4; i++)
    {

    }
    return 0;
}

void MainWindow::selectVideoFolder()
{

    if(accepted)
    {
        QString videodir = logWorkingDir;
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
            logWorkingDir = videodir;
            openVideoFilesFolder(&videoList);
            openLogFilesFolder(&logList);
            isFolderOpened = true;
        }
        if((VideoFileError==0)&(LogFileError==0))
        {
            setButtonPanelEnabled(true);
        }
    }
    accepted = false;
}

int MainWindow::checkFolderName(QString name)//correct folder name is type as YYYY.MM.DD
{
    int index = 0;
    index = name.indexOf("/");
    QDate date;
    date.setDate(1900,1,1);
    while(index!=-1)
    {
        name.remove(0,index+1);
        date = QDate::fromString(name,"yyyy.MM.dd");
        index = name.indexOf("/");
    }

    if((date.isValid())&&(!date.isNull()))
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

void MainWindow::selectLogFolder()
{
    QString logdir = "";
    QFileDialog dlg;//(this, tr("Выбор директории файлов регистратора"));
    logdir = dlg.getExistingDirectory(this, tr("Выбор директории лог-файлов"),QDir::homePath());
    if((logdir!= "")&&(checkFolderName(logdir)==0))
    {
        if(logdir!=logWorkingDir)
        {
                if(isFolderOpened)
                    terminateAll();
                accepted = true;
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
                    videoWorkingDir = logdir;
                    LogFileError = 0;
                    isFolderOpened = true;
                }
                if((VideoFileError==0)&(LogFileError==0))
                {
                    setButtonPanelEnabled(true);
                }
        }
        else accepted = false;
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
            aviCounter++;
        }
    }
    return aviCounter;
}

//work with files
void MainWindow::updateTime()//i don't like this func
{
    ui->timeEdit->setTime(QDateTime::fromTime_t(timeCells[ui->tableWidget->currentColumn()].beginTime+delayMs/100).toUTC().time());
    tickCounter++;
    if((ui->horizontalSlider->value()>=ui->horizontalSlider->maximum())&(ui->horizontalSlider->maximum()>0))//&(value!=lastVal))
    {
        if((!isSliderPressed)&(!seekerIsBusy))
        {
            ui->horizontalSlider->setValue(0);
            moveToNextTimeFrame();
            ui->horizontalSlider->setEnabled(true);
        }
        else
        {

        }
    }
    if(!videoOnly)
        delayMs++;
    if(delayMs >= maxCamOffset)
    {

    }
    int currentDelayMs = delayMs;
    if(currentDelayMs%100==0)//second passed
    {

        if(timeCellIndex!=ui->tableWidget->currentColumn())
        {
            int tmpval = ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();//-ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn());
            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
            getDelayMsToSet(tmpval,totalTime);
            delayMs = delayMsToSet;\
            ui->horizontalSlider->setValue(delayMs/100);
            setSliderPosition();
            updateTime();
        }
        ui->horizontalSlider->setValue((int)currentDelayMs/100);
        tickCounter=0;
        int pos = ((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->tableWidget->width();
        correctCellSeekerPosition(pos);
        if(!videoOnly)
        {
            dataParams *tmpDP = new dataParams;
            lastRecNum = getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)currentDelayMs/100,0,0);
            makeStructFromRecord(log->record,tmpDP);
            updateThermos(*tmpDP);
        }
    }
    else if(currentDelayMs%10==0)
    {
        correctFramePosition();
        int pos = ((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->tableWidget->width();
        correctCellSeekerPosition(pos);
        if(!videoOnly)
        {
            dataParams *tmpDP = new dataParams;
            ui->horizontalSlider->setValue((int)currentDelayMs/100);
            if(ui->horizontalSlider->value()==0)
                lastRecNum = getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)currentDelayMs/100,/*beginTimeFract*/0,0);//we need to define timeFract here
            else
                lastRecNum = getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)currentDelayMs/100,(int)((currentDelayMs%100)*2.56),0);//we need to define timeFract here
            makeStructFromRecord(log->record,tmpDP);
            updateThermos(*tmpDP);

        }
    }
    if(videoOnly)
    {
      ui->horizontalSlider->setValue((int)currentDelayMs);
    }
}

int MainWindow::updateThermos(dataParams dp)
{
    int doubleCounter=0, flagCounter=0;
    if(timeCells[ui->tableWidget->currentColumn()].cellType!=2)
    {
        for(int i = 0; i < dp.paramsSequence.count(); i++)
        {

            switch(dp.paramsSequence[i])
            {
                case 34:
                {
                    parameterBar[doubleCounter]->setValue(dp.doubleTypes[doubleCounter]);
                    thermoVals[doubleCounter]->setText(QString::number(dp.doubleTypes[doubleCounter],10,2));
                    doubleCounter++;
                    break;
                }
                case 8:
                {
                    QString tmp = "0";
                    double db = 0;
                    if(dp.flagTypes[flagCounter])
                    {
                        tmp = "1";
                        db = 1;
                    }
                    checkBoxes[flagCounter]->setChecked(dp.flagTypes[flagCounter]);
                    flagCounter++;
                    break;
                }
                default:
                    break;
            }
        }
    }
    else
        log->clearBuff();
    return 0;
}

int MainWindow::getRecordNumClosestToTime(time_t currentTime, int timeFract, int lastRecord /*char *rec*/) //search record number using time
{
    long tmpErr = log->selectSegment(bigTableID);
    int recIndex=0;
    bool timeFractSearchFlag = false;
    time_t recTime;
    time_t beforeTime;
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
                         {
                             switch(interpreter->TInterpItemArray[i].typ&0xffff)
                             {
                             case 10 :
                             {
                                 recTime = (time_t)interpreter->fieldInt(&log->record[recIndex]);
                                 if(interpreter->TInterpItemArray[i].name!="PowOnTime")
                                 {
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
                                            {
                                                 return index;
                                            }
                                         }
                                         else
                                         {
                                             if(currentTime<recTime)
                                             {
                                                 return index;
                                             }
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
                             default:
                             {
                                 break;
                             }
                             }
                         }
                     }
                 }
        }
    }
    return -1;
}

int MainWindow::readCamOffsetsAndTimeEdges(time_t *beginTime, time_t *endTime, unsigned char *beginTimeFract, unsigned char *endTimeFract,int globalIterator)
{
    int tmpErr = log->selectSegment(camOffsetsTableID);
    int timeIndex=0; // 0=Time; 1 = StartTime; 2 = ShutdownTime;
    int timeFractIndex = 0,currentval=0;//0 = TimeFrac; 1 = StartTimeFrac; 2 = ShutdownTimeFrac;
    int camoffsetscounter=0,counter=0;
    short int tmp=0;
    if(tmpErr==0)
    {
        char buffArr1[log->segmentHeader.size];
                log->readSegment(buffArr1, log->segmentHeader.size );
                interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
                interpreter->setInterpretationTable(buffArr1,interpreter->interpreterRecordsCount);
                for(int i =0; i <interpreter->interpreterRecordsCount; i++)
                {
                    if(interpreter->TInterpItemArray[i].typ==4)
                    {
                        if(ui->comboBox->count()<11)
                        {
                            ui->comboBox->addItem(QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name));
                            ui->comboBox_2->addItem(QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name));
                            cameraButton camBtn1,camBtn2;
                            camBtn1.camButton = new QPushButton(ui->widget_3);
                            camBtn1.enabled = false;
                            camBtn1.active = false;
                            camBtn1.camButton->setText("Камера"+QString::number(counter+1,10));
                            camBtn1.camButton->raise();
                            camBtn1.camButton->setAutoFillBackground(true);
                            camBtn1.camButton->setStyleSheet("QPushButton{ background-color : white; color : black; }");
                            camBtn2.camButton = new QPushButton(ui->widget_3);
                            camBtn2.enabled = false;
                            camBtn2.active = false;
                            camBtn2.camButton->setText("Камера"+QString::number(counter+1,10));
                            camBtn2.camButton->raise();
                            camBtn2.camButton->setAutoFillBackground(true);
                            camBtn2.camButton->setStyleSheet("QPushButton{ background-color : white; color : black; }");
                            camButtonsLayout1->addWidget(camBtn1.camButton,counter/5,counter%5+1);
                            camButtonsLayout2->addWidget(camBtn2.camButton,counter/5,counter%5+1);
                            qDebug() << "i%5"<< counter%5 << counter;
                            camButtons1.append(camBtn1);
                            camButtons2.append(camBtn2);
                            camButtons1[counter].camButton->setObjectName("camBtn1"+QString::number(counter+1,10));
                            camButtons2[counter].camButton->setObjectName("camBtn2"+QString::number(counter+1,10));
                            connect(camButtons1[counter].camButton,SIGNAL(clicked()),this,SLOT(pushCameraButton()));
                            connect(camButtons2[counter].camButton,SIGNAL(clicked()),this,SLOT(pushCameraButton()));
                            counter++;
                        }
                    }
                }

               /*
                *from here we start to processing data from small table
                */
                  if(log->selectSegment(camOffsetsTableID&0x7fffffff))
                  {
                      QVariant tmpVal = tmpErr;
                      newMessage.setWindowTitle("Ошибка!");
                      newMessage.setText("Файл журнала регистратора поврежден. " + tmpVal.toString());
                      newMessage.exec();
                  }
                            int tmpRecI = 0;
                            log->readRecord(log->segmentHeader.recordSize, log->segmentHeader.size, log->logDataPointer);
                            for (int i = 0; i < interpreter->interpreterRecordsCount; i++)
                            {
                                tmpRecI=interpreter->TInterpItemArray[i].offset;

                                if(interpreter->TInterpItemArray[i].typ==4)
                                {
                                    long tmpVal = interpreter->fieldInt(&log->record[tmpRecI]);
                                    QString tmp = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
                                    camOffsets.append(tmpVal);
                                    camoffsetscounter++;
                                }
                                if(interpreter->TInterpItemArray[i].typ==3)
                                {
                                   unsigned short tmpVal = interpreter->fieldShort(&log->record[tmpRecI]);
                                            if(timeFractIndex==0)
                                            {
                                                *beginTimeFract = tmpVal;
                                                timeFracts.append(tmpVal);
                                            }
                                            if(timeFractIndex==1);
                                                                 //we need here something like global variable StartTimeFract
                                            if(timeFractIndex==2);
                                                                    //we need here something like global variable ShutDownTimeFract
                                            timeFractIndex++;
                                }
                                if(interpreter->TInterpItemArray[i].typ==10)
                                {
                                    long tmpVal = interpreter->fieldInt(&log->record[tmpRecI]);
                                    if(timeIndex==0)
                                    {
                                        *beginTime = (time_t)tmpVal;
                                        qDebug() <<"begin time" <<QDateTime::fromTime_t(*beginTime).toUTC();
                                    }
                                    if(timeIndex==1)
                                    {
                                         //we need here something like global variable StartTime?
                                    }
                                    if(timeIndex==2)
                                    {
                                          //we need here something like global variable ShutDownTime
                                    }
                                    timeIndex++;
                                }
                            }
                            if(createFullListOfVideos(camoffsetscounter)==0)
                            {
                                for(int k = 0; k< videoList.size(); k++)
                                {

                                }
                            }
                            vplayer->stop();
                            QFile filetocheck;
                            int tmpOffsetsCounter = camoffsetscounter;
                                for(int j = 0; j < camoffsetscounter; j++)
                                {
                                    filetocheck.close();
                                    if(camOffsets.at(j)<=0)
                                        tmpOffsetsCounter--;
                                    filetocheck.setFileName(videoWorkingDir+"/"+videoList.at(globalIterator*camoffsetscounter+j));
                                    if(filetocheck.exists())
                                    {
                                        if(filetocheck.size()>1000)
                                        {
                                            vplayer->openLocal(videoWorkingDir+"/"+videoList.at(globalIterator*camoffsetscounter+j));
                                            currentval = (vplayer->getVideoLength()+camOffsets.at(j))/1000;
                                            tmp = (timeFracts.at(timeFracts.size()-1)+vplayer->getVideoLength()+camOffsets.at(globalIterator*camoffsetscounter+j))%1000;
                                        }
                                        else
                                        {
                                            currentval = 0;
                                            tmp = 0;
                                        }
                                        videoTimes.append(currentval);
                                        timeFracts.append(tmp);
                                        vplayer->stop();
                                        correctFramePosition();
                                    }
                                        else
                                        videoTimes.append(0);
                                }
                            time_t timeFromBigTable1,timeFromBigTable2;
                            readTimeEdges(&timeFromBigTable1,&timeFromBigTable2);
                            *endTime = *beginTime;
                            logEndTimes.append(timeFromBigTable2);
                            offsetsCounter.append(camoffsetscounter);
    }
    camButtonsLayout1->addWidget(ui->screen1SoundButton,0,0);
    ui->screen1SoundButton->setVisible(true);
    camButtonsLayout2->addWidget(ui->screen2SoundButton,0,0);
    ui->screen2SoundButton->setVisible(true);
    return tmpErr;
}

void MainWindow::setCameraButtonsToDefault()
{
    bool firstNotZeroCamNumber=false;//flag that shows if the first
        for(int i=0; i < dataMap[0].camTimeOffsets.size();i++)
        {
            if(dataMap[0].camTimeOffsets[i]<=0)
            {
                camButtons1[i].enabled = false;
                camButtons1[i].active = false;
                camButtons1[i].camButton->setStyleSheet("QPushButton{ background-color : lightgray; color : gray; }");
            }
            else
            {

                camButtons1[i].enabled = true;
                if(!firstNotZeroCamNumber)
                {
                    firstNotZeroCamNumber=true;
                    camButtons1[i].active = true;
                     camButtons1[i].camButton->setStyleSheet("QPushButton{ background-color : white; color : green; border-style: outset;border-width: 3px;padding:4px;font: bold 11px;}");
                }
            }
        }
        firstNotZeroCamNumber=false;
        for(int i=0; i < dataMap[0].camTimeOffsets.size();i++)
        {
            if(dataMap[0].camTimeOffsets[i]<=0)
            {
                camButtons2[i].enabled = false;
                camButtons2[i].active = false;
                camButtons2[i].camButton->setStyleSheet("QPushButton{ background-color : lightgray; color : gray; }");
            }
            else
            {

                camButtons2[i].enabled = true;
                if((!firstNotZeroCamNumber)&(!camButtons1[i].active))
                {
                    firstNotZeroCamNumber=true;
                    camButtons2[i].active = true;
                     camButtons2[i].camButton->setStyleSheet("QPushButton{ background-color : white; color : green; border-style: outset;border-width: 3px;padding:4px;font: bold 11px;}");
                }
            }
        }
}

int MainWindow::updateCameraButtons1(int number)
{
    qDebug() << "number"<<number;
    bool updated = false;
    if(number<0)
    {

    }
    else
    {
        if(camButtons2[number-1].active!=true)
        {
            updated=true;
            camButtons1[number-1].active=true;
             camButtons1[number-1].camButton->setStyleSheet("QPushButton{ background-color : white; color : green; border-style: outset;border-width: 3px;padding:4px;font: bold 11px;}");
        }
        for(int i =0; i < camButtons1.size(); i++)
        {
            if(updated)
            {
                if(camButtons1[i].enabled)
                {
                    if(number-1!=i)
                    {
                       camButtons1[i].active = false;
                       camButtons1[i].camButton->setStyleSheet("QPushButton{ background-color : white; color : black; }");
                    }
                }
                else
                {
                    camButtons1[i].active = false;
                    camButtons1[i].camButton->setEnabled(false);
                    camButtons1[i].camButton->setStyleSheet("QPushButton{ background-color : lightgray; color : gray; }");
                }
            }
        }

    }
    if(updated)
        return 1;
    else
        return 0;
}


int MainWindow::updateCameraButtons2(int number)
{
        qDebug() << "number"<<number;
        bool updated = false;
    if(number<0)
    {

    }
    else
    {
        if(camButtons1[number-1].active!=true)
        {
            updated = true;
            camButtons2[number-1].active=true;
             camButtons2[number-1].camButton->setStyleSheet("QPushButton{ background-color : white; color : green; border-style: outset;border-width: 3px;padding:4px;font: bold 11px;}");
        }
        for(int i =0; i < camButtons2.size(); i++)
        {
            if(updated)
            {
                if(camButtons2[i].enabled)
                {
                    if(number-1!=i)
                    {
                        camButtons2[i].active = false;
                        camButtons2[i].camButton->setStyleSheet("QPushButton{ background-color : white; color : black; }");
                    }
                }
                else
                {
                    camButtons2[i].active = false;
                    camButtons2[i].camButton->setEnabled(false);
                    camButtons2[i].camButton->setStyleSheet("QPushButton{ background-color : lightgray; color : gray; }");
                }
            }
        }

    }
    if(updated)
        return 1;
    else
        return 0;
}

void MainWindow::pushCameraButton()
{
    int camindex,state1,state2;
    state1 = vplayer->getVideoState();
    state2 = vplayer2->getVideoState();
    mythread->exit();
    vplayer->pause();
    vplayer2->pause();
    QString tmpindex,tmpparent;
    QPushButton *tmpbtn = (QPushButton *)QObject::sender();
    tmpbtn->clearFocus();
    tmpindex = QObject::sender()->objectName().toLocal8Bit();
    camindex = (int)tmpindex.at(7).toLatin1();
    if(QObject::sender()->parent()->objectName()=="widget_3")
    {
        if(updateCameraButtons1(camindex-0x30))//if 1 need change cameras, else not
            setCamera1(camindex-0x30,state1);
        currentCam1Index = camindex-0x30;
    }
    if(QObject::sender()->parent()->objectName()=="widget_4")
    {
        if(updateCameraButtons2(camindex-0x30))//if 1 need change cameras, else not
            setCamera2(camindex-0x30,state2);
        currentCam2Index = camindex-0x30;
    }
}

void MainWindow::setCamera1(int index, int state)
{
    int tmp1=0,activeIndex=0;
    for(int i = 0; i < camButtons1.size(); i++)
    {
        if(camButtons1[i].active)
            activeIndex = i;
    }
    if(readyToPlay)
    {
        pageIndex = timeCells[ui->tableWidget->currentColumn()].currentPage;
        QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
        if(isVideo1Opened|isVideo2Opened)
        {
                int tmptime = vplayer->getCurrentTime()+dataMap[pageIndex].camTimeOffsets[lastIndex1-1]-dataMap[pageIndex].camTimeOffsets[index-1];
                while(tmp1<=activeIndex)
                {
                    Iter1.next();
                    tmp1++;
                }
                vplayer->openLocal(videoWorkingDir+"/"+Iter1.key());
                showCameraNameTimer->start(200);
                isVideo1Opened = true;
                vplayer->setPlayerTime(tmptime);
                setPause();
        }
        lastIndex1 =index;
        sound1IconState = vplayer->getAudioIconState();
        sound2IconState = vplayer2->getAudioIconState();
        if(vplayer->isSoundEnabled())
            qDebug() << "vplayer1 sound is enabled";
        else
            qDebug() << "vplayer1 sound is disabled";

        if((sound1IconState!=0)&(sound2IconState!=0))
        {
            if(sound1IconState==sound2IconState)
            {
                if(sound1IconState!=1)
                {
                    setSoundIconState(1,2);
                    setSoundIconState(2,1);
                }
            }
        }
        updateSoundMode();
    }
}

void MainWindow::setCamera2(int index, int state)
{
    int tmp2=0,activeIndex=0;
    for(int i = 0; i < camButtons2.size(); i++)
    {
        if(camButtons2[i].active)
            activeIndex = i;
    }
    if(readyToPlay)
    {
        pageIndex = timeCells[ui->tableWidget->currentColumn()].currentPage;
        QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);
        if(isVideo1Opened|isVideo2Opened)
        {

            int tmptime = vplayer2->getCurrentTime()+dataMap[pageIndex].camTimeOffsets[lastIndex2-1]-dataMap[pageIndex].camTimeOffsets[index-1];//!!
            while(tmp2<=activeIndex)
                {
                    Iter2.next();
                    tmp2++;
                }
            vplayer2->openLocal(videoWorkingDir+"/"+Iter2.key());
            showCameraNameTimer->start(200);
            isVideo2Opened = true;
            vplayer2->setPlayerTime(tmptime);
            setPause();
            sound1IconState = vplayer->getAudioIconState();
            sound2IconState = vplayer2->getAudioIconState();
            if(vplayer2->isSoundEnabled())
                qDebug() << "vplayer2 sound is enabled";
            else
                qDebug() << "vplayer2 sound is disabled";
                if((sound1IconState!=0)&(sound2IconState!=0))
                {
                    if(sound1IconState==sound2IconState)
                    {
                        if(sound1IconState!=1)
                        {
                            setSoundIconState(2,2);
                            setSoundIconState(1,1);
                        }
                    }
                }
                updateSoundMode();
        }
        lastIndex2 = index;
    }
}


int MainWindow::readTimeEdges(time_t *beginTime, time_t *endTime/*, unsigned char *beginTimeFract, unsigned char *endTimeFract*/)
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
            int recPosition=log->logDataPointer;
            int recPositionCompareVal = recPosition;
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
    ui->progressBar->setVisible(true);
    correctFramePosition();
    ui->mainToolBar->setEnabled(false);
    ui->progressBar->setValue(0);
    listOfLogs->clear();
    QString pathToFileDir = logWorkingDir;
    QDir filesDir(pathToFileDir);
    if(!filesDir.exists())
        return 1;
    filesDir.setSorting(QDir::Time);
    QStringList list;
    int algCounter = 0;
    list = filesDir.entryList(QDir::Files,QDir::Type);
    ui->progressBar->setMaximum(list.size()-1);
    for(int i = 0; i<list.size() ; i++)
    {
        if(list.at(i).indexOf(".alg")!=-1)
        {
            algCounter++;
            listOfLogs->append(list.at(i));
        }
        ui->progressBar->setValue(i);
    }
    ui->progressBar->setVisible(false);
    correctFramePosition();
    ui->mainToolBar->setEnabled(true);
    return 0;
}

int MainWindow::openVideoFilesFolder(QStringList *listOfVideos)
{
    listOfVideos->clear();
    ui->mainToolBar->setEnabled(false);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setVisible(true);
    correctFramePosition();
    ui->progressBar->setValue(0);
    QString pathToFileDir = videoWorkingDir;
    QDir filesDir(pathToFileDir);
    if(!filesDir.exists())
        return 1;
    filesDir.setSorting(QDir::Time|QDir::Reversed);
    ui->progressBar->setMaximum(filesDir.entryList(QDir::Files).size()-1);
    for(int i = 0; i < filesDir.entryList(QDir::Files).size(); i++)
    {
        if(filesDir.entryList(QDir::Files).at(i).indexOf(".mkv")!=-1)
            listOfVideos->append(filesDir.entryList(QDir::Files).at(i));
        ui->progressBar->setValue(i);
        ui->progressBar->update();
    }
    qSort(listOfVideos->begin(),listOfVideos->end());
    for (int i =0; i < listOfVideos->size(); i++)
    ui->progressBar->setVisible(false);
    correctFramePosition();
    ui->mainToolBar->setEnabled(true);
    return 0;
}

int MainWindow::openLogFile(QString filename)
{
    QString selectedLogFilePath;
    selectedLogFilePath = logWorkingDir+"/"+filename;//logList.at(logIndex);
    int logfilesize = log->selectLogFile(selectedLogFilePath);
    checkFileHeaderCRC(selectedLogFilePath);
    tickCounter = 1;
    getTimeTimer->start(1);
    videoOnly = false;
    return 0;
}


bool MainWindow::checkFileHeaderCRC(QString filename)
{
    log->selectLogFile(filename);
    int maxSegCount = log->getSegmentsCount();
    log->checkSegmentsExistance();
    log->readFileHeader();
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

int MainWindow::readHeadTableData()//here we read head table - its header and its data
{
    for(int i = 0; i < log->segIDs.size(); i++)
    {

    }
    if(log->fileHeader.fileSize != log->tmpFile.size())//check file size
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Файл журнала регистратора поврежден. Неверный размер логфайла.");
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
        newMessage.setText("В файле журнала регистратора не найден сегмент локализации."+tmp2.toString());
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
                log->readSegment(buffArr1, log->segmentHeader.size );
                interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
                interpreter->setInterpretationTable(buffArr1,interpreter->interpreterRecordsCount);
                int index=0;
                for(int i =0; i <interpreter->interpreterRecordsCount; i++)
                {
                    if(interpreter->TInterpItemArray[i].level!=0)
                    {
                        int col1 = 0;
                        parname = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);//QTextCodec::codecForLocale()->toUnicode(interpreter->TInterpItemArray[i].name);
                        QLabel *labe1 = new QLabel(parname);
                        labe1->setAlignment(Qt::AlignCenter);
                        ui->tableWidget_2->setCellWidget(index/2,col1+(index%2)*2,labe1);
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
                      newMessage.setText("В файле журнала регистратора не найден сегмент саммари по машине. " + tmpVal.toString());
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
                                                QVariant tmpVal = tmpDbl;
                                                tmpField = tmpVal.toByteArray();
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
                                                int tmpInt;
                                                tmpInt = interpreter->fieldInt(&log->record[recIndex]);
                                                QVariant tmpVal = tmpInt;
                                                tmpField = tmpVal.toByteArray();
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
                                else
                                {
                                    int tmpInt;
                                    tmpInt = interpreter->fieldInt(&log->record[recIndex]);
                                    QVariant tmpVal = tmpInt;
                                    tmpField = tmpVal.toByteArray();
                                }
                            }
    }
    else
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
        newMessage.exec();
    }
    return tmpErr;
}

//actions buttons etc
void MainWindow::on_action_triggered()
{
    logList.clear();
    if(!isFolderOpened)
    {
       selectLogFolder();
       selectVideoFolder();
    }
    else
    {

    }
    openLogFilesFolder(&logList);
    openVideoFilesFolder(&videoList);
     qSort(logList.begin(),logList.end());
     for(int i = 0; i < logList.size(); i++)
     {

     }
    ui->pushButton->click();

}

void MainWindow::createCellVector()
{
    int length = dataMap.size();
    if(dataMap[dataMap.size()-1].timeEdge2 ==dataMap[dataMap.size()-1].timeEdge1)
    {
        int tmpMax=0;
        for(int a = 0; a < dataMap[dataMap.size()-1].videoTimeEdges.size();a++)
        {
            int tmpTime = dataMap[dataMap.size()-1].videoTimeEdges[a]+dataMap[dataMap.size()-1].camTimeOffsets[a]/1000;
            if(tmpMax < tmpTime)
                tmpMax = tmpTime;
        }
        dataMap[dataMap.size()-1].timeEdge2+=tmpMax;
    }
    int totalWidth = dataMap[dataMap.size()-1].timeEdge2 - dataMap[0].timeEdge1;\
    if(length!=0)
    {
        int k = 0,tmpGreenLength=0, tmpGrayLength=0, tmpWhiteLength=0,tmpTimeCell=0;
        tableCell tc;
        for(int i = 0; i < length; i++)
        {
            int tmpMax = 0;
            tmpGrayLength=0;
            tmpGreenLength=0;
            tmpWhiteLength=0;
            tmpTimeCell=0;
            tc.beginTime=0;
            tc.cellType=0;
            tc.colWidth=0;
            tc.currentPage=0;
            tc.donor=0;
            tc.endTime=0;
            tc.relativeWidth=0;
            for(int a = 0; a < dataMap[i].videoTimeEdges.size();a++)
            {
                int tmpTime = dataMap[i].videoTimeEdges[a]+dataMap[i].camTimeOffsets[a]/1000;
                if(tmpMax < tmpTime)
                    tmpMax = tmpTime;
            }
            tmpGreenLength = tmpMax;
            tmpGrayLength = dataMap[i].logTimeEdge2-dataMap[i].timeEdge1;
            if(tmpGrayLength<0)
                tmpGrayLength = 0;
            tmpTimeCell = dataMap[i].timeEdge2-dataMap[i].timeEdge1;
            if(tmpGreenLength>tmpGrayLength)
            {
                tmpGrayLength= 0;
                if(tmpTimeCell>tmpGreenLength)
                   tmpWhiteLength  =  tmpTimeCell - tmpGreenLength;
            }
            else
            {
               tmpGrayLength = tmpGrayLength-tmpGreenLength;
               if(tmpTimeCell>(tmpGreenLength+tmpGrayLength))
                   tmpWhiteLength = tmpTimeCell - (tmpGreenLength+tmpGrayLength);
               else
                   tmpWhiteLength = 0;
            }
            bool redFlag = true;
            for(int b = 0; b < dataMap[i].camTimeOffsets.size(); b++)
            {
                if((dataMap[i].camTimeOffsets.at(b)>0)&(dataMap[i].videoTimeEdges.at(b)>0))
                    redFlag = false;
                else if((dataMap[i].camTimeOffsets.at(b)==0)&(dataMap[i].videoTimeEdges.at(b)==0))
                    redFlag = false;
                else
                {
                    redFlag = true;
                    b = dataMap[i].camTimeOffsets.size();
                }

            }
            if(tmpGreenLength>0)
            {
                tc.donor = 0;
                tc.beginTime = dataMap[i].timeEdge1;
                tc.endTime = tc.beginTime+tmpGreenLength;
                float tmplength = (float)tmpGreenLength/totalWidth;
                tc.colWidth = ui->tableWidget->width()*(tmplength);
                if(!redFlag)
                    tc.cellType = 0;
                else
                    tc.cellType = 3;
                tc.relativeWidth = tmplength;
                tc.currentPage = i;
                timeCells.append(tc);
                k++;

            }
            if(tmpGrayLength>1)
            {
                tc.donor = 0;
                tc.beginTime = dataMap[i].timeEdge1+tmpGreenLength;
                tc.endTime = tc.beginTime+tmpGrayLength;
                float tmplength = (float)tmpGrayLength/totalWidth;
                tc.colWidth = ui->tableWidget->width()*(tmplength);
                if(!redFlag)
                    tc.cellType = 1;
                else
                    tc.cellType = 3;
                tc.relativeWidth = tmplength;
                tc.currentPage = i;
                if(redFlag)
                    timeCells.append(tc);
                k++;

            }
            if(tmpWhiteLength>1)
            {
                tc.donor = 0;
                tc.beginTime = dataMap[i].timeEdge1+tmpGreenLength+tmpGrayLength;
                tc.endTime = tc.beginTime+tmpWhiteLength;
                float tmplength = (float)tmpWhiteLength/totalWidth;
                tc.colWidth = ui->tableWidget->width()*(tmplength);
                tc.cellType = 2;
                tc.relativeWidth = tmplength;
                tc.currentPage = i;
                timeCells.append(tc);
                k++;
            }
        }
    }
    int acceptorCounts=0,donorCounts=0;//acceptors and donors are used to make correct filling of timesegment table
    for(int a = 0; a < timeCells.size(); a++)
    {
        if((timeCells[a].colWidth<1)&(timeCells[a].cellType!=1))
            acceptorCounts++;
        else if(timeCells[a].colWidth>5)
        {
                donorCounts++;
        }
    }
    if(acceptorCounts)
    {
        for(int a = 0; a < timeCells.size(); a++)
        {
            if(acceptorCounts>0)
            {
                if(timeCells[a].colWidth < 1)
                {
                    timeCells[a].colWidth=1;
                    timeCells[a].donor = 2;
                    acceptorCounts--;
                }
            }
            if(donorCounts>0)
            {
                if(timeCells[a].colWidth>5)
                {
                    timeCells[a].colWidth = timeCells[a].colWidth-1;
                    timeCells[a].donor = 1;
                    donorCounts--;
                }
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{

    QVector <long> thMaxs(0);
    QVector <QString> thNames(0);
    QVector <int> seq(0);
    openLogFile(logList.at(0));
    if(timeSegment.isEmpty())
    {

    }
    if(createTimeSegment(&logList))
    {
        dataMap.clear();
        videoTimeGlobalIterator=0;
        createDataMap();
        for(int l = 0; l < dataMap.size(); l++)
        {
            QMapIterator <QString, bool> Iter(dataMap[l].videoVector);
            for(int a = 0; a< dataMap[l].camTimeOffsets.size();a++)
            {

            }
            for(int a = 0; a< dataMap[l].videoTimeEdges.size();a++)
            {

            }
            while(Iter.hasNext())
            {
                Iter.next();
            }
        }
        createCellVector();
        initColoredScale();
        setCameraButtonsToDefault();
        currentCam1Index = 1;
        currentCam2Index = 2;
        QDir dir;
        qint64 totalsize = 0;
        int videoCounter=0, logCounter = 0;
        dir.setPath(videoWorkingDir);
        QDirIterator iterator(dir.absolutePath(),QDirIterator::Subdirectories);
        while(iterator.hasNext())
        {
            iterator.next();
            if(iterator.fileInfo().isFile())
            {
                QString filename = iterator.fileName();
                if(filename.endsWith(".mkv"))
                    videoCounter++;
                if(filename.endsWith(".alg"))
                    logCounter++;
                QFile file(videoWorkingDir+"/"+  filename);
                totalsize+= file.size();
            }
        }
        QVariant tmpvc = videoCounter, tmpvl = logCounter;
        QDateTime begin = QDateTime::fromTime_t(timeCells[0].beginTime).toUTC(), end = QDateTime::fromTime_t(timeCells[timeCells.size()-1].endTime).toUTC();//QDateTime::fromTime_t(dataMap[0].timeEdge1), end = QDateTime::fromTime_t(dataMap[dataMap.size()-1].timeEdge2);
        ui->tableWidget_3->setItem(0,0, new QTableWidgetItem);
        ui->tableWidget_3->item(0,0)->setText(QString::number(totalsize/1048576,10));
        ui->tableWidget_3->setItem(1,0, new QTableWidgetItem);\
        qDebug() << "days to end" << begin.daysTo(end);
        qDebug() << QDateTime::fromTime_t(timeCells[timeCells.size()-1].beginTime).toUTC();
        qDebug() << QDateTime::fromTime_t(timeCells[timeCells.size()-1].endTime).toUTC();
        qDebug() << QDateTime::fromTime_t(dataMap[dataMap.size()-1].timeEdge1).toUTC();
        qDebug() << QDateTime::fromTime_t(dataMap[dataMap.size()-1].timeEdge2).toUTC();
        qDebug() << QDateTime::fromTime_t(dataMap[0].timeEdge1).toUTC();
        qDebug() << "and time" << QDateTime::fromTime_t(dataMap[dataMap.size()-1].timeEdge2 - dataMap[0].timeEdge1-86400*begin.daysTo(end)).toUTC();
        ui->tableWidget_3->item(1,0)->setText(QString::number(begin.daysTo(end),10)+" дн. "+QDateTime::fromTime_t(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime-86400*begin.daysTo(end)).toUTC().time().toString());
        ui->tableWidget_3->setItem(2,0, new QTableWidgetItem);
        ui->tableWidget_3->item(2,0)->setText(tmpvc.toString());
        ui->tableWidget_3->setItem(3,0, new QTableWidgetItem);
        ui->tableWidget_3->item(3,0)->setText(tmpvl.toString());
        openLogFile(logList.at(0));
        if(ui->horizontalSlider->maximum()!=0)
        {
            ui->horizontalSlider->setValue(0);
            ui->horizontalSlider->setMaximum(0);
            QTime tmp;
            tmp.setHMS(0,0,0);
            ui->timeEdit->setTime(tmp);
        }
        createFakeTimeScale(0,0);
        initThermoNames(&thNames,&seq);
        initSmallThermos(initThermoMaxs(&thMaxs),thNames,thMaxs,seq);
        ui->comboBox->removeItem(0);
        ui->comboBox_2->removeItem(0);
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(1);
        openVideoFile(videoList[0],videoList[1]);
        flowingOffset = 300;
        delayMs = (vplayer->getCurrentTime()+flowingOffset + camOffsets.at(currentCam1Index-1))/10;
        delayMs = (delayMs/10 + 2)*10;
        updateTime();
        dataParams *tmpDP = new dataParams;
        getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)delayMs/100,(int)((delayMs%100)*2.56),0);
        makeStructFromRecord(log->record,tmpDP);
        updateThermos(*tmpDP);
        flowingOffset = 0;
        ui->horizontalSlider->installEventFilter(this);
        setButtonsEnable(true);
    }
    else
    {
        createFakeTimeScale(0,0);
        ui->comboBox->removeItem(0);
        ui->comboBox_2->removeItem(0);
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(1);
        openVideoFile(videoList[0],videoList[1]);
        setButtonsEnable(true);
    }
    if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
    {
        if(vplayer->getVideoState()==3)
        {
            mythread->start();
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        }

    }
    else
    {
        mythread->start();
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    readyToPlay = true;
    sound1IconState = vplayer->getAudioIconState();
    sound2IconState = vplayer2->getAudioIconState();
    if((sound1IconState!=0)&(sound2IconState!=0))
    {
        if(sound1IconState==sound2IconState)
        {
            setSoundIconState(1,2);
            setSoundIconState(2,1);
        }
    }
    updateSoundMode();
}

void MainWindow::on_action_2_triggered()
{


}

int MainWindow::createDataMap()
{
    dataPage tmpPage;
    for(int i = 0; i < timeSegment.size()/2;i++)
    {
        tmpPage.camOffsetAmount=0;
        tmpPage.camTimeOffsets.clear();
        tmpPage.logName ="";
        tmpPage.logTimeEdge2=0;
        tmpPage.timeEdge1=0;
        tmpPage.timeEdge2=0;
        tmpPage.TimeFract1=0;
        tmpPage.TimeFract2=0;
        tmpPage.videoTimeEdges.clear();
        tmpPage.videoVector.clear();
        tmpPage.timeEdge1 = timeSegment.at(i*2);
        if(i<timeSegment.size()/2-1)
            tmpPage.timeEdge2 = timeSegment.at((i+1)*2);//timeSegment.at(i*2+1);
        else
            tmpPage.timeEdge2 = timeSegment.at(i*2+1);
        tmpPage.TimeFract1 = timeFracts.at(i*2);
        tmpPage.TimeFract2 = timeFracts.at(i*2+1);
        tmpPage.logName = logList.at(i);
        tmpPage.videoTimeEdges.clear();
        for(int a=0; a < offsetsCounter.at(i); a++)
        {
            tmpPage.videoTimeEdges.append(videoTimes.at(videoTimeGlobalIterator));
            videoTimeGlobalIterator++;
        }
        qDebug() << tmpPage.videoTimeEdges;
        if(i==timeSegment.size()/2-1)//check if latest time edge exists (if there is video) else set it equal to logEndTime
        {
            int tmpMaxVtime=0;
            for(int a=0; a < offsetsCounter.at(i); a++)
            {
                if(tmpMaxVtime<=tmpPage.videoTimeEdges.at(a))
                    tmpMaxVtime = tmpPage.videoTimeEdges.at(a);
            }
            if(tmpMaxVtime < (logEndTimes.at(i) - tmpPage.timeEdge1))
                tmpPage.timeEdge2 = logEndTimes.at(i);
        }
        tmpPage.logTimeEdge2 = logEndTimes.at(i);
        tmpPage.camOffsetAmount = offsetsCounter.at(i);
        tmpPage.videoVector.clear();
        tmpPage.camTimeOffsets.clear();
        for(int j = 0; j< ui->comboBox->count()-1; j++)
        {
            QFile tmpFile;
            tmpFile.setFileName(videoWorkingDir+"/"+videoList.at(i*10+j));
            bool tmpval = tmpFile.exists();
            tmpPage.camTimeOffsets.append(camOffsets.at(i*10+j));
            tmpPage.videoVector.insert(videoList.at(i*10+j),tmpval);
        }
        dataMap.append(tmpPage);
    }
    ui->horizontalSlider->setEnabled(true);
    ui->line->raise();
    timeSegment.clear();
    videoTimeGlobalIterator=0;
    return 0;
}

int MainWindow::openVideoFile(QString filename1, QString filename2)
{
    int result1=0,result2=0;
    QFile filetocheck;
    videoDelayms=0;
        playingFile1 = filename1;
        filetocheck.setFileName(videoWorkingDir+"/"+playingFile1);
        if(filetocheck.size()>10000)
        {
           result1 = vplayer->openLocal(videoWorkingDir+"/"+playingFile1);
           correctFramePosition();
           vplayer->setPlayerTime(maxCamOffset - dataMap[pageIndex].camTimeOffsets.at(currentCam1Index));
           isVideo1Opened = true;
         }
        playingFile2 = filename2;
        filetocheck.setFileName(videoWorkingDir+"/"+playingFile2);
        if(filetocheck.size()>10000)
        {
            result2 = vplayer2->openLocal(videoWorkingDir+"/"+playingFile2);
            correctFramePosition();
            vplayer2->setPlayerTime(maxCamOffset - dataMap[pageIndex].camTimeOffsets.at(currentCam2Index));
            isVideo2Opened = true;
        }
        timeSegmentIterator = videoList.indexOf(filename1)/(ui->comboBox->count()-1);
        updateSoundMode();
        setPause();
   return 0;
}
//void MainWindow::simpleDelayTimerTick()
//{
//    ////qDebug() << "index of simpleDelayTick changed";
//    if(!timer->isActive())
//        {
//            simpleDelayTimer->stop();
//            //vplayer->play();
//            //vplayer2->play();
//            timer->start(mainTimerInterval);
////            mythread->start();
//        }

//}

//void MainWindow::delayTimerTick()//unused yet
//{
//    videoDelayms++;
//    delayTimer->start(1);
//    if((isVideo1Opened)&(isVideo2Opened))
//    {
//        if((vplayer->getVideoState()==4)&(vplayer2->getVideoState()==4))
//        {
//            videoDelayms = 0;
//            delayTimer->stop();
//        }
//    }

//}

//void MainWindow::stopDelayTimer()
//{
////    delayTimer->stop();
////    ////////qDebug()() <<"delaytime" << videoDelayms;

////   disconnect(vplayer->_player,SIGNAL(playing()),this,SLOT(startDelayTimer()));
////   disconnect(vplayer2->_player,SIGNAL(playing()),this,SLOT(stopDelayTimer()));
//}

//void MainWindow::startDelayTimer()
//{

//}

//bool MainWindow::checkVideosSynchronized()
//{

//    vplayer->pause();
//    vplayer2->pause();
//    if((vplayer->getVideoState()==4)&(vplayer2->getVideoState()==4))
//    {
//        int tmpTime1 = vplayer->getCurrentTime();
//        int tmpTime2 = vplayer2->getCurrentTime();
//        if(tmpTime1>tmpTime2)
//        {
//            vplayer2->setPlayerTime(tmpTime1);
//            vplayer2->pause();
//            while(vplayer2->getVideoState()!=4){}
//        }
//        else if(tmpTime2>=tmpTime1)
//        {
//            vplayer->setPlayerTime(tmpTime2);
//            vplayer->pause();
//            while(vplayer->getVideoState()!=4){}
//        }
//        return true;
//    }
//    else
//    return false;

//}

//int MainWindow::changeVideo1(QString filename)
//{
//    int result1=0;
//   if(currentCam1Index!=0)
//   {
//        vplayer->stop();
//        correctFramePosition();
//        vplayer2->pause();
//        playingFile1 = filename;
//        QFile filetocheck;
//        filetocheck.setFileName(videoWorkingDir+"/"+playingFile1);
//        if(filetocheck.size()>10000)
//        {

//        }
//        else result1 = 2;
//   }
//   return result1;
//}

//int MainWindow::changeVideo2(QString filename)
//{
//    int result2=0;
//   if(currentCam2Index!=0)
//   {
//        vplayer2->stop();
//        correctFramePosition();
//        vplayer->pause();
//        playingFile2 = filename;
//        QFile filetocheck;
//        filetocheck.setFileName(videoWorkingDir+"/"+playingFile2);
//        if(filetocheck.size()>10000)
//        {

//        }
//        else result2 = 2;
//   }
//   return result2;
//}

//bool MainWindow::synchronizePlayersStates()
//{
//    if(playersStatesSynchronized)
//        return true;
//    else
//    {
//        stateTimerTickCounter = 0;
//        if((vplayer->getVideoState()==3)&(vplayer2->getVideoState()==6))
//        {
////            vplayer->stop();
////            waitEndStateTimer->start(1);
//        }
//        if((vplayer->getVideoState()==6)&(vplayer2->getVideoState()==3))
//        {
////            vplayer2->stop();
////            waitEndStateTimer->start(1);
//        }
//        if((vplayer->getVideoState()==4)&(vplayer2->getVideoState()==3))
//        {
//            vplayer2->pause();
//        }
//        else if((vplayer->getVideoState()==3)&(vplayer2->getVideoState()==4))
//        {
//            //vplayer2->play();
//        }
//        stateTimer->start(1);
//        while((stateTimerTickCounter<100)|(!playersStatesSynchronized)){}
//        if(!playersStatesSynchronized)
//            return false;
//        else
//            return true;
//    }

//}

//void MainWindow::video1Ended()
//{

//    pageIndex++;
//    int index1=0,index2=0;
//    player1Opening = false;
//    player1Paused = false;
//    player1Playing = false;
//    if(vplayer2->getVideoState()==6)
//    {
//        timer->stop();
//        mythread->exit();

//    }
//    for(int i = 0; i < videoList.size(); i++)
//    {
//        if(videoList[i]==playingFile1)
//            index1=i;
//        if(videoList[i]==playingFile2)
//            index2=i;
//    }
//    if(vplayer->getVideoState()==vplayer2->getVideoState())
//    {
//    if((index1+ui->comboBox->count()-1<videoList.size())&(index2+ui->comboBox->count()-1<videoList.size()))
//        {
//            openVideoFile(videoList[index1+ui->comboBox->count()-1],videoList[index2+ui->comboBox->count()-1]);
//        }
//        playersStatesSynchronized = true;
//    }
//    if(vplayer->getVideoState()==3)
//        mythread->start();
//}

//void MainWindow::video2Ended()
//{
//    int index1=0,index2=0;
//    player2Opening = false;
//    player2Paused = false;
//    player2Playing = false;
////    isVideo2Opened = false;
//    if(vplayer->getVideoState()==6)
//    {
//        timer->stop();
////        mythread->exit();
//        //////qDebug() << ui->horizontalSlider->value();
//    }
//    ////////qDebug()() << "current player 2 state is" <<vplayer2->getVideoState();
//    for(int i = 0; i < videoList.size(); i++)
//    {
//        if(videoList[i]==playingFile1)
//            index1=i;
//        if(videoList[i]==playingFile2)
//            index2=i;

//    }
//    if(vplayer->getVideoState()==vplayer2->getVideoState())
//    {
//        if((index1+ui->comboBox->count()-1<videoList.size())&(index2+ui->comboBox->count()-1<videoList.size()))
//            {
//                openVideoFile(videoList[index1+ui->comboBox->count()-1],videoList[index2+ui->comboBox->count()-1]);
//            }
//        playersStatesSynchronized = true;
//    }
//}

//void MainWindow::saveVideoStats()
//{
//    savedVideoStats.video1Status = vplayer->getVideoState();
//    savedVideoStats.video2Status = vplayer2->getVideoState();
//    savedVideoStats.mythreadStatus = mythread->isRunning();
//    savedVideoStats.dataUpdated = true;
//}

//void MainWindow::loadVideoStats()
//{
//    if(savedVideoStats.dataUpdated)
//    {
//        savedVideoStats.dataUpdated = false;
//        switch(savedVideoStats.video1Status)
//        {
//            case 3:
//            {

//            }
//        }

//    }
//}

void MainWindow::on_playButton_clicked()
{
    isPaused = !isPaused;
    setPause();
    if(isPaused)
    {
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    else
    {
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
}

void MainWindow::on_stopButton_clicked()
{
    terminateAll();
}

void MainWindow::setButtonsEnable(bool tf)
{
    ui->playButton->setEnabled(tf);
    ui->stopButton->setEnabled(tf);
    ui->previousTimeSegment->setEnabled(tf);
    ui->nextTimeSegment->setEnabled(tf);
    ui->frameBackwardButton->setEnabled(tf);
    ui->nextFrameButton->setEnabled(tf);
    ui->pushButton->setEnabled(!tf);
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
}

void MainWindow::on_timeEdit_editingFinished()//unused but who knows may be some time it will be usefull
{
      QTime zerotime;
      zerotime.setHMS(0,0,0,0);
      vplayer->moveToTime(zerotime.secsTo(ui->timeEdit->time())*1000);

}


void MainWindow::updateCamWidgetsState()
{
    if(timeCells[ui->tableWidget->currentColumn()].cellType!=0)
    {
        ui->widget_3->setVisible(false);
        ui->widget_4->setVisible(false);
    }
    else
    {
        ui->widget_3->setVisible(true);
        ui->widget_4->setVisible(true);
    }

}

//void MainWindow::on_nextTimeSegment_clicked()
//{
//    clearParTable();
//    if(ui->tableWidget->currentColumn()<ui->tableWidget->columnCount()-1)
//    {
//        moveToAnotherTimeSegment(ui->tableWidget->currentColumn()+1);
//        ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn()+1);
//        updateCamWidgetsState();
//    }
//    else
//    {
//        moveToAnotherTimeSegment(ui->tableWidget->currentColumn());
//        ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn());
//        updateCamWidgetsState();

//    }
//correctFramePosition();
//}

/*unused*/
//void MainWindow::setVideoTime()//its my handmade slot
//{
//    int time =0;
//    int ms = time%1000;
//    time = time/1000;
//    QTime outtime;
//    int h = time/3600;
//    int m = (time/60)%60;
//    int s = time%60;
//    int tmpDelayMs=0;
//    int currentVideoTime = 0;
//    int frameLength = 5;//50ms
//    ui->timeEdit->setTime(outtime);
//    if(!videoOnly)
//    {
//            time =  vplayer->getCurrentTime();
//            outtime.setHMS(h,m,s,ms);
//            currentVideoTime =(vplayer->getCurrentTime() + camOffsets.at(currentCam1Index-1))/10;
//            int mainTime=0;
//            if(vplayer->getVideoLength()>vplayer2->getVideoLength())
//                mainTime = vplayer2->getCurrentTime();
//            else
//                mainTime = vplayer->getCurrentTime();
//                tmpDelayMs = (mainTime + flowingOffset+ camOffsets.at(currentCam1Index-1))/10;//(delayMs*10 + vplayer->getCurrentTime() + camOffsets.at(currentCam1Index-1))/20;//true time is a sum of maxcamoffset,
//            logVideoDelta += delayMs - (vplayer->getCurrentTime() + camOffsets.at(currentCam1Index-1))/10;
//                delayMs = tmpDelayMs;
//            logVideoDeltaCounter++;
//            tickCounter = delayMs%50;
//            lastDelay = delayMs;
//    }
//    else
//    {
//        delayMs = (vplayer->getCurrentTime());//(delayMs*10 + vplayer->getCurrentTime() + camOffsets.at(currentCam1Index-1))/20;//true time is a sum of maxcamoffset,
//    }
//    if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
//    {
//        if(vplayer->getVideoState()==3)
//        {
//            if(mythread->isFinished())
//            {
//                mythread->start();
//                ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
//            }
//        }
//    }
//    else
//    {
//        if(mythread->isFinished())
//        {
//            mythread->start();
//            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
//        }
//    }
//}



//void MainWindow::on_previousTimeSegment_clicked()
//{
//    if(ui->tableWidget->currentColumn()>0)
//    {
//        moveToAnotherTimeSegment(ui->tableWidget->currentColumn(),vplayer->getVideoState(),vplayer2->getVideoState());
//        ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn()-1);
//        updateCamWidgetsState();
//        setPause();
//    }
//    else
//    {
//         ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn());
//         updateCamWidgetsState();
//    }
//    correctFramePosition();
//}

//void MainWindow::on_horizontalSlider_valueChanged(int value)
//{
//    delayMs = value*100;
//}

void MainWindow::moveToNextTimeFrame()
{
    ui->nextTimeSegment->click();
}

void MainWindow::terminateAll()
{
        logWorkingDir = "";
        videoWorkingDir = "";
        ui->line->setVisible(false);
        ui->line_2->setVisible(false);
        ui->line_3->setVisible(false);
        ui->line_4->setVisible(false);
        ui->ScaleWidget->setVisible(false);
        ui->horizontalSlider->setEnabled(false);
        vplayer->pause();
        vplayer2->pause();
        if(mythread->isRunning())
            mythread->exit();
        isPaused = false;
        vplayer->stop();
        vplayer2->stop();
        delayMs = 0;
        pauseDelayTimer->stop();
        updateTime();
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(0);
        ui->tableWidget_2->clear();
        for(int j = 0; j< ui->tableWidget_3->rowCount(); j++)
            ui->tableWidget_3->item(j,0)->setText(" ");
        if(!videoOnly)
        {
            dataParams *tmpDP = new dataParams;
            getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)delayMs/100,(int)((delayMs%100)*2.56),0);
            makeStructFromRecord(log->record,tmpDP);
            updateThermos(*tmpDP);
        }
        QTime tmp;
        tmp.setHMS(0,0,0);
        ui->timeEdit->setTime(tmp);
        ui->horizontalSlider->setValue(0);
        isFolderOpened = false;
        accepted = false;
        ui->comboBox->blockSignals(true);
        ui->comboBox_2->blockSignals(true);
        ui->comboBox->addItem("Нет");
        ui->comboBox_2->addItem("Нет");
        ui->comboBox->blockSignals(false);
        ui->comboBox_2->blockSignals(false);
        videoButton->setEnabled(true);
        setButtonsEnable(false);
        dataMap.clear();
        timeCells.clear();
        videoList.clear();
        for(int a = 0 ; a< ui->tableWidget->columnCount(); a++)
            ui->tableWidget->removeColumn(0);
        ui->tableWidget->clear();
        QwtScaleDraw *resetScale = new QwtScaleDraw;
        resetScale->setLabelAlignment(Qt::AlignRight);
        ui->ScaleWidget->setScaleDraw(resetScale);
        ui->ScaleWidget->setContentsMargins(0,0,0,0);//leveling scale labels alignment balance
        logList.clear();
        camOffsets.clear();
        logEndTimes.clear();
        pageIndex = 0;
        ui->horizontalLayout_2->addWidget(ui->screen1SoundButton);
        ui->horizontalLayout_3->addWidget(ui->screen2SoundButton);
        for(int i =0; i < ui->gridLayout_2->count(); i++)
        {
                QLayoutItem* item;
                while((item = ui->gridLayout_2->takeAt(0))!=NULL)
                {
                    delete item->widget();
                    delete item;
                }

        }
        for(int i =1; i < camButtonsLayout1->count(); i++)
        {
                QLayoutItem* item;
                while((item = camButtonsLayout1->takeAt(0))!=NULL)
                {
                    delete item->widget();
                    delete item;
                }

        }
        for(int i =1; i < camButtonsLayout2->count(); i++)
        {
            qDebug() << "cambuttons count" << camButtonsLayout2->count();
                QLayoutItem* item;
                while((item = camButtonsLayout2->takeAt(0))!=NULL)
                {
                    delete item->widget();
                    delete item;
                }

        }

        thermoVals.clear();
        parameterBar.clear();
        checkBoxes.clear();
        ui->screen1SoundButton->setVisible(false);
        ui->screen2SoundButton->setVisible(false);
        camButtons1.clear();
        camButtons2.clear();
}

void MainWindow::on_action_4_triggered()
{

    if(mythread->isRunning())
        ui->playButton->click();
        selectLogFolder();
        if(LogFileError==2)
        {

        }
        selectVideoFolder();
    this->setWindowTitle(logWorkingDir);
    if(logWorkingDir!="")
        ui->pushButton->click();
    if(threadTimer->isActive())
    {
        //threadtimer is unused still
    }

}


//void MainWindow::on_comboBox_2_currentIndexChanged(int index)//unused as the combobox
//{
//    int tmp1=0,tmp2=0;
//    if(readyToPlay)
//    {
//        pageIndex = timeCells[ui->tableWidget->currentColumn()].currentPage;
//        QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);
//        if(index==currentCam1Index)
//        {
//            if(index==ui->comboBox->count()-1)
//                ui->comboBox_2->setCurrentIndex(index-1);
//            else
//                ui->comboBox_2->setCurrentIndex(index+1);
//        }
//        if(isVideo1Opened|isVideo2Opened)
//        {

//            int tmptime = vplayer2->getCurrentTime()+camOffsets.at(lastIndex1-1)-camOffsets.at(index-1);//!!
//                 while(tmp2<currentCam2Index)
//                {
//                    Iter2.next();
//                    tmp2++;
//                }
//                if(vplayer->getVideoState()==4)
//                    vplayer->togglePause();
//            vplayer2->openLocal(videoWorkingDir+"/"+Iter2.key());
//            showCameraNameTimer->start(200);
//            isVideo2Opened = true;
//            vplayer2->setPlayerTime(tmptime);
//            if(mythread->isRunning())
//                mythread->exit();
//            if(mythread->isRunning())
//                mythread->exit();
//                sound1IconState = vplayer->getAudioIconState();
//                sound2IconState = vplayer2->getAudioIconState();
//                if((sound1IconState!=0)&(sound2IconState!=0))
//                {
//                    if(sound1IconState==sound2IconState)
//                    {
//                        if(sound1IconState!=1)
//                        {
//                            setSoundIconState(2,2);
//                            setSoundIconState(1,1);
//                        }
//                    }
//                }
//                updateSoundMode();
//        }
//        lastIndex2 = index;
//    }
//}


//int MainWindow::getBeforeIndex(int videoIndex)
//{
//    if(videoIndex==0)
//        return 1;
//    if(videoIndex==1)
//        return 2;
//    if(videoIndex==2)
//        return 3;
//    if(videoIndex==3)
//        return 4;
//    if(videoIndex==4)
//        return 5;
//    if(videoIndex==5)
//        return 6;
//    if(videoIndex==6)
//        return 7;
//    if(videoIndex==7)
//        return 8;
//    if(videoIndex==8)
//        return 9;
//    if(videoIndex==9)
//        return 10;
//    else return 0;
//}

//void MainWindow::on_comboBox_currentIndexChanged(int index)//unused
//{
//    int tmp1=0,tmp2=0;
//    if(readyToPlay)
//    {
//        pageIndex = timeCells[ui->tableWidget->currentColumn()].currentPage;
//        QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
//        if(index==currentCam2Index)
//        {
//            if(index==ui->comboBox->count()-1)
//                ui->comboBox->setCurrentIndex(index-1);
//            else
//                ui->comboBox->setCurrentIndex(index+1);
//        }
//        if(isVideo1Opened|isVideo2Opened)
//        {
//                int tmptime = vplayer->getCurrentTime()+camOffsets.at(lastIndex1-1)-camOffsets.at(index-1);
//                while(tmp1<currentCam1Index)
//                {
//                    Iter1.next();
//                    tmp1++;
//                }
//                if(vplayer2->getVideoState()==4)
//                    vplayer2->togglePause();
//                vplayer->openLocal(videoWorkingDir+"/"+Iter1.key());
//                showCameraNameTimer->start(200);
//                isVideo1Opened = true;
//                vplayer->setPlayerTime(tmptime);
//                if(mythread->isRunning())
//                    mythread->exit();
//        }
//        lastIndex1 =index;
//        sound1IconState = vplayer->getAudioIconState();
//        sound2IconState = vplayer2->getAudioIconState();
//        if((sound1IconState!=0)&(sound2IconState!=0))
//        {
//            if(sound1IconState==sound2IconState)
//            {
//                if(sound1IconState!=1)
//                {
//                    setSoundIconState(1,2);
//                    setSoundIconState(2,1);
//                }
//            }
//        }
//        updateSoundMode();
//    }
//}

//void MainWindow::on_horizontalSlider_sliderMoved(int position)
//{

//}

//void MainWindow::on_frameBackwardButton_clicked()//unused
//{
//    if(tickCounter<=0)
//        tickCounter = 20;
//    tickCounter--;
//    tickCounter--;
//    updateTime();
//}

void MainWindow::prepareVideoMarque()
{
    int activeIndex1=0,activeIndex2=0;
    qDebug() << "show camera names!!!";
    QString str="    Камера ";
    for(int i = 0; i < camButtons1.size();i++)
    {
        if(camButtons1[i].active)
            activeIndex1=i;
        if(camButtons2[i].active)
            activeIndex2=i;

    }
    str.append(QString::number(activeIndex1+1,10));
    QString soundstr = "\nЗвук ";
    if(sound1IconState==0)
        soundstr.append("отсутствует");
    if(sound1IconState==1)
        soundstr.append("выключен");
    if(sound1IconState==2)
        soundstr.append("включён");
    str.append(soundstr);
    vplayer->showText(str,2000,50,2000);
    str="    Камера ";
    str.append(QString::number(activeIndex2+1,10));
    soundstr = "\nЗвук ";
    if(sound2IconState==0)
        soundstr.append("отсутствует");
    if(sound2IconState==1)
        soundstr.append("выключен");
    if(sound2IconState==2)
        soundstr.append("включён");
    str.append(soundstr);
    vplayer2->showText(str,2000,50,2000);
    tickCounter++;
    showCameraNameTimer->stop();
    updateTime();
}

void MainWindow::on_nextFrameButton_clicked()
{

}

//void MainWindow::on_spinBox_2_valueChanged(int arg1)
//{
//    currentWidget1Geometry.setY(widget1Y+arg1);
//    int X1, Y1, X2, Y2;
//    currentWidget1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
//    baseVideo1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
//    currentWidget1Geometry.setCoords(X1,Y1+arg1,X2,Y2+arg1);
//    ////////qDebug()() <<"Y changed" << currentWidget1Geometry;
//    vplayer->changeGeometry(currentWidget1Geometry);
//    ////////qDebug()() << vplayer->getVideoSize();
//}

void MainWindow::on_spinBox_valueChanged(int arg1)//since spinbox is unused it is not needed too
{

}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

}

//void MainWindow::on_horizontalSlider_sliderReleased()//unused
//{
//    isSliderPressed = false;
//    qDebug() << "slider event release";
//    if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
//    {

//    }
//}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    isSliderPressed = true;
}


int MainWindow::setPause()
{
    pauseDelayFinished = false;
    if(isPaused)
    {
        mythread->exit();
        if(timeCells[ui->tableWidget->currentColumn()].cellType==0)//||(timeCells[ui->tableWidget->currentColumn()].cellType==3))
        {
            vplayer->pause();
            vplayer2->pause();
            while(vplayer->getVideoState()!=4)
                vplayer->pause();
            while(vplayer2->getVideoState()!=4)
                vplayer2->pause();
            pauseDelayTimer->start(250);
            if(pauseDelayFinished)
            {
                vplayer->pause();
                vplayer2->pause();
            }
        }
        else
        {
            mythread->exit();
            qDebug() << "hereherehere";
        }

    }
    else
    {
        mythread->start();
        if(timeCells[ui->tableWidget->currentColumn()].cellType==0)//||(timeCells[ui->tableWidget->currentColumn()].cellType==3))
        {
            vplayer->play();
            vplayer2->play();
            while(vplayer->getVideoState()!=3)
                vplayer->play();
            while(vplayer2->getVideoState()!=3)
                vplayer2->play();
            pauseDelayTimer->start(250);
            if(pauseDelayFinished)
            {
                vplayer->play();
                vplayer2->play();
            }
        }
        else
        {
            qDebug() << "herehere"<<mythread->isRunning();
            qDebug() << threadTimer->isActive();
            if(mythread->isRunning()==threadTimer->isActive())
            {
                mythread->exit();
                mythread->start();
            }
            qDebug() << "herehere"<<mythread->isRunning();
            qDebug() << threadTimer->isActive();
        }

    }
    pauseDelayTimer->stop();
    return 0;
}
int MainWindow::setPlay()
{
    if(mythread->isFinished())
    {
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        qDebug() << "started from setplay";
        mythread->start();
        if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
        {
            vplayer->play();
            vplayer2->play();
        }
    }
    return 0;
}

/*getting how many miliseconds are needed to set to move cursor to chosen time */
void MainWindow::getDelayMsToSet(int pos,int totalTime)
{
    float tmpPos = 0;
    int excessTime = 0,state1=0,state2=0;
    bool lastCellFlag = false;
    float realLength = 0;
    float totallength =0,littlelength = 0;
    state1 = vplayer->getVideoState();
    state2 = vplayer2->getVideoState();
    if(state1==5&state2==5)
    {
        if(mythread->isRunning())
        {
            state1 = 3;
            state2 = 3;
        }
        else
        {
            state1= 4;
            state2 = 4;
        }
    }
    for(int i = 0; i < timeCells.count(); i++)
    {
        totallength+=(float)((ui->tableWidget->width())*timeCells[i].relativeWidth);
        littlelength+=timeCells[i].relativeWidth;
        realLength+=ui->tableWidget->columnWidth(i);
    }
    for(int i =0; i <= ui->tableWidget->columnCount(); i++)
    {
        if( i ==  ui->tableWidget->columnCount())
        {
            tmpPos = (((float)(timeCells[i-1].endTime-timeCells[0].beginTime)/totalTime))*realLength/*ui->tableWidget->width()*/;
            lastCellFlag = true;
        }
        else
        {
            tmpPos = (((float)(timeCells[i].beginTime-timeCells[0].beginTime)/totalTime))*realLength/*ui->tableWidget->width()*/;

        }
        if(pos>=tmpPos)
        {

        }
        else
        {
            if(i>=0)//freeze at selected i this position
            {
                if(i==0)
                {

                }
                else
                {
                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i-1))/ui->tableWidget->width()))*totalTime;
                    if(ui->tableWidget->currentColumn()!=i-1)
                    {
                        moveToAnotherTimeSegment(i-1,state1,state2);
                        ui->tableWidget->setCurrentCell(0,i-1);
                        updateCamWidgetsState();
                        setPause();

                    }
                    correctCellSeekerPosition(pos-ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn()));
                    delayMsToSet = excessTime*100;

                    i = ui->tableWidget->columnCount();
                }
            }
            else if(i==0)
            {

                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i))/ui->tableWidget->width()))*totalTime;
                    if(ui->tableWidget->currentColumn()!=i)
                    {
                        moveToAnotherTimeSegment(i,state1,state2);
                        ui->tableWidget->setCurrentCell(0,i);
                        updateCamWidgetsState();
                        setPause();

                    }
                    delayMsToSet = excessTime*100;
                    i = ui->tableWidget->columnCount();
            }
        }
    }
}
void MainWindow::getCellAndTimeToMoveTo(int pos,int totalTime)//i guess this function is unused
{
    int tmpPos = 0;
    int excessTime = 0;
    bool lastCellFlag = false;
    for(int i =0; i <= ui->tableWidget->columnCount(); i++)
    {
        if( i ==  ui->tableWidget->columnCount())
        {
            tmpPos = (((float)(timeCells[i-1].endTime-timeCells[0].beginTime)/totalTime))*ui->tableWidget->width();
            lastCellFlag = true;    
        }
        else
            tmpPos = (((float)(timeCells[i].beginTime-timeCells[0].beginTime)/totalTime))*ui->tableWidget->width();
        if(pos>=tmpPos)
        {

        }
        else
        {

            if(i>=0)//freeze at selected i this position
            {
                if(i==0)
                {

                }
                else
                {
                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i-1))/ui->tableWidget->width()))*totalTime;
                    if(ui->tableWidget->currentColumn()!=i-1)
                    {
                         moveToAnotherTimeSegment(i-1,vplayer->getVideoState(),vplayer2->getVideoState());
                         ui->tableWidget->setCurrentCell(0,i-1);
                         updateCamWidgetsState();
                         setPause();
                    }
                    delayMsToSet = excessTime*100;
                    i = ui->tableWidget->columnCount();
                }
            }
            else if(i==0)
            {
                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i))/ui->tableWidget->width()))*totalTime;
                    if(ui->tableWidget->currentColumn()!=i)
                    {
                        moveToAnotherTimeSegment(i,vplayer->getVideoState(),vplayer2->getVideoState());
                        ui->tableWidget->setCurrentCell(0,i);
                        updateCamWidgetsState();
                        setPause();

                    }
                    delayMsToSet = excessTime*100;
                    i = ui->tableWidget->columnCount();
            }
        }
    }
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        QString parent_name = target->objectName();
        if((target== ui->line_5)||(target==  ui->tableWidget->viewport())||(parent_name=="ScaleWidget"))
        {
            ui->line_5->clearFocus();
            ui->tableWidget->viewport()->clearFocus();
            ui->ScaleWidget->clearFocus();
            ui->tableWidget->clearFocus();
            canMoveSeeker = false;
            seekerIsBusy = false;
        }
    }
    else if(event->type() == QEvent::MouseMove|QEvent::MouseButtonPress & target != 0x0)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *) event;
        QString parent_name = target->objectName();
        if(target== ui->line_5)
        {
            target->setParent(ui->ScaleWidget);
        }
        if((target==  ui->tableWidget->viewport())||(parent_name=="ScaleWidget")||(parent_name == "qt_scrollarea_viewport")||(target== ui->line_5))
        {
            seekerIsBusy = true;
            ui->tableWidget->viewport()->clearFocus();
            ui->tableWidget->clearFocus();
            int tmpval = ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();//-ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn());
            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
            getDelayMsToSet(tmpval,totalTime); //ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x(),totalTime);
            if((timeCells[ui->tableWidget->currentColumn()].cellType!=1))//&(timeCells[ui->tableWidget->currentColumn()].cellType!=2))
            {
                delayMs = delayMsToSet;\
                updateTime();
                delayMs = delayMsToSet;\
                updateTime();
                ui->horizontalSlider->setValue(delayMs/100);
                setSliderPosition();
            }
            return QObject::eventFilter(target, event);

        }
        else if(parent_name=="horizontalSlider")
        {
                double halfHandleWidth = 2.5; // Correct rounding
                int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
                int adaptedPosX = mouseEvent->x();
                if ( adaptedPosX < halfHandleWidth )
                        adaptedPosX = halfHandleWidth;
                if ( adaptedPosX > ui->horizontalSlider->width() - halfHandleWidth )
                        adaptedPosX = ui->horizontalSlider->width() - halfHandleWidth;
                double newWidth = (ui->horizontalSlider->width() - halfHandleWidth) - halfHandleWidth;
                double normalizedPosition = (adaptedPosX - halfHandleWidth)  / newWidth ;
                int newVal = ui->horizontalSlider->minimum() + ((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum()) * normalizedPosition);
                ui->horizontalSlider->setValue(newVal/*ui->horizontalSlider->minimum()+((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum())*mouseEvent->x())/ui->horizontalSlider->width()*/);
                newVal = ((float)ui->horizontalSlider->value()/totalTime)*ui->tableWidget->width();
                correctCellSeekerPosition(newVal);
                if((timeCells[ui->tableWidget->currentColumn()].cellType!=1))//&(timeCells[ui->tableWidget->currentColumn()].cellType!=2))
                {
                    updateTime();
                    setSliderPosition();
                    updateTime();
                }

            return QObject::eventFilter(target, event);
        }
    }
    else if(event->type() == QEvent::GrabMouse)
    {
        //qDebug() << "grab event";
    }
    else if(event->type() == QEvent::MouseButtonPress & target!=0x0)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *) event;
        QString parent_name = target->objectName();
        if(target== ui->line_5)
        {
            target->setParent(ui->ScaleWidget);
            return QObject::eventFilter(target, event);
        }
        if((parent_name=="ScaleWidget")||(target == ui->tableWidget->viewport())||(parent_name == "qt_scrollarea_viewport"))
        {
            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
            int tmpval = ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();
            /*getCellAndTimeToMoveTo*/getDelayMsToSet(tmpval,totalTime);
            delayMs = delayMsToSet;\
            updateTime();
            delayMs = delayMsToSet;\
            updateTime();
            ui->horizontalSlider->setValue(delayMs/100);
            setSliderPosition();
            return QObject::eventFilter(target, event);
        }
        if(parent_name=="horizontalSlider")
        {
            setHSliderPosOnButtonPress(mouseEvent);
            return QObject::eventFilter(target, event);
        }
    }
    else if((event->type()==QEvent::MouseMove)&target!=0x0)//&isSliderPressed
    {
        setSliderPosition();
        return QObject::eventFilter(target, event);
    }
    else if(target == 0x0)
    {
        //qDebug() << "blank2";
    }
    return QObject::eventFilter(target, event);//QMainWindow::eventFilter(target, event);
}

void MainWindow::setHSliderPosOnButtonPress(QMouseEvent *me)
{
    if(mythread->isRunning())
    {

    }
     double halfHandleWidth = 2.5; // Correct rounding
     int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
        int adaptedPosX = me->x();
        if ( adaptedPosX < halfHandleWidth )
                adaptedPosX = halfHandleWidth;
        if ( adaptedPosX > ui->horizontalSlider->width() - halfHandleWidth )
                adaptedPosX = ui->horizontalSlider->width() - halfHandleWidth;
        double newWidth = (ui->horizontalSlider->width() - halfHandleWidth) - halfHandleWidth;
        double normalizedPosition = (adaptedPosX - halfHandleWidth)  / newWidth ;
        int newVal = ui->horizontalSlider->minimum() + ((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum()) * normalizedPosition);
        ui->horizontalSlider->setValue(newVal/*ui->horizontalSlider->minimum()+((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum())*mouseEvent->x())/ui->horizontalSlider->width()*/);
        newVal = ((float)ui->horizontalSlider->value()/totalTime)*ui->tableWidget->width();
        correctCellSeekerPosition(newVal);
        updateTime();
        setSliderPosition();
        updateTime();
}

void MainWindow::setSliderPosition()
{
    int changedTime1=0,changedTime2=0;
    int oneVideoLength=0;
    if((vplayer->getVideoLength()!=-1)&(vplayer2->getVideoLength()!=-1))
    {
        if(vplayer->getVideoLength()<vplayer2->getVideoLength())
            oneVideoLength = vplayer->getVideoLength();
        else
            oneVideoLength = vplayer2->getVideoLength();
    }
    else
    {
            oneVideoLength = (dataMap[pageIndex].timeEdge2 - dataMap[pageIndex].timeEdge1)*1000;

    }
    changedTime1 = ui->horizontalSlider->value()*1000;/*((float)ui->horizontalSlider->value()/ui->horizontalSlider->maximum())*((float)oneVideoLength/(ui->horizontalSlider->maximum()))*(ui->horizontalSlider->value());*/
    if(changedTime1>vplayer->getVideoLength())
        changedTime1 = vplayer->getVideoLength();
    changedTime2 = ui->horizontalSlider->value()*1000;/*((float)ui->horizontalSlider->value()/ui->horizontalSlider->maximum())*((float)oneVideoLength/(ui->horizontalSlider->maximum()))*(ui->horizontalSlider->value());*/
    if(changedTime2>vplayer2->getVideoLength())
        changedTime2 = vplayer2->getVideoLength();
    if(timeCells[ui->tableWidget->currentColumn()].cellType==0)//if we're working with  0 celltype, changing video time
    {
        if((!videoOnly)|(offsetsAvailable))
        {
            vplayer->setPlayerTime(changedTime1 + maxCamOffset - camOffsets.at(currentCam1Index-1));
            vplayer2->setPlayerTime(changedTime2 + maxCamOffset - camOffsets.at(currentCam2Index-1));
            delayMs = (changedTime1 + camOffsets.at(currentCam1Index-1))/10;
        }
        else
        {
            vplayer->setPlayerTime(changedTime1);
            vplayer2->setPlayerTime(changedTime2);
            delayMs = changedTime1;// + camOffsets.at(currentCam1Index-1))/10;
        }
    }
    else
    {
        changedTime1 = ui->horizontalSlider->value()*100;
        delayMs = changedTime1;

    }
    updateTime();
}

void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{

}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{

}
void MainWindow::clearParTable()
{
    log->clearBuff();
    for(int i =0; i < checkBoxes.count(); i++)
        checkBoxes[i]->setChecked(false);
    for(int i = 0; i < thermoVals.count(); i++)
    {
        thermoVals[i]->setText(0);
        parameterBar[i]->setValue(0);
    }
    dataParams dp;
    makeStructFromRecord(log->record,&dp);
    updateThermos(dp);
}

void MainWindow::moveToAnotherTimeSegment(int column,int state1, int state2)
{
    bool nextpage = false;//,state1,state2;
    clearParTable();
    if((timeCells[column].cellType==0)|(timeCells[column].cellType==3))//|(timeCells[column].cellType==2))//||(timeCells[column].cellType==3))
        {
            if(pageIndex!=timeCells[column].currentPage)
            {
                nextpage = true;
            }
            else
            {
                if(timeCells[column].currentPage==timeCells.count()-1)
                {
                    nextpage=true;
                    vplayer->stop();
                    vplayer2->stop();
                }
                else if(ui->tableWidget->currentColumn()!=column)
                {
                    nextpage=true;
                    vplayer->stop();
                    vplayer2->stop();
                }
                else if(column == timeCells.count()-1)
                {
                    nextpage=true;
                    vplayer->stop();
                    vplayer2->stop();
                }
                else if(column != timeCellIndex)
                {
                    nextpage=true;
                    vplayer->stop();
                    vplayer2->stop();
                }

            }
            createFakeTimeScale(timeCells[column].cellType,column);
        }
    else if(timeCells[column].cellType==2)
            {
                if(ui->tableWidget->currentColumn()!=column)
                {
                    vplayer->stop();
                    vplayer2->stop();
                    createFakeTimeScale(timeCells[column].cellType,column);
                    nextpage=true;

                }

            }
    else createFakeTimeScale(timeCells[column].cellType,column);
        pageIndex = timeCells[column].currentPage;
    timeCellIndex = column;
        int tmp1=0,tmp2=0;
        QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
        QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);
        while(tmp1<currentCam1Index)
        {
            Iter1.next();
            tmp1++;
        }
        while(tmp2<currentCam2Index)
        {
            Iter2.next();
            tmp2++;
        }
        if(nextpage)
        {
             calculateMaxOffset();
             if(timeCells[column].cellType==0)
             {
                vplayer->stop();
                vplayer2->stop();
                openVideoFile(Iter1.key(),Iter2.key());
                if(state1==3)
                {
                    vplayer->play();
                    mythread->start();
                }
                else if(state1==4)
                {
                    vplayer->pause();
                    mythread->exit();
                }
                if(state2==3)
                {
                    vplayer2->play();
                    mythread->start();
                }
                else if(state2==4)
                {
                    vplayer2->pause();
                    mythread->exit();
                }
             }
             else
             {
                 vplayer->stop();
                 vplayer2->stop();
             }
            if((timeCells[column].cellType==0)|(timeCells[column].cellType==3))
                openLogFile(dataMap[pageIndex].logName);
            if(timeCells[column].cellType==0)
            {
                if(mythread->isRunning())
                {
                    correctFramePosition();
                }
                if(vplayer->getVideoState()==3)
                {
                    correctFramePosition();
                }
            }
            else
            {
                if(mythread->isFinished())
                {
                    qDebug() << "here";
                    correctFramePosition();
                }
                else
                {
                    qDebug() << "or here";
                    correctFramePosition();
                }
            }
            correctFramePosition();
        }

}



void MainWindow::on_horizontalSlider_actionTriggered(int action)
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //correctFramePosition();
//    if(event->)
//    ////qDebug() << "paint event";
//        line1->setP1(ui->horizontalSlider->rect().topLeft());
//        line1->setP2(ui->horizontalSlider->rect().topRight());
//        line2->setP1(ui->horizontalSlider->rect().topLeft());
//        line2->setP2(ui->horizontalSlider->rect().bottomLeft());
//        line3->setP1(ui->horizontalSlider->rect().bottomLeft());
//        line3->setP2(ui->horizontalSlider->rect().bottomRight());
//        line4->setP1(ui->horizontalSlider->rect().bottomRight());
//        line4->setP2(ui->horizontalSlider->rect().bottomLeft());
//    QPoint tmpPos = ui->horizontalSlider->pos();
//    ui->line->setGeometry(ui->horizontalSlider->geometry());
//    QRect tmp = ui->line->rect();
//    QPoint ptmp = ui->horizontalSlider->pos();
//    //top line
//    tmp.setX(ptmp.x());
//    tmp.setY(ptmp.y()-tmp.height());
//    tmp.setSize(ui->line->rect().size());
//    ui->line->setGeometry(tmp);
//    //left line
//    tmp = ui->line_2->rect();
//    tmp.setX(ptmp.x());
//    tmp.setY(ptmp.y()-1);
//    tmp.setHeight(ui->horizontalSlider->height());
//    tmp.setWidth(1);
//    ui->line_2->setGeometry(tmp);
//    //right line
//    tmp = ui->line_3->rect();
//    tmp.setX(ptmp.x()+ui->horizontalSlider->width()-1);
//    tmp.setY(ptmp.y()-1);
//    tmp.setHeight(ui->horizontalSlider->height());
//    tmp.setWidth(1);
//    ui->line_3->setGeometry(tmp);
//    //bottom line
//    tmp = ui->line_4->rect();
//    tmp.setX(ptmp.x());
//    tmp.setY(ptmp.y()+ui->horizontalSlider->height()-ui->line->height());
//    tmp.setSize(ui->line->rect().size());
}


void MainWindow::on_screen1SoundButton_clicked()
{
    toggleSoundState(1);
    updateSoundMode();
    showCameraNameTimer->start(200);
}

void MainWindow::on_screen2SoundButton_clicked()
{
    toggleSoundState(2);
     updateSoundMode();
     showCameraNameTimer->start(200);
}

void MainWindow::toggleSoundState(int count)
{
    if(count==1)
    {
        if(sound1IconState>0)
        {
            if(sound1IconState==1)
            {
                sound1IconState = 2;
                if(sound2IconState>0)
                    sound2IconState = 1;
            }
            else
            {
                sound1IconState = 1;
                if(sound2IconState>0)
                    sound2IconState = 2;
            }
        }
    }
    else
    {
        if(sound2IconState>0)
        {
            if(sound2IconState==1)
            {
                sound2IconState = 2;
                if(sound1IconState>0)
                    sound1IconState = 1;
            }
            else
            {
                sound2IconState = 1;
                if(sound1IconState>0)
                    sound1IconState = 2;
            }
        }
    }
    setSoundIcons();
}
void MainWindow::setSoundIconState(int snum, int state)
{
    if(snum==1)
    {
        sound1IconState = state;
    }
    if(snum==2)
    {
        sound2IconState = state;
    }
}

void MainWindow::setSoundIcons()
{
    switch (sound1IconState)
    {
        case 1:
            ui->screen1SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
            ui->screen1SoundButton->setEnabled(true);
            break;
        case 2:
            ui->screen1SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
            ui->screen1SoundButton->setEnabled(true);
            break;
        default:
            ui->screen1SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
            ui->screen1SoundButton->setEnabled(false);
            break;
    }
    switch (sound2IconState)
    {
        case 1:
            ui->screen2SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
            ui->screen2SoundButton->setEnabled(true);
            break;
        case 2:
            ui->screen2SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
            ui->screen2SoundButton->setEnabled(true);
            break;
        default:
            ui->screen2SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
            ui->screen2SoundButton->setEnabled(false);
            break;
    }
}

void MainWindow::updateSoundMode()
{

    if(sound1IconState>0)
    {
        if(sound1IconState==1)
            vplayer->setAudioMuted(true);
        else
        {
            vplayer->setAudioMuted(false);
        }
    }
    if(sound2IconState>0)
    {
        if(sound2IconState==1)
            vplayer2->setAudioMuted(true);
        else
            vplayer2->setAudioMuted(false);
    }
    setSoundIcons();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->playButton->isEnabled())
    {
        keyboardKey = event->key();
        if(event->key()==Qt::Key_Space)
            qDebug() << "space pressed";
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() != keyboardKey)
      return;
    keyboardKey = 0;
    switch(event->key())
    {
    case Qt::Key_Space:
        qDebug() << "space released";
        ui->playButton->click();
        break;
    case Qt::Key_Escape:
       // Обработка нажатия Esc
       break;
    case Qt::Key_Enter:
       // Обработка нажатия Enter
       break;
    default:
        break;
     // Обработчики других клавиш
    }
   // update();
}

void MainWindow::on_hideSummary_clicked()
{
    if(!summaryIsHidden)
    {
        hideSummaryCounter=15;
        ui->hideSummary->setEnabled(false);
        hideSummarySeamlessTimer->start(5);
    }
    else
    {
        hideSummaryCounter=0;
        ui->hideSummary->setEnabled(false);
        hideSummarySeamlessTimer->start(5);

    }
}

void MainWindow::hideSummaryTimerTick()
{
    if(!summaryIsHidden)
    {
        if(hideSummaryCounter>0)
        {
            ui->summaryBox->setMinimumHeight(hideSummaryCounter*10);
            ui->summaryBox->setMaximumHeight(hideSummaryCounter*10);
            hideSummaryCounter--;

        }
        else
        {
            ui->summaryBox->setMinimumHeight(0);
            ui->summaryBox->setMaximumHeight(0);
            tmpIcon = new QIcon(":new/p/showPanel");
            ui->hideSummary->setIcon(*tmpIcon);
            summaryIsHidden = true;
            ui->hideSummary->setEnabled(true);
            hideSummarySeamlessTimer->stop();
            this->update();
        }
    }
    else
    {
        if(hideSummaryCounter<15)
        {
            ui->summaryBox->setMinimumHeight(hideSummaryCounter*10);
            ui->summaryBox->setMaximumHeight(hideSummaryCounter*10);
            hideSummaryCounter++;

        }
        else
        {
            ui->summaryBox->setMinimumHeight(150);
            ui->summaryBox->setMaximumHeight(150);
            tmpIcon = new QIcon(":new/p/hidePanel");
            ui->hideSummary->setIcon(*tmpIcon);
            ui->hideSummary->setEnabled(true);
            summaryIsHidden = false;
            hideSummarySeamlessTimer->stop();
            this->update();
        }
    }
}

void MainWindow::syncroTimerTimeout()
{

}

void MainWindow::pauseDelayTimerTimeout()
{
    pauseDelayFinished = true;
    pauseDelayTimer->stop();
}
