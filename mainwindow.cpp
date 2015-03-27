#include "mainwindow.h"
#include "ui_myform.h"

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{

}

void MyThread::run()
{
//    Timer = new QTimer;
//    loop = new QEventLoop(this);
//    timerTicks = 0;

//    connect(Timer,SIGNAL(timeout()),this,SLOT(timerTick()));
//    loop->exec();
    //exec();
}

void MapTimeScaleDraw::drawLabel(QPainter *painter, double value) const
{
//   double beforeVal = value;
    QwtText lbl = tickLabel( painter->font(), value );
    if ( lbl.isEmpty() )
        return;
//        lbl = tickLabel( painter->font(), beforeVal );
//     if ( lbl.isEmpty() )
//        return;

    QPointF pos = labelPosition( value );
        pos = labelPosition( value );
//        if(value==timeArrLength-7201)
//            pos.setX(pos.x()-45);
        if(value==timeArrLength-1)
            pos.setX(pos.x()-45);
        else if(value==timeArrLength-timeArrDelta)
            pos.setX(pos.x()-23);
//        ////qDebug() <<"timeArrLength" <<timeArrLength;
//        ////qDebug() << "timeArrDelta"<< timeArrDelta;
    QSizeF labelSize = lbl.textSize( painter->font() );

    const QTransform transform = labelTransformation( pos, labelSize );
    painter->save();
    painter->setWorldTransform( transform, true );
    lbl.draw ( painter, QRect( QPoint( 0, 0 ), labelSize.toSize() ) );
    painter->restore();
}


void MyThread::getTicksFromWorker(int ticks)//receiving signal from worker and emitting signal to app
{
    //////qDebug() << "ticks" << ticks;
    emit tickOut(ticks); //send ticks to out space
}

void MyThread::synchroTick(int ms)
{
    //////qDebug() << "tick";
    emit tickIn(ms);    //send ticks into worker
}

//void ThreadWorker::ticksToThread(int ms)
//{
//    emit
//}
ThreadWorker::~ThreadWorker()
{
    stopTimer();
}
ThreadWorker::ThreadWorker()
{



}

void ThreadWorker::synchroTickFromThread(int ms)
{

    //////qDebug() << "recieved video time" << ms<<"self time"<<tickCounter;
    tickCounter = ms;
}

void ThreadWorker::timerTick()
{
    tickCounter++;
//    //////qDebug() << "init complete";
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

//int MyThread::tickOut()
//{
//   return timerTicks;
//}

//void MyThread::timerTick()
//{
//    timerTicks++;
////   //////qDebug()<< timerTicks;
//    //here we have to emit some signal
////    emit tick();

//}

//void MyThread::setTimerInterval(int ms)
//{
//    Timer->setInterval(ms);
//}

//void MyThread::stopTimer()
//{
////    loop->exit();
//    Timer->stop();
//   //    timerTicks = 0;

//}

//void MyThread::restartTimer()
//{
//    timerTicks = 0;
//    Timer->start(1);

////    Timer->start();
//}

//void MyThread::setTimerZero()
//{
//    timerTicks = 0;
//}


// TableWidget::TableWidget()
// {
//  setRowCount(10);
//  setColumnCount(5);
//  QTableWidgetItem *newItem = new QTableWidgetItem("An item");
//  setItem(0,0, newItem);
//  horizontalHeader()->setSectionResizeMode();
//  verticalHeader()->setResizeMode(QHeaderView::Stretch);
// }

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //this->setCentralWidget(ui->widget);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->comboBox_2->setVisible(false);
    ui->screen1SoundButton->setVisible(false);
    ui->screen2SoundButton->setVisible(false);

    videoButton = new QPushButton(ui->mainToolBar);
    ui->nextFrameButton->setVisible(true);
    ui->frameBackwardButton->setVisible(false);
    ui->line->setVisible(false);
    ui->line_2->setVisible(false);
    ui->line_3->setVisible(false);
    ui->line_4->setVisible(false);
    ui->line_5->setVisible(false);
    ui->line_5->installEventFilter(this);
    ui->line_5->setAttribute( Qt::WA_TransparentForMouseEvents );
    ui->ScaleWidget->setVisible(false);

//    videoCheck = new QCheckBox("");
//    logButton = new QPushButton("");
//    logCheck = new QCheckBox("");
    ui->timeEdit->setDisabled(true);
    videoButton->setMaximumWidth(25);
    videoButton->setMinimumWidth(25);
    videoButton->setMaximumHeight(25);
    videoButton->setMinimumHeight(25);
    videoButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->mainToolBar->addWidget(videoButton);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(ui->previousTimeSegment);
    ui->mainToolBar->addWidget(ui->frameBackwardButton);
    ui->mainToolBar->addWidget(ui->playButton);
    ui->mainToolBar->addWidget(ui->stopButton);
    ui->mainToolBar->addWidget(ui->nextFrameButton);
    ui->mainToolBar->addWidget(ui->nextTimeSegment);
    ui->mainToolBar->addWidget(ui->timeEdit);
  /*  QWidget *w1 = new QWidget;
    coloredBars.append(*w1);
    coloredBars.at(0).setPalette(QPalette(Qt::green,Qt::green,Qt::green,Qt::green,Qt::green,Qt::green,Qt::green));
*/
//    logButton->setMaximumWidth(25);
//    logButton->setMinimumWidth(25);
//    logButton->setMaximumHeight(25);
//    logButton->setMinimumHeight(25);
//    logButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
//    logButton->setVisible(false);
//    videoCheck->setEnabled(false);
//    logCheck->setEnabled(false);
//    ui->horizontalLayout_5->addWidget(logButton);
//    ui->horizontalLayout_5->addWidget(ui->lineEdit_2);
//    ui->horizontalLayout_5->addWidget(logCheck);
//    ui->horizontalLayout_5->addWidget(videoButton);
//    ui->horizontalLayout_5->addWidget(ui->lineEdit);
//    ui->horizontalLayout_5->addWidget(videoCheck);
//    ui->lineEdit->setText("Выберите директорию с видео файлами");
//    ui->lineEdit->setEnabled(false);
//    ui->lineEdit_2->setText("Выберите директорию с лог-файлами");
//    ui->lineEdit_2->setEnabled(false);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->nextTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->previousTimeSegment->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->frameBackwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->nextFrameButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->screen1SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->screen1SoundButton->setEnabled(false);
    ui->screen2SoundButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->screen2SoundButton->setEnabled(false);
//    sound1Enabled = 1;
//    sound2Enabled = 2;
    ui->pushButton->setVisible(false);
    QString str = "12121212";
    qDebug() << str.toUtf8().data();
//               GLOBALMODE = debmode;
//    ui->Thermo->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
//    ui->Thermo_2->setOrientation(Qt::Horizontal,QwtThermo::NoScale);

    timer = new QTimer(this);
    ui->progressBar->setVisible(false);
    dataMap.clear();
    timeFracts.clear();
    isFolderOpened= false;
    pageIndex=0;
    camQty = 0;
//    connect(timer, SIGNAL(timeout()),this,SLOT(updateTime()));
    #ifdef GLOBALMODE
    videoLayout1 = new QHBoxLayout;
    vplayer = new VideoPlayer;
    delayTimer = new QTimer(this);
    stateTimer = new QTimer(this);
    getTimeTimer = new QTimer(0);
    simpleDelayTimer = new QTimer(this);
    waitEndStateTimer = new QTimer(this);
    showCameraNameTimer = new QTimer(this);
    vplayer->defineVideo(/*ui->widget*/this,ui->widget);

    mythread = new QThread(this);
    someThread = new MyThread(this);
    worker = new ThreadWorker();
//    connect(worker,SIGNAL(ticksToThread(int)),someThread,SLOT(getTicksFromWorker(int)));
//    connect(someThread,SIGNAL(tickIn(int)),worker,SLOT(synchroTickFromThread(int)));
    connect(worker, SIGNAL(finished()),worker,SLOT(deleteLater()));
    connect(someThread,SIGNAL(finished()),someThread,SLOT(deleteLater()));
    connect(worker,SIGNAL(ticksToThread(int)),this, SLOT(getThreadedTicks(int)));
    connect (this, SIGNAL(sendTicksToWorker(int)),someThread,SLOT(synchroTick(int)));
    connect (someThread,SIGNAL(tickIn(int)),worker,SLOT(synchroTickFromThread(int)));
    someThread->start();
    worker->moveToThread(someThread);
    worker->initWorker();
    worker->startTimer(10);
//    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->horizontalHeader()->setVisible(false);
//    ui->tableWidget_3->setColumnWidth(0,200);
//    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//    QEventLoop *eloop = new QEventLoop(mythread);
//    eloop->exec();
    threadTimer = new QTimer(0);
    threadTimer->setInterval(10);
    threadTimer->moveToThread(mythread);
    connect(threadTimer,SIGNAL(timeout()),SLOT(updateTime()));//,Qt::DirectConnection
    QObject::connect(mythread,SIGNAL(started()),threadTimer,SLOT(start()));
    QObject::connect(mythread,SIGNAL(finished()),threadTimer,SLOT(stop()));
    //////qDebug() << "parent of timer" << timer->parent();
    //////qDebug() << "parent of threadTimer" << threadTimer->parent();

//    //////qDebug() << "process of timer" << timer->parent();
//    //////qDebug() << "process threadTimer" << threadTimer->parent()->thread();
//    thrd = new MyThread();
//    thrd->start();
//    getTimeTimer->setTimerType(Qt::PreciseTimer);
//    connect(thrd,SIGNAL(tick()),this,SLOT(getTimeTimerTick())); //it works too

//    thrd->start();
//    thrd->restartTimer();
    ui->widget->setLayout(videoLayout1);
//    vplayer->_player->startTimer(40,Qt::PreciseTimer);
    videoLayout2 = new QHBoxLayout;
    vplayer2 = new VideoPlayer;
    vplayer2->defineVideo(ui->widget_2,ui->widget_2);
    connect(delayTimer,SIGNAL(timeout()),this,SLOT(delayTimerTick()));
    connect(videoButton,SIGNAL(clicked()),this,SLOT(on_action_4_triggered()));
//    connect(logButton,SIGNAL(clicked()),this,SLOT(on_action_triggered()));
    connect(vplayer->_player,SIGNAL(timeChanged(int)),this,SLOT(setVideoTime()));
    connect(vplayer->_player, SIGNAL(end()),this,SLOT(stop()));
    connect(vplayer2->_player, SIGNAL(end()),this,SLOT(stop()));
    connect(vplayer->_player,SIGNAL(playing()),this,SLOT(setPlayer1ModePlaying()));
    connect(vplayer2->_player,SIGNAL(playing()),this,SLOT(setPlayer2ModePlaying()));
    connect(vplayer->_player,SIGNAL(paused()),this,SLOT(setPlayer1ModePaused()));
    connect(vplayer2->_player,SIGNAL(paused()),this,SLOT(setPlayer2ModePaused()));
    connect(vplayer->_player,SIGNAL(opening()),this,SLOT(setPlayer1ModeOpening()));
    connect(vplayer2->_player,SIGNAL(opening()),this,SLOT(setPlayer2ModeOpening()));
    connect(waitEndStateTimer,SIGNAL(timeout()),this,SLOT(waitEndStateTimerTick()));
    connect(vplayer->_player,SIGNAL(stateChanged()),this,SLOT(setPlayer1State()));
    connect(vplayer2->_player,SIGNAL(stateChanged()),this,SLOT(setPlayer2State()));
//    connect(vplayer->_player, SIGNAL(stateChanged()),this,SLOT(stateTimerTick()));
//    connect(vplayer2->_player, SIGNAL(stateChanged()),this,SLOT(stateTimerTick()));
    connect(simpleDelayTimer, SIGNAL(timeout()),this,SLOT(simpleDelayTimerTick()));
    connect(stateTimer, SIGNAL(timeout()),this,SLOT(stateTimerTick()));
    connect(showCameraNameTimer,SIGNAL(timeout()),this,SLOT(on_nextFrameButton_clicked()));

//    connect(getTimeTimer,SIGNAL(timeout()),this,SLOT(getTimeTimerTick()));
//    connect(vplayer->_player,SIGNAL(paused()),vplayer2->_player,SLOT(pause()));
//    connect(vplayer2->_player,SIGNAL(paused()),vplayer->_player,SLOT(pause()));
//    ui->horizontalLayout_6->setEnabled(false);
    #endif
//    this->setEnabled(false);
//    ui->menuBar->setEnabled(true);
//    ui->menu->setEnabled(true);

    ui->ScaleWidget->setAlignment(QwtScaleDraw::TopScale);
    ui->ScaleWidget->installEventFilter(this);
//    QwtPlotMarker marker;
//    marker.attach(ui->qwtPlot);

    secondsCounter = 0;
    realSecondsCounter = 0;
    delayMs = 0;
    logVideoDelta = 0;
    logVideoDeltaCounter = 0;
    lastDelay = 0;
    setButtonPanelEnabled(false);
            getTimeTickCounter =0;
//            getTimeTimer->start(1);
//    openLogConfigFile(&logWorkingDir);
//    openVideoConfigFile(&videoWorkingDir);
//    openVideoFilesFolder(&videoList);
//    ////////qDebug()() << videoList;

    log = new logProcessor;
    interpreter = new TMIinterpretator;
    msys = new msgSys;
    isVideo1Opened = false;
    isVideo2Opened = false;
    ui->widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->widget_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


//    vplayer->video->setGeometry(ui->widget->geometry());
//    ////////qDebug()() << ui->widget->geometry();
//    ////////qDebug()() << ui->widget_2->geometry();
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
//    QGridLayout *lay = new QGridLayout();

//    ui->widget_3->setLayout(lay);
//    QPushButton *tmpbtn1 = new QPushButton(ui->widget_3);
//    QPushButton *tmpbtn2 = new QPushButton(ui->widget_3);
//    QPushButton *tmpbtn3 = new QPushButton(ui->widget_3);
//    QPushButton *tmpbtn4 = new QPushButton(ui->widget_3);
//    QPushButton *tmpbtn5 = new QPushButton(ui->widget_3);
//    QPushButton *tmpbtn6 = new QPushButton(ui->widget_3);
//    lay->addWidget(tmpbtn1,0,0);
//    lay->addWidget(tmpbtn2,0,1);
//    lay->addWidget(tmpbtn3,0,2);
//    lay->addWidget(tmpbtn4,0,3);
//    lay->addWidget(tmpbtn5,0,4);
//    lay->addWidget(tmpbtn6,1,2);
//    ////qDebug() << p.color(QPalette::Foreground);
//    QApplication::setPalette(p);
//    ui->checkBox->setPalette(p);
//    ui->checkBox->setEnabled(true);
//    ui->checkBox->setStyleSheet("QCheckBox#checkBox:checked{color:black;}QCheckBox#checkBox:unchecked{color:black;}");
//    ui->checkBox->setStyleSheet( "QCheckBox:checked{color: black;}");
//    ui->checkBox->setStyleSheet( "QCheckBox:unchecked{color: black;}");
//    ui->checkBox->setStyleSheet( "QCheckBox:disabled{color: black;}");
//    ui->checkBox->setStyleSheet( "QCheckBox::indicator{width:60px;height:60px;}");
//    ui->checkBox->setStyleSheet( "QCheckBox::indicator:disabled{color: black;}");
//    line1 = new QLine();
//    line2 = new QLine();
//    line3 = new QLine();
//    line4 = new QLine();
//    ui->progressBar_2->setVisible(false);
//    ////qDebug() << ui->line->geometry();
//    ////qDebug() << ui->line_2->geometry();
//    ////qDebug() << ui->line_3->geometry();
//    ////qDebug() << ui->line_4->geometry();
//    line1 = new QLine(ui->horizontalSlider->rect().topLeft(),ui->horizontalSlider->rect().topRight());
//    line2 = new QLine(ui->horizontalSlider->rect().topLeft(),ui->horizontalSlider->rect().bottomLeft());
//    line3 = new QLine(ui->horizontalSlider->rect().bottomLeft(),ui->horizontalSlider->rect().bottomRight());
//    line4 = new QLine(ui->horizontalSlider->rect().bottomRight(),ui->horizontalSlider->rect().bottomLeft());
//correctFramePosition();
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
//   // tmp.setHeight(ui->horizontalSlider->height());
//   // tmp.setWidth(1);
//    ui->line_4->setGeometry(tmp);
//    ////qDebug() << tmp;
//    ////qDebug() << ui->line_4->pos();
//    ////qDebug() << ui->line_4->rect();
    //myFrame = new FlyingFrame(this,ui->tableWidget,ui->horizontalSlider);
    //myFrame->update();
   // //myFrame->setGeometry(0,0,1000,200);
//    QPainter *p = new QPainter(ui->tableWidget_3);
//    QPen pen;
//    pen.setColor(Qt::black);
//    pen.setWidth(4);
   // p->setPen(pen);
//    p->setBrush(QBrush(QColor(255,0,0,0 ? 255:0)));
//    p->drawEllipse(10,0,10,10);


//    QPointF p1,p2;
//    p1.setX(0);
//    p1.setY(50);
//    p2.setX(20);
//    p2.setY(70);
//    p->drawLine(p1,p2);
//    ui->tableWidget_3->update();
//    this->update();
//    p->setWindow(0,0,100,100);
//    p->drawLine(p1,p2);
    //ui->widget_3->size();
     //ui->ScaleWidget->setAlignment(QwtScaleDraw::TopScale);
//    ui->Slider->setRange( 1000.0, 3000.0, 10.0, 10 );
  //  ui->Slider->setScalePosition(QwtSlider::TopScale);

  //  ui->ScaleWidget->repaint();
    //ui->Slider->setScaleDraw(mapTimeScale);
//    ui->Slider->setTracking(true);

//    QwtScaleWidget *myScale;
//    myScale = new QwtScaleWidget(QwtScaleDraw::TopScale,ui->verticalLayout_3);

//    QString tmp = "Нет";
//    ui->comboBox->addItem(tmp);
//     ////qDebug() << "WTF??";
//    ui->comboBox_2->addItem(tmp);

}
void MainWindow::correctCellSeekerPosition(int newPos)
{
//    ui->tableWidget->viewport()->lower();
    ui->tableWidget->lower();
    ui->ScaleWidget->lower();
    ui->line_5->setLineWidth(4);
    ui->line_5->setPalette(ui->ScaleWidget->palette());
    QRect tmp = ui->line_5->rect();
//    //qDebug() << "before"<<this->mapToParent(ui->tableWidget->rect().bottomLeft());
    QPoint ptmp;
    ptmp = ui->ScaleWidget->pos();
    ptmp.setX(ptmp.x()+ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn()));
    //qDebug() << ui->line_5->palette().background();
    //qDebug() << "newPos" << newPos;
    //qDebug() << "ptmp.x"<< ptmp.x();
    if(newPos>=0)
    {
        tmp.setX(ptmp.x()+newPos);
        tmp.setY(ptmp.y()+15);
        tmp.setWidth(3);
        tmp.setHeight(22);//-tmp.height());
        ui->line_5->setGeometry(tmp);
        ui->line_5->setVisible(true);
//        ui->line_5->repaint();
    }

//    //qDebug() << "after"<<newPos;//ui->ScaleWidget->mapToGlobal(ui->line_5->rect().bottomLeft());
//    ui->line_5->setAttribute( Qt::WA_TransparentForMouseEvents );

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
    //qDebug() << "test resize";
    int X1, Y1, X2, Y2;
    ////////qDebug()() << ui->widget_2->geometry();
    ////////qDebug()() << vplayer2->getGeometry();
    currentWidget1Geometry = ui->widget->geometry();
    currentWidget2Geometry = ui->widget_2->geometry();
    baseVideo1Geometry.setSize(ui->widget->geometry().size());
    baseVideo1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
    currentWidget1Geometry.setCoords(X1,Y1,X2,Y2);
//    ////////qDebug()() <<"Y changed" << currentWidget1Geometry;
//    if(currentWidget1Geometry != ui->widget->geometry())
        vplayer->changeGeometry(currentWidget1Geometry);
    baseVideo2Geometry.setSize(ui->widget_2->geometry().size());
    baseVideo2Geometry.getCoords(&X1,&Y1,&X2,&Y2);
    currentWidget2Geometry.setCoords(X1,Y1,X2,Y2);
    //myFrame->setBottomWidget(ui->horizontalSlider);
    //myFrame->adjustPos(ui->horizontalSlider,ui->tableWidget);
    //myFrame->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    //myFrame->setAttribute(Qt::WA_TransparentForMouseEvents,true);
//    if(currentWidget2Geometry != ui->widget_2->geometry())
    float totalRelativeWidth=0;

    int totalColumnWidth = 0;

        vplayer2->changeGeometry(currentWidget2Geometry);
        if(dataMap.size()!=0)
        {
//            timeCells[i].colWidth
//            for(int i = 0; i < timeCells.size(); i++)
//            {
//                ui->tableWidget->setColumnWidth(i,((float)ui->tableWidget->width()*timeCells[i].relativeWidth));
//                totalColumnWidth+=ui->tableWidget->columnWidth(i);
//            }
            for(int i = 0; i < ui->tableWidget->columnCount(); i++)
                totalColumnWidth+=(float)((ui->tableWidget->width())*timeCells[i].relativeWidth);
//            ////qDebug() << totalColumnWidth;
            if(ui->ScaleWidget->width()!=totalColumnWidth)
            {
                float correctGain=(float)(ui->ScaleWidget->width())/((float)(totalColumnWidth));
                ////qDebug() << "correctGAin" << correctGain;
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
//            QRect tmpGeometry = ui->tableWidget->geometry();
//            tmpGeometry.setWidth(totalColumnWidth);
//            ui->tableWidget->setGeometry(tmpGeometry);
//            ui->tableWidget->setColumnWidth(i,ui->tableWidget->width()*(dataMap[i].timeEdge2-dataMap[i].timeEdge1)/(dataMap[dataMap.size()-1].timeEdge2 -dataMap[0].timeEdge1 ));
        }
        else
        {
            ////qDebug() << "ERRRORRRRR";
        }
//        ////qDebug() << "total relative width" << totalRelativeWidth;
//        ////qDebug() << "total column width" << totalColumnWidth;
//        ////qDebug() << "width from native method" << ui->tableWidget->width();
//        ////qDebug() << "width of scale is" << ui->ScaleWidget->width();
        //qDebug() << "v7";
        correctCellSeekerPosition(((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->ScaleWidget->width());
        correctFramePosition();

//        ////qDebug() << "column widthes";
//        for(int a = 0; a < pageVector.size();a++)
//            ////qDebug() << ui->tableWidget->columnWidth(a);
//     tmp.setTop(ui->horizontalSlider->rect().top());
//     ui->line->setGeometry(tmp);
//     ui->line->rect().setTop(ui->horizontalSlider->rect().top());
//     ui->line->setGeometry(tmp);
 //    ui->line->setFrameRect(ui->horizontalSlider->rect());
//     ui->line->setGeometry();
}

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
        ////////qDebug()() << "camName"<<camName;
    }
    if(lastOpenedFileIndex!=-1)
    {
        lastFile = videoList[lastOpenedFileIndex];
        ////////qDebug()() << lastFile;
     //check if camIndex didn't changed
//        QByteArray tmparr = lastFile.toLocal8Bit();
        int tmpIndexOfMkv = lastFile.indexOf(".mkv");
        int beforeindex = (int)lastFile.toLocal8Bit()[tmpIndexOfMkv-1]-0x30;
        int deltaindex=0;
//        beforeindex = (int)tmparr[3];
        ////////qDebug()() << beforeindex;
//        if(beforeindex!=camIndex)//it means that camera is changed so we need to calculate delta index
//        {
            deltaindex = beforeindex-camIndex;
            ////////qDebug()() << deltaindex;
//        }
        if(lastOpenedFileIndex+ui->comboBox->count()-1>=videoList.size())
            return -2;
        else
            return lastOpenedFileIndex+ui->comboBox->count()-1+deltaindex+jumpindex;
    }
    return camIndex-1+jumpindex;
}

int MainWindow::initSlider(int topVal)
{

    return 0;
}


int MainWindow::initColoredScale()
{
    ////qDebug() << "start initcoloredscale";
    int length = dataMap.size();
    int totalWidth = dataMap[dataMap.size()-1].timeEdge2 - dataMap[0].timeEdge1;\
//    ////qDebug() << "width of " << totalWidth;
//    ////qDebug() << "width of tablewidget"<< ui->tableWidget->width();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    for(int a = 0; a< timeCells.size(); a++)
    {
        ui->tableWidget->insertColumn(a);
//        ////qDebug() << "column number" << a << " inserted in tablewidget"<<timeCells[a].cellType;
//        QMapIterator <QString, bool> Iter(dataMap[i].videoVector);
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
//        ////qDebug() << "TIMECELLTOTALTIME" << timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
        int tmpTotalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;//(int)(dataMap[dataMap.size()-1].timeEdge2 - dataMap[0].timeEdge1);
        time_t step = (int)(tmpTotalTime/(timeScaleTickCounter-1));
        time_t vals[tmpTotalTime];
        for(int i =0; i < tmpTotalTime-1; i++)
        {
            vals[i] = timeCells[0].beginTime+i;//dataMap[0].timeEdge1+i/**step*/;
        }
        vals[tmpTotalTime-1] = timeCells[timeCells.size()-1].endTime;//dataMap[dataMap.size()-1].timeEdge2;
        QList<double> ticks[QwtScaleDiv::NTickTypes];
        QList<double> &majorTicks = ticks[QwtScaleDiv::MajorTick];
        QList<double> &minorTicks = ticks[QwtScaleDiv::MinorTick];
        int tmpStartTime = timeCells[0].beginTime%7200;//dataMap[0].timeEdge1%7200;
        ////qDebug() << "here";
//        ////qDebug() << "TMPSTARTTIME" << tmpStartTime;
//        ////qDebug() << "TMPTOTALTIME" << tmpTotalTime;
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
        ////qDebug() << "majorticks count" << majorTicks.count();
        ////qDebug() << "minorticks count" << minorTicks.count();
              ////qDebug() << "here1";
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
        ////qDebug() << "Quit Creating Time Scale";
        QwtScaleDiv mTimeScaleDiv = QwtScaleDiv(majorTicks.first(), majorTicks.last(), ticks);
        mapTimeScale = new MapTimeScaleDraw("hh:mm:ss");

//        ////qDebug() <<"majortickssize" << majorTicks.at(majorTicks.size()-2);
        mapTimeScale->setTimeArrayDelta(tmpTotalTime-majorTicks[majorTicks.size()-2]);
        mapTimeScale->setTimeArr(vals,tmpTotalTime);
        mapTimeScale->setLabelAlignment(Qt::AlignRight);
        ui->ScaleWidget->setScaleDraw(mapTimeScale);
        ui->ScaleWidget->setContentsMargins(0,0,-43,0);//leveling scale labels alignment balance
        QwtScaleTransformation *tr= new QwtScaleTransformation(QwtScaleTransformation::Linear);
        ui->ScaleWidget->setScaleDiv(tr,mTimeScaleDiv);
    }
    else return 1;
    moveToAnotherTimeSegment(0);
    ui->tableWidget->selectColumn(0);
//    for(int a =0 ; a < pageFlagVector.size(); a++)
//    {
//        ////qDebug() << "pageFlagVector :" << pageFlagVector.at(a) <<"pageVector" << pageVector.at(a)<<"pageEndTimes"<<pageEndTimes.at(a);
//    }
    ////qDebug() << "pos4";
    //qDebug() << "v6";
    correctCellSeekerPosition(((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->ScaleWidget->width());
    //ui->tableWidget->installEventFilter(this);
    ui->tableWidget->viewport()->installEventFilter(this);
    this->resize(this->size().width()-1,this->size().height()-1);
    this->resize(this->size().width()+1,this->size().height()+1);
    ////qDebug() << "finish initcoloredscale";
    return 0;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getThreadedTicks(int ms)
{
    threadedTime = ms;
//    //////qDebug() << "received threaded time" << threadedTime;
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
                if(QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name)=="LAS_Counter                    ")
                {
                    retval++;
                    ////////qDebug()() << interpreter->TInterpItemArray[i].max;
                    thermoMaxs->append(interpreter->TInterpItemArray[i].max);
                }
            }
            if((interpreter->TInterpItemArray[i].typ&0xffff) == 8 )
            {
                QString tmpstr = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
                if((tmpstr == "LDS_Group1                     ")|(tmpstr == "LDS_Group2                     ")|(tmpstr == "LDS_Group3                     ")|(tmpstr == "LDS_Group4                     ")|(tmpstr == "LDS_Group5                     "))
                {
                    retval++;
                    ////////qDebug()() << interpreter->TInterpItemArray[i].max;
                    thermoMaxs->append(interpreter->TInterpItemArray[i].max);
                }
            }
           // else
                ////////qDebug()() << interpreter->TInterpItemArray[i].typ;

    }

   ////qDebug() << "there are maxs qty" << retval;
//    for (int i = 0; i < thermoMaxs->size(); i++)
//        ////////qDebug()() << thermoMaxs[i];
    return retval;
}

int MainWindow::initThermoNames(QVector<QString> *thermoNames, QVector<int> *dataSequence)
{
    int retval = 0;
    log->selectSegment(bigTableID);
    char buffArr1[log->segmentHeader.size];
    log->readSegment(buffArr1, log->segmentHeader.size );
//    ////qDebug() << "HERE?";
//    ////qDebug() << log->segmentHeader.size;
//    ////qDebug() << log->segmentHeader.recordSize;
    interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
//    ////qDebug() << interpreter->interpreterRecordsCount;
    interpreter->setInterpretationTable(buffArr1,interpreter->interpreterRecordsCount);
    ////qDebug() << "naaames";
    ////qDebug() << interpreter->interpreterRecordsCount;
    for(int i = 0; i < interpreter->interpreterRecordsCount; i++)
    {
//            ////qDebug() << interpreter->TInterpItemArray[i].name;
//            ////qDebug() << (interpreter->TInterpItemArray[i].level&0xffff);
//            ////qDebug() << (interpreter->TInterpItemArray[i].mask_&0xffff);
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
//                {
                    retval++;
                    dataSequence->append(8);
                    thermoNames->append(interpreter->TInterpItemArray[i].name);
//                }
            }
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
//    ////////qDebug()() << "next step";
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

//        case 0: //timeFracts
//        {
////            QVariant tmpVar = backIndex;
//            //timeFractExistFlag = true;
//            //timeFract[backIndex] = interpreter->fieldChar(record[recIndex]);
//            dp->timeFract.append(interpreter->fieldChar(&record[recIndex]));
//            dp->paramsSequence.append(0);
//            dp->paramsVisibleArr.append(0);
//            break;
//        }
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
//            ////qDebug() << tmpDbl;
            break;
        }
//        case 7:
//        {
//            float tmpFloat, tmpMinFloat, tmpMaxFloat;
//            int tmpIntFloat;
//            tmpFloat = interpreter->fieldFloat(&record[recIndex]);
////            ////qDebug() << tmpFloat;
//            if(tmpFloat==tmpFloat)
//            {
//                tmpMinFloat = interpreter->TInterpItemArray[i].min/pow(10,interpreter->TInterpItemArray[i].mask_);
//                tmpMaxFloat = interpreter->TInterpItemArray[i].max/pow(10,interpreter->TInterpItemArray[i].mask_);
//                if((tmpMinFloat==0)&&(tmpMaxFloat==0));
//                else
//                {
//                    if(tmpFloat!=tmpMinFloat)
//                    {
//                        if(tmpFloat<tmpMinFloat)tmpFloat = tmpMinFloat;
//                        if(tmpFloat>=tmpMaxFloat)tmpFloat = tmpMaxFloat;
//                    }
//                }
//                int tmpMask = interpreter->TInterpItemArray[i].mask_;
//                tmpFloat = tmpFloat*pow(10,tmpMask);
//                tmpIntFloat = tmpFloat;
//                tmpFloat = tmpIntFloat/pow(10,tmpMask);
//                //////////qDebug() << tmpFloat;
//                //Y[i-2/*-tmpInvisibleVarDecrease*/][backIndex] =  tmpFloat; //round((double)tmpFloat);
//                dp->floatTypes.append(tmpFloat);
//                dp->paramsSequence.append(7);
//                dp->paramsVisibleArr.append(1);
//            }
//            else
//            {
//               // Y[i-2/*-tmpInvisibleVarDecrease*/][backIndex] =0;
//                dp->floatTypes.append(0);
//                dp->paramsSequence.append(7);
//                dp->paramsVisibleArr.append(1);
////                tmpFloat=0;
//            }
//            break;
//        }
//        case 10 :
//        {
//            ////////////qDebug() << interpreter->TInterpItemArray[i].name;
//            recTime = (time_t)interpreter->fieldInt(&record[recIndex]);
////            ////qDebug() << recTime;
////            recTime = mktime(gmtime(&recTime));
////            ////qDebug() << recTime;
////            ////qDebug() << QDateTime::fromTime_t(recTime).toUTC();
////            ////qDebug() << QDateTime::fromTime_t(recTime).toUTC().toLocalTime();
//            if(interpreter->TInterpItemArray[i].name!="PowOnTime")
//            {
//                dp->time.append(recTime);
//                dp->paramsSequence.append(10);
//                dp->paramsVisibleArr.append(0);
//            }
//            else
//            {
//                //////////qDebug() << interpreter->TInterpItemArray[i].name;
//            }
//            break;
//        }
//        case 4://powOnTime
//        {

////            powOnTimeArrayExistFlag = true;
//            recTime = (time_t)interpreter->fieldInt(&record[recIndex]);
////            recTime = mktime(gmtime(&recTime));
//           // powOnTimeArray[backIndex] = recTime;//(int)((uint)recTime-(uint)firstPointDateTime);
//            dp->powOnTime.append(recTime);
//            dp->paramsSequence.append(4);
//            dp->paramsVisibleArr.append(0);
//            break;
//        }
        case 8 :
        {

            bool flag = false;
               // dateChangedArrExistFlag = true;
               // ////////qDebug()() << "DateChg";
                //dateTimeChangeIndex = i;
//            if(QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name) == "LDS_Group1                     ")
            QString tmpstr = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
            if((tmpstr == "LDS_Group1                     ")|(tmpstr == "LDS_Group2                     ")|(tmpstr == "LDS_Group3                     ")|(tmpstr == "LDS_Group4                     ")|(tmpstr == "LDS_Group5                     "))
            {
//                ////qDebug() << tmpstr;
                flag = (bool)interpreter->fieldFlag(&record[recIndex],&interpreter->TInterpItemArray[i].mask_);
                    dp->flagTypes.append(interpreter->fieldFlag(&record[recIndex], &interpreter->TInterpItemArray[i].mask_));
                    dp->paramsSequence.append(8);
                    dp->paramsVisibleArr.append(1);
            }

            break;
        }
//        case 27:
//        {
////            ////////qDebug() << interpreter->TInterpItemArray[i].name;
//            int tmpErrVal = interpreter->fieldInt(&record[recIndex]);
//            dp->error.append(tmpErrVal);
//            dp->paramsSequence.append(27);
//            dp->paramsVisibleArr.append(1);
//            break;
//        }

        default:
        {
            break;
        }
        }

    }
    ////////qDebug()() << "finished getting data from rec";
    return 0;
}


int MainWindow::fillHeadTable()
{
    return 0;
}

int MainWindow::initBigThermos(int qty)
{
    qty = 2;
    QwtThermo *big1 = new QwtThermo;
    QwtThermo *big2 = new QwtThermo;
    ui->horizontalLayout_4->addWidget(big1);
    ui->horizontalLayout_4->addWidget(big2);
//    big1->heightMM() = 10;
//    big2->widthMM() = 100;
//    big2->widthMM() = 10;
    big1->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
    big2->setOrientation(Qt::Horizontal,QwtThermo::NoScale);

    return 0;
}
int MainWindow::createFullListOfVideos(int offsetsQty)
{
    camQty = offsetsQty;
//    ////qDebug() << "offsetsQty" << offsetsQty;
//    ////qDebug() << "size of loglist" << logList.size();
    if((videoList.size()/offsetsQty)>=logList.size())
    {
        //////qDebug()<< "quiting from createFullListOfVideos func with dishonor";
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

bool MainWindow::createTimeSegment(QStringList *listOfLogs)
{
    int something = 2;
    int success = true;
    time_t one,two;
    //////qDebug() << "logList size" << listOfLogs->size();
//    ////qDebug() << "creating time segment now";
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
//            ////qDebug() << "SUCCESS?"<< success;

            if(success)
            {
//                ////qDebug() << "iterator is" << i;

                    //////qDebug() << "working with file " << listOfLogs->at(i);

                    int tmpCount = ui->comboBox->count()-1;
                    if(tmpCount<0)
                        tmpCount = 0;
                    //////qDebug() << "tmpcount" << tmpCount;
                    if(openLogFile(listOfLogs->at(i))==-1)//if(openLogFile(videoList.at(i*tmpCount))==-1)
                    {
                        //////qDebug()<< "exit from creating time segment 1";
                        return false;
                    }
                    if(readCamOffsetsAndTimeEdges(&one, &two,&beginTimeFract,&endTimeFract,i))
                    {
                        offsetsAvailable = false;
//                        if(!camoffsetscounter)
//                        {
//                            QVariant tmpVal = tmpErr;
                            newMessage.setWindowTitle("Внимание!");
                            newMessage.setText("В логе "+logWorkingDir+"/"+ logList.at(i)+ " отсутствуют камерные задержки. " );
                            newMessage.exec();
//                        }
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
//                            ////qDebug() <<"camOffsets are" << camOffsets.at(j);
                        }
                        //////qDebug() << maxCamOffset;
                    }
                    if(readHeadTableData()==0)
                    {
//                        offsetsAvailable = true;
                        //////qDebug() << "reading time edges now";
                        videoOnly = false;
//                        success = true;
//                        readTimeEdges(&one, &two,&beginTimeFract,&endTimeFract);//one = first, two = second this function available only when reading time edges from log file

                    }
                    else
                        videoOnly = true;
//                        VlcInstance someInstance;

//                        VlcMedia videofile()
//                        one = videoList.at(i).

//                    }
                  if(!videoOnly)
                  {
                    if(two<one)
                        inverseTime = true;
                    else inverseTime = false;
                    timeSegment.append(one);
                    timeSegment.append(two);
                    qDebug() << one;
                    qDebug() << two;
                  }
                  else
                  {


                      //////qDebug()<< "exit from creating time segment 2";
                      success = false;
                  }

            }
//            this->update();
            ui->progressBar->setValue(i);

        }

//        ////qDebug() << "all videovals!!!!!!!!!!!!!!!!!!!!!!!!!!";
        for(int a = 0; a< videoTimes.size();a++)
        {
            qDebug() << videoTimes.at(a);
        }
                    ui->progressBar->setVisible(false);
                    correctFramePosition();
    ui->mainToolBar->setEnabled(true);
//    ui->comboBox->removeItem(0);
//    ui->comboBox_2->removeItem(0);
    for(int j=0; j< timeSegment.size(); j++)
    {
//        qDebug() << timeSegment.at(j);
//        ////qDebug() << timeSegment.at(j*2+1);
    }

    return success;
}

int MainWindow::createFakeTimeScale(int mode,int column)
{
    ////qDebug() << "creatinFakeTimeScale";
    ////qDebug() << "mode" << mode;
    ////qDebug() << "current column" << ui->tableWidget->currentColumn();
    ////qDebug() << "column" << column;
//    timer->stop();
    if(mode!=0)
    {
        vplayer->stop();
        vplayer2->stop();
        correctFramePosition();
    }
    mythread->exit();
//    thread()->exit();
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setMaximum(0);
    int sliderScaleVal = 0;
    switch(mode)
    {
        case 0:
                {
                    sliderScaleVal = timeCells[column].endTime- timeCells[column].beginTime;
                    ////qDebug() << column;
                    ////qDebug() <<  timeCells[column].beginTime;
                    ////qDebug() <<  timeCells[column].endTime;
                    ////qDebug() << "sliderscaleval0" << sliderScaleVal;
                    break;
                }
        default:
                {
                    vplayer->stop();
                    correctFramePosition();
                    vplayer2->stop();
                    correctFramePosition();
                    sliderScaleVal = timeCells[column].endTime- timeCells[column].beginTime;
                    ////qDebug() << column;
                    ////qDebug() <<  timeCells[column].beginTime;
                    ////qDebug() <<  timeCells[column].endTime;
                    ////qDebug() << "sliderscaleval default" << sliderScaleVal;
                    break;
                }
    }



        ui->horizontalSlider->setMaximum(sliderScaleVal);
//        ////qDebug() << "sliderscaleval at createFakeTimeScale" << sliderScaleVal;
//        int sliderPageCount = 100;
//        if (sliderScaleVal < sliderPageCount)
//            sliderPageCount = sliderScaleVal;
//         ////qDebug() << "entering createfaketimescale function";
//        ui->horizontalSlider->setPageStep(sliderScaleVal/sliderPageCount);
//        timer->start();
        mythread->start();
        ////qDebug() << "mythread started";

//        thread()->exit();
//        ////qDebug() <<"exiting createfaketimescale func its sliderscaleval" <<sliderScaleVal;
        correctFramePosition();
    return 0;
}

int MainWindow::initSmallThermos(int qty, QVector <QString> names, QVector <long> maxs,QVector <int> dataSequence)
{
    QHBoxLayout thermoLayout[4];
    ////qDebug() << "Quantity" << dataSequence.count();
    ////qDebug() << dataSequence;
    int doubleCounter=0, flagCounter=0;
    for(int i = 0; i < dataSequence.count(); i++)
    {
        switch(dataSequence[i])
        {

            case 34:
            {
              //  parameterBar.insert(i,new QwtThermo(this));
                parameterBar.insert(doubleCounter,new QwtThermo(0));
                parameterBar[doubleCounter]->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
                if(maxs[doubleCounter]>0)
                    parameterBar[doubleCounter]->setMaxValue(maxs[doubleCounter]);
                else
                    parameterBar[doubleCounter]->setMaxValue(32);
                QLabel *tmptext = new QLabel(names[i]);
        //        thermoLayout[i%4].addWidget(&tmptext);
        //        thermoLayout[i%4].addWidget(parameterBar[i]);
                thermoVals.append(new QLineEdit("0"));

                QRect tmpG = thermoVals.at(doubleCounter)->geometry();
                tmpG.setWidth(10);
                thermoVals.at(doubleCounter)->setBaseSize(10,5);
                thermoVals.at(doubleCounter)->setFrame(false);
                thermoVals.at(doubleCounter)->setGeometry(tmpG);
                thermoVals.at(doubleCounter)->setEnabled(false);
                thermoVals[doubleCounter]->setPalette(ui->tableWidget_3->palette());
        //        thermoVals.at(i)->setText("0");
                thermoVals.at(doubleCounter)->installEventFilter(this);
        //        thermoVals.at(i)->setParent(this);
                ui->gridLayout_2->addWidget(parameterBar[doubleCounter],2*(int)(i/4)+1,i%4,Qt::AlignLeft);

                ui->gridLayout_2->addWidget(tmptext,2*(int)(i/4),i%4, Qt::AlignLeft);
                ui->gridLayout_2->addWidget(thermoVals[doubleCounter],2*(int)(i/4),i%4, Qt::AlignRight);
        //        parameterBar[i] = new QwtThermo(this);
        //        parameterBar.insert(i,parameterBar[i]);
        //        ui->verticalLayout_3->addWidget(parameterBar[i],0,0);
        //        parameterBar[i].setParent(ui->verticalLayout_3);
                doubleCounter++;
                break;
            }
            case 8:
            {
            //  parameterBar.insert(i,new QwtThermo(this));
//            parameterBar.insert(i,new QCheckBox(names[i]));
//              parameterBar[i]->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
//              if(maxs[i]>0)
//                  parameterBar[i]->setMaxValue(maxs[i]);
//              else
//                  parameterBar[i]->setMaxValue(2000);
//              QLabel *tmptext = new QLabel(names[i]);
//      //        thermoLayout[i%4].addWidget(&tmptext);
//      //        thermoLayout[i%4].addWidget(parameterBar[i]);
//              thermoVals.append(new QLineEdit("0"));

//              QRect tmpG = thermoVals.at(i)->geometry();
//              tmpG.setWidth(10);
//              thermoVals.at(i)->setBaseSize(10,5);
//              thermoVals.at(i)->setFrame(false);
//              thermoVals.at(i)->setGeometry(tmpG);
//              thermoVals.at(i)->setEnabled(false);
//      //        thermoVals.at(i)->setText("0");
//              thermoVals.at(i)->installEventFilter(this);
      //        thermoVals.at(i)->setParent(this);
            checkBoxes.insert(flagCounter,new QCheckBox(names[i]));
            checkBoxes[flagCounter]->setEnabled(false);
            checkBoxes[flagCounter]->setStyleSheet("QCheckBox::disabled{color:black;}""QCheckBox::indicator:checked:disabled{background: black;}""QCheckBox::indicator:unchecked:disabled{border: 1px solid black;}");
//                                                   "QCheckBox::indicator:checked:disabled{background-color: qradialgradient(cx:0.5, cy:0.5, fx:0.25, fy:0.15, radius:0.3, stop:0 #BBBBBB, stop:1 #444444);}");
            ////qDebug() << "palette!!!!!!!!!!!!!!!!!";
//            ////qDebug() << checkBoxes[flagCounter]->palette();

//            checkBoxes[flagCounter]->setCheckable(false);
            ui->gridLayout_2->addWidget(checkBoxes[flagCounter],2*(int)(i/4)+1,i%4,Qt::AlignLeft);
//              ui->gridLayout_2->addWidget(tmptext,2*(int)(i/4),i%4, Qt::AlignLeft);
//              ui->gridLayout_2->addWidget(thermoVals[i],2*(int)(i/4),i%4, Qt::AlignRight);
      //        parameterBar[i] = new QwtThermo(this);
      //        parameterBar.insert(i,parameterBar[i]);
      //        ui->verticalLayout_3->addWidget(parameterBar[i],0,0);
      //        parameterBar[i].setParent(ui->verticalLayout_3);
            flagCounter++;
            }
            default:
                break;
        }
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
    //////////qDebug()() << currentdir;
    //////////qDebug()() << path;
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
    //////////qDebug()() << currentdir;
    //////////qDebug()() << path;
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
    //////////qDebug()() << currentdir;
    QFile *conf = new QFile;
    conf->setFileName(currentdir);
    if(conf->open(QIODevice::ReadWrite))
    {
        retstr->append(QTextCodec::codecForLocale()->toUnicode(conf->readAll()));//необходимо представление стринга в юникоде, иначе QDir не понимает
        //////////qDebug()() << retstr;
        conf->close();
        return 0;
    }
    else
        //////////qDebug()() << "NULL";
        conf->close();
        return 1;
}

int MainWindow::openVideoConfigFile(QString *retstr)
{

    retstr->clear();
    QString currentdir = QApplication::applicationDirPath()+"/videoconfig";
    //////////qDebug()() << currentdir;
    QFile *conf = new QFile;
    conf->setFileName(currentdir);
    if(conf->open(QIODevice::ReadWrite))
    {
        retstr->append(QTextCodec::codecForLocale()->toUnicode(conf->readAll()));//необходимо представление стринга в юникоде, иначе QDir не понимает
        //////////qDebug()() << retstr;
        conf->close();
        return 0;
    }
    else
        //////////qDebug()() << "NULL";
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

    if(accepted)
    {
        QString videodir = logWorkingDir;

    //    ////////qDebug()() << checkVideoFilesExistance(videoWorkingDir);
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
             ////////qDebug()() << videoWorkingDir;
    //         ui->lineEdit->setText(videoWorkingDir);
    //         ui->lineEdit_2->setText(videoWorkingDir);
    //         logCheck->setChecked(true);
    //         videoCheck->setChecked(true);
             openVideoFilesFolder(&videoList);
             openLogFilesFolder(&logList);
             isFolderOpened = true;
             ////////qDebug()() << videoList;
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

        qDebug() << index;
        qDebug() << name;
        name.remove(0,index+1);
//        name.chop(name.length() - index);
        qDebug() << name;
        date = QDate::fromString(name,"yyyy.MM.dd");

        index = name.indexOf("/");
    }

    if((date.isValid())&&(!date.isNull()))
    {
        qDebug() << date;
        return 0;
    }
    else
    {

        qDebug() << "error!!!!!!!!!!!!!1111";
        return 1;
    }

}

void MainWindow::selectLogFolder()
{
    QString logdir = "";
    QFileDialog dlg;//(this, tr("Выбор директории файлов регистратора"));
//    dlg.setOption(QFileDialog::ShowDirsOnly,true);
    logdir = dlg.getExistingDirectory(this, tr("Выбор директории лог-файлов"),QDir::homePath());
//    ////qDebug() << "logdir" << logdir;
//            ::getExistingDirectory(this, tr("Выбор директории лог-файлов"),QDir::homePath());
    if((logdir!= "")&&(checkFolderName(logdir)==0))
    {
        if(logdir!=logWorkingDir)
        {
            if(isFolderOpened)
                terminateAll();
            accepted = true;
            //logdir = dlg.getExistingDirectory(this, tr("Выбор директории лог-файлов"),QDir::homePath());
//            if(checkFolderName(logdir)==1);
//            {
//                accepted = false;
//                LogFileError = 2;

//            }
//            else
//            {
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
                    ////////qDebug()() << logWorkingDir;
            //        ui->lineEdit_2->setText(logWorkingDir);
            //        ui->lineEdit->setText(logWorkingDir);
            //        logCheck->setChecked(true);
            //        videoCheck->setChecked(true);
                    LogFileError = 0;
                    isFolderOpened = true;
                }
                if((VideoFileError==0)&(LogFileError==0))
                {
                    setButtonPanelEnabled(true);

                }
//            }
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
//            ////////qDebug()() << list.at(i).indexOf(".alg");
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
//            ////////qDebug()() << list.at(i).indexOf(".avi");
            aviCounter++;
        }

    }
    return aviCounter;
}

void MainWindow::getTimeTimerTick()
{
//    getTimeTickCounter++;
    delayMs++;
    realSecondsCounter++;
//   //////qDebug() << "tick";
//    getTimeTimer->start(1);

}

//work with files
void MainWindow::updateTime()//i don't like this func
{
//    delayMs = 0;
//    mythread->start();
//    mutex.lock();
//    ////qDebug() << "delayms at settime" << delayMs;

    ui->timeEdit->setTime(QDateTime::fromTime_t(timeCells[ui->tableWidget->currentColumn()].beginTime+delayMs/100).toUTC().time());
    tickCounter++;
    if((ui->horizontalSlider->value()>=ui->horizontalSlider->maximum())&(ui->horizontalSlider->maximum()>0))//&(value!=lastVal))
    {
        if((!isSliderPressed)&(!seekerIsBusy))
        {
            //qDebug() << seekerIsBusy;
//            ui->horizontalSlider->setEnabled(false);
            ui->horizontalSlider->setValue(0);
//            ui->horizontalSlider->releaseMouse();
//            ui->horizontalSlider->blockSignals(true);
//            ////qDebug() << "get next segment here" << delayMs;
            //qDebug() <<"timeCellIndex" <<timeCellIndex;
            moveToNextTimeFrame();
            ui->horizontalSlider->setEnabled(true);
        }
        else
        {
            ////qDebug() << "delay" << delayMs;
        }
    }
//    ////qDebug()<<"inverseTime"<<inverseTime;
    if(!videoOnly)
        delayMs++;
    if(delayMs >= maxCamOffset)
    {

    }
    //////qDebug() << delayMs;
    int currentDelayMs = delayMs;
    if(currentDelayMs%100==0)//second passed
    {

        if(timeCellIndex!=ui->tableWidget->currentColumn())
        {
            //qDebug() << "timeCellIndex" << timeCellIndex;
            ////qDebug() << "column" << ui->tableWidget->currentColumn();
            int tmpval = ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();//-ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn());
            ////qDebug() << "global coords2" << tmpval;
//            canMoveSeeker = true;
            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
            ////qDebug() << "totaltime";
//            int currentPos = mouseEvent->x();//delayMs/100;
            getDelayMsToSet(tmpval,totalTime);
            delayMs = delayMsToSet;\
            ui->horizontalSlider->setValue(delayMs/100);
            setSliderPosition();
//            updateTime();
//            delayMs = delayMsToSet;\
       //     delayMsToSet = 0;
            updateTime();
//            ////qDebug() << "delayMs"<<delayMs;

//            moveToAnotherTimeSegment(ui->tableWidget->currentColumn());
//            ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn());

//            moveToAnotherTimeSegment(ui->tableWidget->currentColumn());
//            if(mythread->isFinished())
//                mythread->start();

        }
        ui->horizontalSlider->setValue((int)currentDelayMs/100);
        tickCounter=0;
        int pos = ((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->tableWidget->width();
       // ////qDebug() << "pos on updatetime100" << pos;
        //qDebug() << "v5";
        correctCellSeekerPosition(pos);
        if(!videoOnly)
        {
            dataParams *tmpDP = new dataParams;
            lastRecNum = getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)currentDelayMs/100,0,0);
            makeStructFromRecord(log->record,tmpDP);
            updateThermos(*tmpDP);
        }

//        ////qDebug() << delayMs;

    }
    else if(currentDelayMs%10==0)
    {
//        ////qDebug() <<"table" <<ui->tableWidget->currentColumn();
//        ////qDebug() <<"cell type" <<timeCells[ui->tableWidget->currentColumn()].cellType;
//        ////qDebug() <<"currentPage" <<timeCells[ui->tableWidget->currentColumn()].currentPage;
//        ////qDebug() <<"pageindex" << pageIndex;
        correctFramePosition();
        //if(ui->tableWidget->currentColumn()==ui->tableWidget->columnCount()-1)
//        ////qDebug() << "pos3";
        int pos = ((float)(delayMs/100)/(timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime))*ui->tableWidget->width();
//        ////qDebug() << timeCells[timeCells.size()-1].endTime << timeCells[0].beginTime <<ui->tableWidget->width()<<delayMs;
//        ////qDebug() << "sliderlength"<<ui->horizontalSlider->maximum();
//        ////qDebug() << "pos on updatetime10" << pos;
        //qDebug() << "v4";
        correctCellSeekerPosition(pos);
        if(!videoOnly)
        {
            dataParams *tmpDP = new dataParams;
            ui->horizontalSlider->setValue((int)currentDelayMs/100);
            if(ui->horizontalSlider->value()==0)
                lastRecNum = getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)currentDelayMs/100,/*beginTimeFract*/0,0);//we need to define timeFract here
            else
                lastRecNum = getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)currentDelayMs/100,(int)((currentDelayMs%100)*2.56),0);//we need to define timeFract here
    //        //////qDebug() <<"current timefract" << delayMs%100;
            makeStructFromRecord(log->record,tmpDP);
            updateThermos(*tmpDP);

        }
    }
    if(videoOnly)
    {
      ui->horizontalSlider->setValue((int)currentDelayMs);
    }

//    mutex.unlock();
}

int MainWindow::updateThermos(dataParams dp)
{
//    ////////qDebug()() << "doubleTypes size" << dp.doubleTypes.size();
//    ////qDebug() << "update thermos";
//    ////qDebug() << "doubleTypes" << dp.doubleTypes.size();
//    ////qDebug() << "flagTypes" << dp.flagTypes.size();
//    ////qDebug() << dp.doubleTypes;
//    ////qDebug() << dp.flagTypes;
//    ////qDebug() << dp.paramsSequence;

 //  ////qDebug() << dp;
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
//                thermoVals[doubleCounter]->setUpdatesEnabled(true);
                thermoVals[doubleCounter]->setText(QString::number(dp.doubleTypes[doubleCounter],10,2));
//                thermoVals[doubleCounter]->setUpdatesEnabled(false);
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
//                checkBoxes[flagCounter]->setCheckable(true);
                checkBoxes[flagCounter]->setChecked(dp.flagTypes[flagCounter]);
//                checkBoxes[flagCounter]->setCheckable(false);
                //parameterBar[i]->setValue(db);
                //thermoVals[i]->setText(tmp);
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
   // char rec[100];
//    log->selectLogFile()
//    ////qDebug() << log->getLogFileName();
//    ////qDebug()<< QDateTime::fromTime_t(currentTime);
//    ////qDebug() << "current time" << currentTime;
  //  ////qDebug() << QDateTime::fromTime_t(currentTime);
//     ////qDebug() << QDateTime::fromTime_t(currentTime).toUTC();
   // ////qDebug() << "current UTC time" << currentTime;
//    ////qDebug() << "inverse time" << inverseTime;
//    ////qDebug() << "last record" << lastRecord;
//     currentTime = currentTime - 14400;
    long tmpErr = log->selectSegment(bigTableID);
    int recIndex=0;
    bool timeFractSearchFlag = false;
    time_t recTime;
    time_t beforeTime;
    ////////qDebug()() << QDateTime::fromTime_t(currentTime);
    ////////qDebug()() << inverseTime;
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
//                         if(interpreter->TInterpItemArray[i].level)
                         {

                             switch(interpreter->TInterpItemArray[i].typ&0xffff)
                             {
                             case 10 :
                             {
                                 recTime = (time_t)interpreter->fieldInt(&log->record[recIndex]);
//                                 recTime = mktime(gmtime(&recTime));

                                 if(interpreter->TInterpItemArray[i].name!="PowOnTime")
                                 {
                                     //check time going direction
                                     if(currentTime==recTime)
                                     {
                                         beforeTime = recTime;
//                                         ////qDebug()<< QDateTime::fromTime_t(recTime);
                                         timeFractSearchFlag = true;//set flag of searching timefract

                                     }
                                     else
                                     {
                                         if(inverseTime)
                                         {
                                            if(currentTime>recTime)
                                            {
//                                                ////qDebug() << "out index"<<index;
                                                 return index;
                                            }

                                         }
                                         else
                                         {

                                             if(currentTime<recTime)
                                             {
//                                                 ////qDebug() << "out index"<<index;
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
                                        ////////qDebug()() << (int)tmpTimeFract;
                                        ////////qDebug()() << timeFract;
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
                                // ////qDebug() << QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
                                 break;
                             }
                             }
                         }
                     }
                 }
        }
//        ////qDebug() << QDateTime::fromTime_t(recTime).toUTC();
    }

    return -1;
}

int MainWindow::readCamOffsetsAndTimeEdges(time_t *beginTime, time_t *endTime, unsigned char *beginTimeFract, unsigned char *endTimeFract,int globalIterator)
{
//    ////qDebug() << "WTF?";
//    logEndTimes.clear();
    int tmpErr = log->selectSegment(camOffsetsTableID);
//    ////qDebug() << "WTF??!";
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
//                ////qDebug() << "WTF??";

                for(int i =0; i <interpreter->interpreterRecordsCount; i++)
                {
//                    ////qDebug() << "name" << i << interpreter->TInterpItemArray[i].name;
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
//                            QPalette pal = camBtn.camButton->palette();
//                            pal.setColor(Qt::Widget,Qt::ForegroundRole);
//                            camBtn.camButton->setPalette(pal);
//                            camButtons1.append({QPushButton::QPushButton(ui->widget_3),false,false});

                            camButtonsLayout1->addWidget(camBtn1.camButton,counter/5,counter%5+1);
                            camButtonsLayout2->addWidget(camBtn2.camButton,counter/5,counter%5+1);
                            qDebug() << "i%5"<< counter%5 << counter;
                            camButtons1.append(camBtn1);
                            camButtons2.append(camBtn2);
                            camButtons1[counter].camButton->setObjectName("camBtn1"+QString::number(counter+1,10));
                            camButtons2[counter].camButton->setObjectName("camBtn2"+QString::number(counter+1,10));
                            connect(camButtons1[counter].camButton,SIGNAL(clicked()),this,SLOT(pushCameraButton()));
                            connect(camButtons2[counter].camButton,SIGNAL(clicked()),this,SLOT(pushCameraButton()));
//                            camButtonsLayout1->addWidget(camButtons1[i].camButton,i/5,i%5);
//                            ui->gridLayout->addWidget(camButtons1[i].camButton,i/5,i%5);
//                            qDebug() << camOffsets.at(i);
//                            ////qDebug() << "current index i " << i;
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
                            QString tmpField = " ";
                            int tmpRecI = 0;
                            QVariant recFloat;
                            log->readRecord(log->segmentHeader.recordSize, log->segmentHeader.size, log->logDataPointer);
                            for (int i = 0; i < interpreter->interpreterRecordsCount; i++)
                            {
                                tmpRecI=interpreter->TInterpItemArray[i].offset;

                                if(interpreter->TInterpItemArray[i].typ==4)
                                {

                                    long tmpVal = interpreter->fieldInt(&log->record[tmpRecI]);
                                            ////////qDebug()() << tmpVal;
                                    QString tmp = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
//                                    ////qDebug() << tmp;
//                                    if(tmp=="time"||tmp=="Time")
//                                    {
//                                        *beginTime = (time_t)tmpVal;
//                                        //////qDebug() << QDateTime::fromTime_t(*beginTime);
//                                    }
//                                    else
                                        camOffsets.append(tmpVal);
                                        camoffsetscounter++;
                                }
                                if(interpreter->TInterpItemArray[i].typ==3)
                                {
                                   unsigned short tmpVal = interpreter->fieldShort(&log->record[tmpRecI]);
//                                            //////qDebug() << tmpVal;
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
//                                    camOffsets.append(tmpVal);
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
                                             ////qDebug() << QDateTime::fromTime_t((time_t)tmpVal);       //we need here something like global variable StartTime
                                    }
                                    if(timeIndex==2)
                                    {
                                             ////qDebug() << QDateTime::fromTime_t((time_t)tmpVal);      //we need here something like global variable ShutDownTime
                                    }

                                    timeIndex++;
//                                    camOffsets.append(tmpVal);
                                }

                            }

                            if(createFullListOfVideos(camoffsetscounter)==0)
                            {
                                for(int k = 0; k< videoList.size(); k++)
                                {
                                    ////qDebug() << videoList.at(k);
                                }
                            }
//                            ////qDebug() << "camOffsets" << camOffsets.size();
//                            ////qDebug() << "size of video list" << videoList.size();
                            vplayer->stop();
                            QFile filetocheck;
//                            ////qDebug() << "some size from here" << filetocheck.fileName();
//                            if(globalIterator ==logList.size()-1)
//                            {
//                                int tmpMax = 0,currentval=0;
//                                short tmp = 0;
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
                                            QString str="Камера ";
//                                            vplayer->showText(str.append(QString::number(ui->comboBox->currentIndex(),10)),1000,50,1000);
                                            currentval = (vplayer->_player->length()+camOffsets.at(j))/1000;
                                            tmp = (timeFracts.at(timeFracts.size()-1)+vplayer->_player->length()+camOffsets.at(globalIterator*camoffsetscounter+j))%1000;
                                        }
                                        else
                                        {
                                            currentval = 0;
                                            tmp = 0;
                                        }
                                        videoTimes.append(currentval);
//                                        ////qDebug() << "video time"<<currentval;
                                        timeFracts.append(tmp);
                                        vplayer->stop();
                                        correctFramePosition();
                                    }
                                        else
                                        videoTimes.append(0);
//                                    else
//                                    {
//                                        timeFracts.append(0);
//                                    }

//                                    //////qDebug() << "second time fract"<<tmp;

                                }

//                                *endTime = *beginTime + (time_t)tmpMax;
//                            }
//                            else
//                            {
//                                *endTime = *beginTime;
//                                timeFracts.append(0);
//                            }
                            time_t timeFromBigTable1,timeFromBigTable2;
                            readTimeEdges(&timeFromBigTable1,&timeFromBigTable2);

//                            ////qDebug() << QDateTime::fromTime_t(timeFromBigTable1);
//                            ////qDebug() << QDateTime::fromTime_t(timeFromBigTable2);
                            *endTime = *beginTime;
                            logEndTimes.append(timeFromBigTable2);
                            offsetsCounter.append(camoffsetscounter);
//                            if(filetocheck.size()>10000)
//                            {
//                                vplayer->openLocal(videoWorkingDir+"/"+videoList.at(globalIterator*camoffsetscounter));
////                            obj.setObjectName(videoWorkingDir+"/"+videoList.at(globalIterator*camOffsets.size()));
//                                *endTime = *beginTime + (time_t)(vplayer->_player->length()+camOffsets.at(camoffsetscounter-1))/1000;
//                                ////qDebug() << *beginTime;
//                                short tmp = (timeFracts.at(timeFracts.size()-1)+vplayer->_player->length()+camOffsets.at(globalIterator*camoffsetscounter))%1000;
//                                //////qDebug() << "second time fract"<<tmp;
//                                timeFracts.append(tmp);
//                                //////qDebug() << QDateTime::fromTime_t(*endTime);
//                                //////qDebug() << vplayer->_player->length()/1000;
//                                vplayer->stop();
//                            }
//                            else
//                            {
//                                *endTime = *beginTime + (time_t)(vplayer->_player->length()+camOffsets.at(globalIterator*camoffsetscounter))/1000;
//                                timeFracts.append(0);
//                            }
    }
//////qDebug() << "now we have offsets";
    camButtonsLayout1->addWidget(ui->screen1SoundButton,0,0);
    ui->screen1SoundButton->setVisible(true);
    camButtonsLayout2->addWidget(ui->screen2SoundButton,0,0);
    ui->screen2SoundButton->setVisible(true);

    return tmpErr;

}

void MainWindow::setCameraButtonsToDefault()
{
    bool firstNotZeroCamNumber=false;//flag that shows if the first
//    if(timeCells[0].cellType==0)|
    {
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
    int camindex;
    QString tmpindex,tmpparent;
    QPushButton *tmpbtn = (QPushButton *)QObject::sender();
    tmpbtn->clearFocus();
    tmpindex = QObject::sender()->objectName().toLocal8Bit();
    qDebug()<< tmpindex.at(7);
    camindex = (int)tmpindex.at(7).toLatin1();
    qDebug() << QObject::sender()->objectName().toLocal8Bit();
    qDebug() << QObject::sender()->parent()->objectName();
    qDebug() << "some button pushed";
    if(QObject::sender()->parent()->objectName()=="widget_3")
    {
        if(updateCameraButtons1(camindex-0x30))//if 1 need change cameras, else not
            setCamera1(camindex-0x30);
    }
    if(QObject::sender()->parent()->objectName()=="widget_4")
    {
        if(updateCameraButtons2(camindex-0x30))//if 1 need change cameras, else not
            setCamera2(camindex-0x30);
    }
}

void MainWindow::setCamera1(int index)
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
//        if(index==activeIndex)
//        {
//            if(index==ui->comboBox->count()-1)
//                ui->comboBox->setCurrentIndex(index-1);
//            else
//                ui->comboBox->setCurrentIndex(index+1);
//        }
        if(isVideo1Opened|isVideo2Opened)
        {
                int tmptime = vplayer->getCurrentTime()+camOffsets.at(lastIndex1-1)-camOffsets.at(index-1);
                while(tmp1<=activeIndex)
                {
                    Iter1.next();
                    tmp1++;
                }
                if(vplayer2->getVideoState()==4)
                    vplayer2->togglePause();
                vplayer->openLocal(videoWorkingDir+"/"+Iter1.key());
                showCameraNameTimer->start(200);
                isVideo1Opened = true;
                vplayer->_player->setTime(tmptime);
                if(mythread->isRunning())
                    mythread->exit();
        }
        lastIndex1 =index;
        sound1IconState = vplayer->getAudioIconState();
        sound2IconState = vplayer2->getAudioIconState();
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

void MainWindow::setCamera2(int index)
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

            int tmptime = vplayer2->getCurrentTime()+camOffsets.at(lastIndex1-1)-camOffsets.at(index-1);//!!
                 while(tmp2<=activeIndex)
                {
                    Iter2.next();
                    tmp2++;
                }
                if(vplayer->getVideoState()==4)
                    vplayer->togglePause();
            vplayer2->openLocal(videoWorkingDir+"/"+Iter2.key());
            showCameraNameTimer->start(200);
//            QString str="Камера ";
//            vplayer2->showText(str.append(QString::number(ui->comboBox_2->currentIndex(),10)),1000,50,1000);

            isVideo2Opened = true;
            vplayer2->_player->setTime(tmptime);
            if(mythread->isRunning())
                mythread->exit();
                if(mythread->isRunning())
                    mythread->exit();
                sound1IconState = vplayer->getAudioIconState();
                sound2IconState = vplayer2->getAudioIconState();
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
//                setSoundIcons();
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
    //////qDebug() << "reading time edges";
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
            ////////qDebug()() <<"количество записей"<< tmpRecordCount;
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
                         ////qDebug()<< "typ" << (interpreter->TInterpItemArray[i].typ&0xffff) ;
                         ////qDebug() << "name" << interpreter->TInterpItemArray[i].name;
                         recIndex=interpreter->TInterpItemArray[i].offset;
                         if(interpreter->TInterpItemArray[i].level)
                         {

                             switch(interpreter->TInterpItemArray[i].typ&0xffff)
                             {
                             case 10 :
                             {
                                 recTime = (time_t)interpreter->fieldInt(&log->record[recIndex]);
//                                 ////qDebug() << "LOG TIME EDGES" << QDateTime::fromTime_t(recTime).toUTC();
//                                 recTime = mktime(gmtime(&recTime));
//                                 ////qDebug() << "LOG TIME EDGES" << QDateTime::fromTime_t(recTime).toUTC();
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
//                             case 0:
//                             {

//                                     unsigned char tmpTimeFract;

//                                        tmpTimeFract = interpreter->fieldChar(&log->record[recIndex]);
//                                        ////////qDebug()() << (int)tmpTimeFract;
//                                        if(index==0)
//                                            *beginTimeFract = tmpTimeFract;
//                                        else
//                                            *endTimeFract = tmpTimeFract;


//                             }


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
    ui->progressBar->setVisible(true);
    correctFramePosition();
    ui->mainToolBar->setEnabled(false);
    ui->progressBar->setValue(0);
    listOfLogs->clear();
    //////qDebug() << "listOfLogs";
    QString pathToFileDir = logWorkingDir;
    QDir filesDir(pathToFileDir);
    //////////qDebug()() << filesDir.path();
    if(!filesDir.exists())
        return 1;
    filesDir.setSorting(QDir::Time);
    ////////qDebug()() << filesDir.entryList();
    //////////qDebug()() << filesDir.entryList().at(2);
    ///    QDir filesDir(path);
    QStringList list;
    int algCounter = 0;
    list = filesDir.entryList(QDir::Files,QDir::Type);
    ui->progressBar->setMaximum(list.size()-1);

    for(int i = 0; i<list.size() ; i++)
    {
        if(list.at(i).indexOf(".alg")!=-1)
        {
//            ////////qDebug()() << list.at(i).indexOf(".alg");
            algCounter++;
            listOfLogs->append(list.at(i));
        }
        ui->progressBar->setValue(i);
    }
    ui->progressBar->setVisible(false);
    correctFramePosition();
    ui->mainToolBar->setEnabled(true);
//    //////qDebug() << listOfLogs;

    return 0;
}

int MainWindow::openVideoFilesFolder(QStringList *listOfVideos)
{
//    QFile fileToOpen;
    listOfVideos->clear();
    ui->mainToolBar->setEnabled(false);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setVisible(true);
    correctFramePosition();
    ui->progressBar->setValue(0);
    QString pathToFileDir = videoWorkingDir;
    ////////qDebug()() << videoWorkingDir;
    QDir filesDir(pathToFileDir);
    //////////qDebug()() << filesDir.path();
    if(!filesDir.exists())
        return 1;
    filesDir.setSorting(QDir::Time|QDir::Reversed);
//    filesDir.setSorting(QDir::Reversed);
    //////////qDebug()() << filesDir.entryList();
    //////////qDebug()() << filesDir.entryList().at(2);
//    listOfVideos->append(filesDir.entryList(QDir::Files));

     ui->progressBar->setMaximum(filesDir.entryList(QDir::Files).size()-1);
    for(int i = 0; i < filesDir.entryList(QDir::Files).size(); i++)
    {
//        this->update();
        if(filesDir.entryList(QDir::Files).at(i).indexOf(".mkv")!=-1)
            listOfVideos->append(filesDir.entryList(QDir::Files).at(i));
        ui->progressBar->setValue(i);
        ui->progressBar->update();
//        this->update();
//        //////qDebug() << "value" << i;

    }

//    QStringList *tmpVideos = new QStringList;
//    tmpVideos->append(listOfVideos);
//    listOfVideos->clear();
//    ////////qDebug()() << "videolist" << listOfVideos;

    qSort(listOfVideos->begin(),listOfVideos->end());
    for (int i =0; i < listOfVideos->size(); i++)
        //////qDebug() << listOfVideos->at(i);
//    ////////qDebug()() << "sortedlist" << listOfVideos;
    ui->progressBar->setVisible(false);
    correctFramePosition();
    ui->mainToolBar->setEnabled(true);
    return 0;
}

int MainWindow::openLogFile(QString filename)
{

    QString selectedLogFilePath;
//    int logIndex=-1;
//    selectedLogFilePath.clear();
//    QString fileFirstName = "";
//    filename.chop(4);//6 for video files
//    //////qDebug() << "opening log file" << filename;
//    //////qDebug() <<"size in openLogFile" <<logList.size();
//    for(int i =0; i < logList.size(); i++)
//    {
//        fileFirstName.append(logList.at(i));
//        fileFirstName.chop(4);
//        if(fileFirstName==filename)
//           logIndex = i;
//        fileFirstName.clear();
//    }
//    if(logIndex!=-1)
//    {
//        ////qDebug() << "trying to open file" << filename;

        selectedLogFilePath = logWorkingDir+"/"+filename;//logList.at(logIndex);
        ////////qDebug()() << selectedLogFilePath;
      //  ////////qDebug()() << log->selectLogFile(selectedLogFilePath);
        int logfilesize = log->selectLogFile(selectedLogFilePath);
        ////qDebug() <<"bytes in logfile" << logfilesize;
        checkFileHeaderCRC(selectedLogFilePath);
    //   //////qDebug() << logList.at(logIndex);
    //    openedFileIndex = logIndex;
        tickCounter = 1;
//        timer->start(mainTimerInterval);
        getTimeTimer->start(1);


    //    thrd = new MyThread;
    //    thrd->setTimerInterval(25);
    //    connect(thrd,SIGNAL(tick()),this,SLOT(getTimeTimerTick())); //it works too
       // checkFileHeaderCRC(selectedLogFilePath);
        //////qDebug()<< "ok";
        videoOnly = false;
//         //////qDebug() <<"size in openLogFile 2" <<logList.size();
//        ////qDebug() << "quiting openlogfile action";
        return 0;
//    }
//    else
//    {
//        newMessage.setWindowTitle("Внимание!");
//        newMessage.setText("Логфайла, соответствующего данному видео файлу нет в указанной папке, воспроизведение видео продолжится, но параметры системы отображаться не будут.");
//        newMessage.exec();
//        //////qDebug()<< "wrong";
//        videoOnly = true;
////         //////qDebug() <<"size in openLogFile 3" <<logList.size();
//        return -1;
//    }


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

//    int tmpSegCount = newLogProc->getSegmentsCount();
//    ////////qDebug()() << "segments count" << tmpSegCount;
//    newLogProc->checkSegmentsExistance();
//    newLogProc->readFileHeader();

    log->selectLogFile(filename);
    int maxSegCount = log->getSegmentsCount();
    log->checkSegmentsExistance();
    log->readFileHeader();
    ////////qDebug()() << "maxSegCount" << maxSegCount;
    ////////qDebug()() << log->fileHeader.fileSize;
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
        ////////qDebug()() << tmpID;
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
        //////////qDebug() << log->segIDs[i];
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
//                char* buffArr1 = (char*)malloc(log->segmentHeader.size);
                //////////qDebug()() << log->segmentHeader.size;
                log->readSegment(buffArr1, log->segmentHeader.size );
                interpreter->interpreterRecordsCount=log->segmentHeader.size/log->segmentHeader.recordSize;
                interpreter->setInterpretationTable(buffArr1,interpreter->interpreterRecordsCount);
                int index=0;
                for(int i =0; i <interpreter->interpreterRecordsCount; i++)
                {

//                    ////qDebug() << "name1" << i << interpreter->TInterpItemArray[i].name;
                    if(interpreter->TInterpItemArray[i].level!=0)
                    {
//                            verticalHeaderName = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
//                            ui->tableWidget->verticalHeaderItem(i-1)->setText(verticalHeaderName);

                        int col1 = 0;
//                        int col2 = 1;
                        //////////qDebug()()<< QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);
                        parname = QString::fromLocal8Bit(interpreter->TInterpItemArray[i].name);//QTextCodec::codecForLocale()->toUnicode(interpreter->TInterpItemArray[i].name);
                        QLabel *labe1 = new QLabel(parname);
                        //////////qDebug()() << parname;
                        labe1->setAlignment(Qt::AlignCenter);
//                        labe1->text().append(parname);
//                        QLabel *labe2 = new QLabel("textBlock2");
                        ui->tableWidget_2->setCellWidget(index/2,col1+(index%2)*2,labe1);

//                        ui->label_3->text().clear();
//                        ui->label_3->text().append(parname);
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
                                                //////////qDebug()() << interpreter->TInterpItemArray[i].name;
//                                                //////////qDebug()() << tmpDbl;
                                                QVariant tmpVal = tmpDbl;
                                                tmpField = tmpVal.toByteArray();
                                                //////////qDebug()() << interpreter->TInterpItemArray[i].mask_;
                                                //////////qDebug() << tmpDbl;
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
//                                                ////qDebug() << "is it default??";
                                                tmpInt = interpreter->fieldInt(&log->record[recIndex]);
                                                QVariant tmpVal = tmpInt;
                                                tmpField = tmpVal.toByteArray();
                                                ////qDebug() <<"PREPARE TO BEHOLD SOMETHING: " <<tmpField;
//                                                tmpField.append("Недоступно");
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
//                                    ////qDebug() << interpreter->TInterpItemArray[i].name;
                                    tmpInt = interpreter->fieldInt(&log->record[recIndex]);
                                    QVariant tmpVal = tmpInt;
                                    tmpField = tmpVal.toByteArray();
//                                    ////qDebug() <<"PREPARE TO BEHOLD SOMETHING: " <<tmpField;
                                }
                            }

    }
    else
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
        newMessage.exec();
        //////////qDebug() << "error in linguo section";
//        isOpened=false;
//        openNewMainWindow();
//        this->close();
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
//       setButtonsEnable(true);
    }
    else
    {
        ////qDebug() << "we gotta error here!";
    }
    openLogFilesFolder(&logList);
    openVideoFilesFolder(&videoList);
     qSort(logList.begin(),logList.end());
     for(int i = 0; i < logList.size(); i++)
     {
         ////qDebug() << logList.at(i);
     }
     ////qDebug() << "!!!before run start!!!";
    ui->pushButton->click();

}

void MainWindow::createCellVector()
{
//    ////qDebug() << "starting create cell vector";
    int length = dataMap.size();
    if(dataMap[dataMap.size()-1].timeEdge2 ==dataMap[dataMap.size()-1].timeEdge1)
    {
        int tmpMax=0,tmpTime=0;
        for(int a = 0; a < dataMap[dataMap.size()-1].videoTimeEdges.size();a++)
        {
            int tmpTime = dataMap[dataMap.size()-1].videoTimeEdges[a]+dataMap[dataMap.size()-1].camTimeOffsets[a]/1000;
            if(tmpMax < tmpTime)
                tmpMax = tmpTime;
        }
        dataMap[dataMap.size()-1].timeEdge2+=tmpMax;
    }
    int totalWidth = dataMap[dataMap.size()-1].timeEdge2 - dataMap[0].timeEdge1;\
//    qDebug() << "width of " << totalWidth;
//    qDebug() << QDateTime::fromTime_t(dataMap[0].timeEdge1).toUTC();
//    qDebug() << QDateTime::fromTime_t(dataMap[0].timeEdge2).toUTC();
//    qDebug() << QDateTime::fromTime_t(dataMap[dataMap.size()-1].timeEdge1).toUTC();
//    qDebug() << QDateTime::fromTime_t(dataMap[dataMap.size()-1].timeEdge2).toUTC();
//    qDebug() << dataMap[0].videoTimeEdges;
//    qDebug() << dataMap[dataMap.size()-1].videoTimeEdges;
//    ////qDebug() << "width of tablewidget"<< ui->tableWidget->width();
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    if(length!=0)
    {
//        ui->tableWidget->setEnabled(true);
//        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

//        ui->tableWidget->setColumnCount(length);
//        ui->tableWidget->horizontalHeader()->set
     //   ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        int k = 0,tmpGreenLength=0, tmpGrayLength=0, tmpWhiteLength=0,tmpTimeCell=0;

//        pageFlagVector.append(0);
      //   ui->tableWidget->setColumnCount(1);
//        ////qDebug() << "number of green bars on the tablewidget" << length;
//        pageVector.clear();
//        pageFlagVector.clear();
        tableCell tc;
        for(int i = 0; i < length; i++)
        {
//            ////qDebug() << "cycle number" << i;
            int colorcounter=0;
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
//            ////qDebug()<< "timecell" << tmpTimeCell;
            if(tmpGreenLength>tmpGrayLength)
            {
                tmpGrayLength= 0;
                if(tmpTimeCell>tmpGreenLength)
                   tmpWhiteLength  =  tmpTimeCell - tmpGreenLength;
//                tmpWhiteLength = 0;
            }
            else
            {
               tmpGrayLength = tmpGrayLength-tmpGreenLength;
               if(tmpTimeCell>(tmpGreenLength+tmpGrayLength))
                   tmpWhiteLength = tmpTimeCell - (tmpGreenLength+tmpGrayLength);
               else
                   tmpWhiteLength = 0;
            }
            ////qDebug() << "timecell"<< tmpTimeCell <<"tmpgreenlength"<< tmpGreenLength<<"tmpwhitelength"<< tmpWhiteLength<< "tmpgraylength"<< tmpGrayLength;
            bool redFlag = true;
            for(int b = 0; b < dataMap[i].camTimeOffsets.size(); b++)
            {
//                ////qDebug() << dataMap[i].videoTimeEdges.at(b);

                if((dataMap[i].camTimeOffsets.at(b)>0)&(dataMap[i].videoTimeEdges.at(b)>0))
                    redFlag = false;
                else if((dataMap[i].camTimeOffsets.at(b)==0)&(dataMap[i].videoTimeEdges.at(b)==0))
                    redFlag = false;
                else
                {
                    redFlag = true;
                    b = dataMap[i].camTimeOffsets.size();
//                    ////qDebug() << "gray length" << tmpGrayLength;
                    //////qDebug() << "gray length" << tmpGrayLength;
//                    ////qDebug() << "redflag appears";
                }

            }
            if(tmpGreenLength>0)
            {
                tc.donor = 0;
                tc.beginTime = dataMap[i].timeEdge1;
                tc.endTime = tc.beginTime+tmpGreenLength;
//                QMapIterator <QString, bool> Iter(dataMap[i].videoVector);
                float tmplength = (float)tmpGreenLength/totalWidth;
                tc.colWidth = ui->tableWidget->width()*(tmplength);
               // ////qDebug() << "redflag" << redFlag << "celltype"<< tc.cellType;
                if(!redFlag)
                    tc.cellType = 0;
                else
                    tc.cellType = 3;
                tc.relativeWidth = tmplength;
                tc.currentPage = i;
                timeCells.append(tc);
//                ////qDebug() << "green length exists" << tmpGreenLength;
                k++;

            }
            if(tmpGrayLength>1)
            {

                tc.donor = 0;
                tc.beginTime = dataMap[i].timeEdge1+tmpGreenLength;
                tc.endTime = tc.beginTime+tmpGrayLength;
                float tmplength = (float)tmpGrayLength/totalWidth;
                tc.colWidth = ui->tableWidget->width()*(tmplength);
//                ////qDebug() << "tmplength" << tmplength;
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
//                ////qDebug() << "tmplength" << tmplength;
//                if(!redFlag)
                    tc.cellType = 2;
//                else
//                    tc.cellType = 3;
                tc.relativeWidth = tmplength;
                tc.currentPage = i;
                timeCells.append(tc);
                k++;

            }
//            ////qDebug() << "circle finished";
        }
    }
    int acceptorCounts=0,donorCounts=0;
    for(int a = 0; a < timeCells.size(); a++)
    {
        ////qDebug() << "cell number" << a << "*********************************************";
        ////qDebug() << "begin time" <<timeCells[a].beginTime;
        ////qDebug() << "end time" <<timeCells[a].endTime;
        ////qDebug() << "cell type" <<timeCells[a].cellType;
        ////qDebug() << "current page" <<timeCells[a].currentPage;
        qDebug() << "relative width" <<timeCells[a].relativeWidth;
        ////qDebug() << "column width" << timeCells[a].colWidth;
        if((timeCells[a].colWidth<1)&(timeCells[a].cellType!=1))
            acceptorCounts++;
        else if(timeCells[a].colWidth>5)
        {
//            if(timeCells[a].cellType==0)
                donorCounts++;
        }
    }
//    ////qDebug() << acceptorCounts;
//    ////qDebug() << donorCounts;
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
//            ////qDebug() << "donor" << timeCells[a].donor;
        }

    }
    ////qDebug() << "creating cell vector is finished";
}

void MainWindow::on_pushButton_clicked()
{

    QVector <long> thMaxs(0);
    QVector <QString> thNames(0);
    QVector <int> seq(0);
//    logList.clear();
    //////qDebug() << "current vplayer state is" << vplayer->getVideoState();
//    pageIndex = 0;
    openLogFile(logList.at(0));
    if(timeSegment.isEmpty())
    {
        ////qDebug()<< "here!";
    }

    if(createTimeSegment(&logList))
    {
//        videoOnly = false;
//        openLogFile(videoList.at(0));

        dataMap.clear();
        videoTimeGlobalIterator=0;
        createDataMap();
//        ////qDebug() << "DATA MAP CREATED!!!";
        for(int l = 0; l < dataMap.size(); l++)
        {
            QMapIterator <QString, bool> Iter(dataMap[l].videoVector);

            ////qDebug() << dataMap[l].logName;
            ////qDebug() << dataMap[l].timeEdge1;
            ////qDebug() << dataMap[l].timeEdge2;
            ////qDebug() << dataMap[l].TimeFract1;
            ////qDebug() << dataMap[l].TimeFract2;
            for(int a = 0; a< dataMap[l].camTimeOffsets.size();a++)
            {
                ////qDebug() << dataMap[l].camTimeOffsets.at(a);

//                ////qDebug() << dataMap[l].videoVector.Iterator;
            }
            for(int a = 0; a< dataMap[l].videoTimeEdges.size();a++)
            {
                ////qDebug() << dataMap[l].videoTimeEdges.at(a);

//                ////qDebug() << dataMap[l].videoVector.Iterator;
            }
            ////qDebug() << "sizeof videoVector" << dataMap[l].videoVector.size();
            while(Iter.hasNext())
            {
                Iter.next();
                ////qDebug() << Iter.key() << Iter.value();
            }

        }
        createCellVector();
//        ////qDebug() <<"VERY BEGIN TIME" << QDateTime::fromTime_t(timeCells[0].beginTime).toUTC();
        initColoredScale();
        setCameraButtonsToDefault();
//        updateCameraButtons(0);
//        ////qDebug() << "WIDTH OF TABLE" << ui->tableWidget->width();
//        ////qDebug() << "WIDTH OF SCALE" << ui->ScaleWidget->width();
//        ////qDebug() << "column widthes";
//        for(int a = 0; a < pageVector.size();a++)
//            ////qDebug() << ui->tableWidget->columnWidth(a);
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
                ////qDebug() << filename;
                if(filename.endsWith(".mkv"))
                    videoCounter++;
                if(filename.endsWith(".alg"))
                    logCounter++;
                QFile file(videoWorkingDir+"/"+  filename);
                totalsize+= file.size();
                ////qDebug() << file.size();

            }
        }
        QVariant tmpvc = videoCounter, tmpvl = logCounter;
        QDateTime begin = QDateTime::fromTime_t(timeCells[0].beginTime).toUTC(), end = QDateTime::fromTime_t(timeCells[timeCells.size()-1].endTime).toUTC();//QDateTime::fromTime_t(dataMap[0].timeEdge1), end = QDateTime::fromTime_t(dataMap[dataMap.size()-1].timeEdge2);
//        ////qDebug() <<"mysize" <<tmpDir.;
//        ////qDebug() << dir.path();
//        ////qDebug() << "total size" << totalsize;
//        ////qDebug() << "video counter" << videoCounter;
//        ////qDebug() << "log counter" << logCounter;
//        ////qDebug() <<dataMap[dataMap.size()-1].timeEdge2 - dataMap[0].timeEdge1;
//        ////qDebug()<<ui->tableWidget_3->rowCount();
//        ////qDebug()<<ui->tableWidget_3->columnCount();
//        QDateTime sometime = QDateTime::fromTime_t(0);
//        if(end.daysTo(beging)<0)
//        {
//            newMessage.setWindowTitle("Внимание!");
//            newMessage.setText("Что-то случилось со временем! Оно идет назад!!!");
//            newMessage.exec();
//        }
//        ////qDebug() << beging.daysTo(end);
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
//        ui->tableWidget_3->item(0,0)->setText("123");
//        ui->tableWidget_3->item(0,0)->setText("123");
        ////qDebug() << "creating colored scale finished";
        openLogFile(logList.at(0));
        if(ui->horizontalSlider->maximum()!=0)
        {
            ui->horizontalSlider->setValue(0);
            ui->horizontalSlider->setMaximum(0);
            QTime tmp;
    //        tmp.setTime(0);
            tmp.setHMS(0,0,0);
            ui->timeEdit->setTime(tmp);
        }
        createFakeTimeScale(0,0);

        initThermoNames(&thNames,&seq);
        ////qDebug() <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" <<thNames;
        initSmallThermos(initThermoMaxs(&thMaxs),thNames,thMaxs,seq);
//        initBigThermos(2);
        ui->comboBox->removeItem(0);
        ui->comboBox_2->removeItem(0);
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(1);
        openVideoFile(videoList[0],videoList[1]);
        flowingOffset = 300;
        delayMs = (vplayer->_player->time()+flowingOffset + camOffsets.at(ui->comboBox->currentIndex()-1))/10;
        //////qDebug() << "start delayMs" << delayMs;
        delayMs = (delayMs/10 + 2)*10;
        //delayMs = 80;
        //////qDebug() << "start delayMs2" << delayMs;
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
//        videoOnly = true;
        createFakeTimeScale(0,0);
        ui->comboBox->removeItem(0);
        ui->comboBox_2->removeItem(0);
        ui->comboBox->setCurrentIndex(0);
        ui->comboBox_2->setCurrentIndex(1);
        openVideoFile(videoList[0],videoList[1]);
//        ui->horizontalSlider->installEventFilter(this);
        setButtonsEnable(true);
        //////qDebug() << "not opened log files";
        //////qDebug() <<"size in here" <<logList.size();
    }
    //////qDebug() << "current vplayer state is" << vplayer->getVideoState();

//     vplayer->_player->pause();
//     vplayer2->_player->pause();
//     while(vplayer->getVideoState()!=4){}
//     while(vplayer2->getVideoState()!=4){}
//    if(vplayer->getVideoState()==3)
//        while(vplayer->getVideoState()!=4)
//            vplayer->_player->pause();
//        while(vplayer2->getVideoState()!=4)
//            vplayer2->_player->pause();
//        vplayer->_player->pause();
//        vplayer2->_player->pause();
//        ////qDebug() << "player has state" << vplayer->getVideoState();
//        ////qDebug() << "player2 has state" << vplayer2->getVideoState();
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
        ////qDebug() << "passing here";
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
//    setSoundIcons();
    updateSoundMode();

}

void MainWindow::setPlayer1ModePlaying()
{
//    if(vplayer2->getVideoState()==3)
//    {
//        player1Playing = true;
//        player1Paused = false;
//        player1Opening = true;
//    }
//    ////////qDebug()() << "setPlayer1ModePlaying activated";
//    ////////qDebug()() << player1Playing;
//    ////////qDebug()() << player1Paused;
}

void MainWindow::setPlayer2ModePlaying()
{
//    if(vplayer2->getVideoState()==3)
//    {
//        player2Paused = false;
//        player2Playing = true;
//        player2Opening = true;
//    }
//    ////////qDebug()() << "setPlayer2ModePlaying activated";

//    ////////qDebug()() << player2Playing;
//    ////////qDebug()() << player2Paused;

}
void MainWindow::setPlayer1ModePaused()
{
//    if(vplayer->getVideoState()==4)
//    {
//        player1Paused = true;
//        player1Playing = false;
//        player1Opening = false;
//    }
//    ////////qDebug()() << "setPlayer1ModePaused activated";
//    ////////qDebug()() << player1Playing;
//    ////////qDebug()() << player1Paused;
}
void MainWindow::setPlayer2ModePaused()
{
//    if(vplayer2->getVideoState()==4)
//    {
//     player2Paused = true;
//     player2Playing = false;
//     player2Opening = false;
//    }
//     ////////qDebug()() << "setPlayer2ModePaused activated";
//     ////////qDebug()() << player2Playing;
//     ////////qDebug()() << player2Paused;
}
void MainWindow::setPlayer1ModeOpening()
{
//    if(vplayer->getVideoState()==1)
//    {
//        player1Playing = false;
//        player1Paused = false;
//        player1Opening = true;
//    }
}
void MainWindow::setPlayer2ModeOpening()
{
//    if(vplayer2->getVideoState()==1)
//    {
//        player2Playing = false;
//        player2Paused = false;
//        player2Opening = true;
//    }
}
void MainWindow::setPlayer1State()
{
//    if(vplayer->getVideoState()==1)
//    {
//        player1Playing = false;
//        player1Paused = false;
//        player1Opening = true;
//    }
//    if(vplayer->getVideoState()==3)
//    {
//        player1Playing = true;
//        player1Paused = false;
//        player1Opening = false;
//    }
//    if(vplayer->getVideoState()==4)
//    {
//        player1Playing = false;
//        player1Paused = true;
//        player1Opening = false;
//    }
}

void MainWindow::setPlayer2State()
{
//    if(vplayer2->getVideoState()==1)
//    {
//        player2Playing = false;
//        player2Paused = false;
//        player2Opening = true;
//    }
//    if(vplayer2->getVideoState()==3)
//    {
//        player2Playing = true;
//        player2Paused = false;
//        player2Opening = false;
//    }
//    if(vplayer2->getVideoState()==4)
//    {
//        player2Playing = false;
//        player2Paused = true;
//        player2Opening = false;
//    }
}

void MainWindow::waitEndStateTimerTick()
{
//    if(vplayer->getVideoState()==vplayer2->getVideoState()==6)
//    {
//        playersStatesSynchronized = true;
//        waitEndStateTimer->stop();
//    }
//    else if(vplayer->getVideoState()!=vplayer2->getVideoState())
//        playersStatesSynchronized = false;
}

void MainWindow::stateTimerTick()
{
//    stateTimerTickCounter++;
//    if(vplayer->getVideoState()==vplayer2->getVideoState())
//    {
//        playersStatesSynchronized = true;
//        stateTimer->stop();

//    }
//    else
//    {
//        if(vplayer->getVideoState()==6)
//            if(vplayer2->getVideoState()!=6)
//                vplayer2->_player->setTime(vplayer2->_player->length());
//        if(vplayer2->getVideoState()==6)
//            if(vplayer->getVideoState()!=6)
//                vplayer->_player->setTime(vplayer->_player->length());
//        playersStatesSynchronized = true;
//    }

}

void MainWindow::pausePlayer1()
{
//    videoDelayms++;
//    if(isVideo1Opened)
//    {
//       vplayer->_player->pause();
////       disconnect(vplayer->_player,SIGNAL(playing()),this,SLOT(pausePlayer1()));
//       ////////qDebug()() << "can i pause that player?";
//    }
//    if(isVideo2Opened)
//    {
//        vplayer2->_player->pause();
//        ////////qDebug()() << "and that one";
//    }
//    connect(vplayer2->_player,SIGNAL(playing()),this, SLOT(playBothPlayers()));
}

void MainWindow::playBothPlayers()
{
//    vplayer->pause();
////    vplayer2->pause();
//    disconnect(vplayer2->_player,SIGNAL(playing()),this,SLOT(playBothPlayers()));
//    if(isVideo1Opened)
//        vplayer->_player->pause();
//    if(isVideo2Opened)
//        vplayer2->_player->pause();
//    if((isVideo1Opened)&(isVideo2Opened))
//    {
//      //vplayer->play();
//      //vplayer2->play();
//    }
    ////////qDebug()()<<"both players slot";
}

void MainWindow::on_action_2_triggered()
{


}

int MainWindow::createDataMap()
{
    dataPage tmpPage;
//    ////qDebug() << "starting create data map";
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
//        ////qDebug() << tmpPage.timeEdge1;
        if(i<timeSegment.size()/2-1)
            tmpPage.timeEdge2 = timeSegment.at((i+1)*2);//timeSegment.at(i*2+1);
        else
            tmpPage.timeEdge2 = timeSegment.at(i*2+1);
        tmpPage.TimeFract1 = timeFracts.at(i*2);
        tmpPage.TimeFract2 = timeFracts.at(i*2+1);
        tmpPage.logName = logList.at(i);
        tmpPage.videoTimeEdges.clear();
//        ////qDebug() << "offsets counter at creating data map #"<< i <<offsetsCounter.at(i);
        for(int a=0; a < offsetsCounter.at(i); a++)
        {
//            if(camOffsets.at(i*10+a)>0)//&(videoTimes[i])
//            {
//                if(videoTimeGlobalIterator<videoTimes.size())
//                {
                    tmpPage.videoTimeEdges.append(videoTimes.at(videoTimeGlobalIterator));

                    videoTimeGlobalIterator++;
//                }
//                else
//                    tmpPage.videoTimeEdges.append(0);
//            }
//            else
//                tmpPage.videoTimeEdges.append(0);
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
//        tmpPage.videoVector.begin();
//        QMapIterator <QString, bool> Iter(tmpPage);
        tmpPage.videoVector.clear();
        tmpPage.camTimeOffsets.clear();
//        ////qDebug() <<"count of combobox items"<< ui->comboBox->count();
        for(int j = 0; j< ui->comboBox->count()-1; j++)
        {
            QFile tmpFile;
            tmpFile.setFileName(videoWorkingDir+"/"+videoList.at(i*10+j));
            bool tmpval = tmpFile.exists();
            tmpPage.camTimeOffsets.append(camOffsets.at(i*10+j));
            tmpPage.videoVector.insert(videoList.at(i*10+j),tmpval);
//            ////qDebug()<< "current j is" << jread    ;
        }
        dataMap.append(tmpPage);
    }
//    ui->progressBar_2->setMinimum(0);
//    ui->progressBar_2->setMaximum(dataMap.at(dataMap.size()-1).timeEdge2-dataMap.at(0).timeEdge1);
//    ////qDebug() <<"maximal progress bar value is"<< ui->progressBar_2->maximum();
    ui->horizontalSlider->setEnabled(true);
    ui->line->raise();
//    ////qDebug() << "data map successfully created";\
    timeSegment.clear();
    videoTimeGlobalIterator=0;
    return 0;
}

int MainWindow::openVideoFile(QString filename1, QString filename2)
{
#ifdef GLOBALMODE
    int result1=0,result2=0;
    int time;
    QFile filetocheck;
//    timer->stop();
    videoDelayms=0;
        playingFile1 = filename1;
        filetocheck.setFileName(videoWorkingDir+"/"+playingFile1);
        if(filetocheck.size()>10000)
        {
            result1 = vplayer->openLocal(videoWorkingDir+"/"+playingFile1);


            correctFramePosition();
           vplayer->_player->setTime(maxCamOffset - dataMap[pageIndex].camTimeOffsets.at(ui->comboBox->currentIndex()));
//           QString str="Камера ";
//           vplayer->showText(str.append(QString::number(ui->comboBox->currentIndex(),10)),1000,50,1000);
           isVideo1Opened = true;
         }
        playingFile2 = filename2;
        filetocheck.setFileName(videoWorkingDir+"/"+playingFile2);
        //////qDebug() << "some size from here" << filetocheck.size();
        if(filetocheck.size()>10000)
        {
            result2 = vplayer2->openLocal(videoWorkingDir+"/"+playingFile2);


            correctFramePosition();
            vplayer2->_player->setTime(maxCamOffset - dataMap[pageIndex].camTimeOffsets.at(ui->comboBox_2->currentIndex()));
//            QString str="Камера ";
//            vplayer2->showText(str.append(QString::number(ui->comboBox_2->currentIndex(),10)),1000,50,1000);
            isVideo2Opened = true;
        }
        showCameraNameTimer->start(200);
#endif
        timeSegmentIterator = videoList.indexOf(filename1)/(ui->comboBox->count()-1);
        updateSoundMode();
        ////qDebug()<< "in opening video" << ui->tableWidget->currentColumn();
//        createFakeTimeScale(0,ui->tableWidget->currentColumn());
   return 0;
}
void MainWindow::simpleDelayTimerTick()
{
    ////qDebug() << "index of simpleDelayTick changed";
    if(!timer->isActive())
        {
            simpleDelayTimer->stop();
            //vplayer->play();
            //vplayer2->play();
            timer->start(mainTimerInterval);
//            mythread->start();
        }

}

void MainWindow::delayTimerTick()
{
    videoDelayms++;
    delayTimer->start(1);
//    if((isVideo2Opened)&(vplayer->getVideoState()==3))
//        vplayer->_player->pause();
//    if((isVideo2Opened)&(vplayer2->getVideoState()==3))
//        vplayer2->_player->pause();
    if((isVideo1Opened)&(isVideo2Opened))
    {
        if((vplayer->getVideoState()==4)&(vplayer2->getVideoState()==4))
        {
            videoDelayms = 0;
            delayTimer->stop();
//            int tmpTime1 = vplayer->getCurrentTime();
//            int tmpTime2 = vplayer2->getCurrentTime();
//            if(tmpTime1>tmpTime2)
//                vplayer->_player->setTime(tmpTime2);
//            else if(tmpTime1<tmpTime2)
//                vplayer2->_player->setTime(tmpTime1);
//                vplayer2->moveToTime(tmpTime1);
            ////////qDebug()() << "delay ticks"<<videoDelayms;
//            player1Paused = false;
//            player2Paused = false;

//            //vplayer->play();
//            //vplayer2->play();
//            checkVideosSynchronized();
//            while(checkVideosSynchronized()==false){}
//            //vplayer->play();
//            //vplayer2->play();
        }
    }
//    ////////qDebug()() << "playingModePlayer1" << playingModePlayer1;
//    ////////qDebug()() << "playingModePlayer2" << playingModePlayer2;
//    ////////qDebug()() << "delay tick"<<isVideo1Opened<<isVideo2Opened;
//    ////////qDebug()() << "delay ticks"<<videoDelayms;
}

void MainWindow::stopDelayTimer()
{
//    delayTimer->stop();
//    ////////qDebug()() <<"delaytime" << videoDelayms;

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
//    while(vplayer->getVideoState()!=4){}
//    while(vplayer2->getVideoState()!=4){}
    if((vplayer->getVideoState()==4)&(vplayer2->getVideoState()==4))
    {
//    float tmpPos1 = vplayer->_player->position();
//    float tmpPos2 = vplayer2->_player->position();

//    if(tmpPos1>tmpPos2)
//        vplayer->_player->setPosition(tmpPos2);
//    else if(tmpPos1<tmpPos2)
//        vplayer2->_player->setPosition(tmpPos1);

    int tmpTime1 = vplayer->_player->time();
    int tmpTime2 = vplayer2->_player->time();
//    while(vplayer->getVideoState()==3)
    ////////qDebug()() << "tmpTime1" << tmpTime1;
    ////////qDebug()() << "tmpTime2" << tmpTime2;
    if(tmpTime1>tmpTime2)
    {
        vplayer2->_player->setTime(tmpTime1);
        vplayer2->_player->pause();
        while(vplayer2->getVideoState()!=4){}
    }
    else if(tmpTime2>=tmpTime1)
    {
        vplayer->_player->setTime(tmpTime2);
        vplayer->_player->pause();
        while(vplayer->getVideoState()!=4){}
    }


//    vplayer2->_player->pause();

    ////////qDebug()() << "vplayer1 time after all" << vplayer->_player->time();
    ////////qDebug()() << "vplayer2 time after all" << vplayer2->_player->time();
//    if(!player1StateBefore)
//    if(vplayer->getVideoState()==4)
//        //vplayer->play();
////    if(!player2StateBefore)
//    if(vplayer2->getVideoState()==4)
//        //vplayer2->play();
    return true;
    }
    else
        ////////qDebug()() << "player1 state is" << vplayer->getVideoState() << " player 2 state is"<<vplayer2->getVideoState();
    return false;

}

int MainWindow::changeVideo1(QString filename)
{
    ////qDebug() << "changing video #1";
    int result1=0;
//   playingFile1 = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
   if(ui->comboBox->currentIndex()!=0)
   {
        vplayer->stop();
        correctFramePosition();
        vplayer2->_player->pause();
        playingFile1 = filename;
//        while(vplayer->getVideoState()!=5){}


//        isVideo1Opened = false;
        QFile filetocheck;
        filetocheck.setFileName(videoWorkingDir+"/"+playingFile1);
        //////qDebug() << "some size from here" << filetocheck.size();
        if(filetocheck.size()>10000)
        {
//            result1 = vplayer->openLocal(videoWorkingDir+"/"+playingFile1);
        }
        else result1 = 2;
   }
   return result1;
}

int MainWindow::changeVideo2(QString filename)
{
    ////////qDebug()() << "changing video #2";
    int result2=0;
//   playingFile1 = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
   if(ui->comboBox_2->currentIndex()!=0)
   {
        vplayer2->stop();
        correctFramePosition();
        vplayer->_player->pause();
        playingFile2 = filename;
//        isVideo2Opened = false;
//        while(vplayer2->getVideoState()!=5){}
//        if(vplayer2->getVideoState()==3)
//        {
//            vplayer2->_player->pause();
//            vplayer->_player->pause();
//        }
        QFile filetocheck;
        filetocheck.setFileName(videoWorkingDir+"/"+playingFile2);
        //////qDebug() << "some size from here" << filetocheck.size();
        if(filetocheck.size()>10000)
        {
//        result2 = vplayer2->openLocal(videoWorkingDir+"/"+playingFile2);
//        while(vplayer2->getVideoState()!=3){}
//            vplayer2->_player->pause();
//        while(vplayer->getVideoState()!=3){}
//            vplayer->_player->pause();
//        vplayer2->_player->setTime(vplayer->_player->time());
        ////////qDebug()() << vplayer->_player->time();
        ////////qDebug()() << vplayer2->_player->time();
        ////////qDebug()() << vplayer->getVideoState();
        ////////qDebug()() << vplayer2->getVideoState();
//        vplayer2->_player->setPosition(vplayer->_player->position());
//        delayTimer->start(1);
        }
        else result2 = 2;
   }
   ////////qDebug()() << vplayer->_player->time();
   ////////qDebug()() << vplayer2->_player->time();
   ////////qDebug()() << vplayer->getVideoState();
   ////////qDebug()() << vplayer2->getVideoState();
   return result2;
}
bool MainWindow::synchronizePlayersStates()
{

    ////////qDebug()() << "synchronizing states";
    ////////qDebug()() << "player1 state is" << vplayer->getVideoState();
    ////////qDebug()() << "player2 state is" << vplayer2->getVideoState();
    if(playersStatesSynchronized)
        return true;
    else
    {
        stateTimerTickCounter = 0;
        if((vplayer->getVideoState()==3)&(vplayer2->getVideoState()==6))
        {
//            vplayer->stop();
//            waitEndStateTimer->start(1);
        }
        if((vplayer->getVideoState()==6)&(vplayer2->getVideoState()==3))
        {
//            vplayer2->stop();
//            waitEndStateTimer->start(1);
        }
        if((vplayer->getVideoState()==4)&(vplayer2->getVideoState()==3))
        {
            vplayer2->_player->pause();
        }
        else if((vplayer->getVideoState()==3)&(vplayer2->getVideoState()==4))
        {
            //vplayer2->play();
        }
        stateTimer->start(1);
        while((stateTimerTickCounter<100)|(!playersStatesSynchronized)){}
        if(!playersStatesSynchronized)
            return false;
        else
            return true;
    }

}

void MainWindow::video1Ended()
{

    pageIndex++;
    int index1=0,index2=0;
    player1Opening = false;
    player1Paused = false;
    player1Playing = false;
//    isVideo1Opened = false;
    if(vplayer2->getVideoState()==6)
    {
        timer->stop();
        mythread->exit();

    }

    ////////qDebug()() <<"current player 1 state is" <<vplayer->getVideoState();
    ////////qDebug()() <<"current player 2 state is" <<vplayer2->getVideoState();
    for(int i = 0; i < videoList.size(); i++)
    {
        if(videoList[i]==playingFile1)
            index1=i;
        if(videoList[i]==playingFile2)
            index2=i;

    }
    ////////qDebug()() << "index1"<< index1<<" index2"<< index2;

    if(vplayer->getVideoState()==vplayer2->getVideoState())
    {
    if((index1+ui->comboBox->count()-1<videoList.size())&(index2+ui->comboBox->count()-1<videoList.size()))
        {

    //        delayTimer->start(1);
    //        isVideo1Opened = false;
    //        isVideo2Opened = false;
            openVideoFile(videoList[index1+ui->comboBox->count()-1],videoList[index2+ui->comboBox->count()-1]);
//            ////qDebug() << "VIDEO HAS CHANGED";
    //        vplayer2->moveToTime(vplayer->getCurrentTime());
        }
        playersStatesSynchronized = true;
    }
    if(vplayer->getVideoState()==3)
        mythread->start();
    //////qDebug() << "logVideoDelta" << logVideoDelta;
//    else
//        synchronizePlayersStates();
}
void MainWindow::video2Ended()
{
    int index1=0,index2=0;
    player2Opening = false;
    player2Paused = false;
    player2Playing = false;
//    isVideo2Opened = false;
    if(vplayer->getVideoState()==6)
    {
        timer->stop();
//        mythread->exit();
        //////qDebug() << ui->horizontalSlider->value();
    }
    ////////qDebug()() << "current player 2 state is" <<vplayer2->getVideoState();
    for(int i = 0; i < videoList.size(); i++)
    {
        if(videoList[i]==playingFile1)
            index1=i;
        if(videoList[i]==playingFile2)
            index2=i;

    }
    ////////qDebug()() << "index1"<< index1<<" index2"<< index2;
    if(vplayer->getVideoState()==vplayer2->getVideoState())
    {
    if((index1+ui->comboBox->count()-1<videoList.size())&(index2+ui->comboBox->count()-1<videoList.size()))
        {

    //        delayTimer->start(1);
    //        isVideo1Opened = false;
    //        isVideo2Opened = false;
            openVideoFile(videoList[index1+ui->comboBox->count()-1],videoList[index2+ui->comboBox->count()-1]);
//             ////qDebug() << "VIDEO HAS CHANGED";
    //        vplayer2->moveToTime(vplayer->getCurrentTime());
        }
        playersStatesSynchronized = true;
    }
//    else
//        synchronizePlayersStates();
}
void MainWindow::on_playButton_clicked()
{

//    if(timeCells[ui->tableWidget->columnCount()-1].cellType==0)
//    {
//        vplayer->togglePause();
//        vplayer2->togglePause();
//    }
        //delayMs = (vplayer->_player->time()+ flowingOffset+ camOffsets.at(ui->comboBox->currentIndex()-1))/10;
        if(mythread->isRunning())
            {
//                timer->stop();
            setPause();
//                mythread->exit();
                getTimeTimer->stop();
//                ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            }
        else
            {
//                timer->start(mainTimerInterval);
//                mythread->start();
            setPlay();
                getTimeTimer->start(1);
//                ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            }
//    playButtonPressed=!playButtonPressed;
#ifdef GLOBALMODE
//    vplayer->pause();
//    vplayer2->pause();
#endif
}

void MainWindow::on_stopButton_clicked()
{
#ifdef GLOBALMODE
    terminateAll();
#endif
}

void MainWindow::setButtonsEnable(bool tf)
{
    ui->playButton->setEnabled(tf);
    ui->stopButton->setEnabled(tf);
    ui->previousTimeSegment->setEnabled(tf);
    ui->nextTimeSegment->setEnabled(tf);
    ui->frameBackwardButton->setEnabled(tf);
    ui->nextFrameButton->setEnabled(tf);
//    ui->timeEdit->setEnabled(tf);
    ui->pushButton->setEnabled(!tf);
  //  videoButton->setEnabled(!tf);
//    logButton->setEnabled(!tf);

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
//    ui->timeEdit->setEnabled(tf);

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
//    //////////qDebug()() << tmp;
}

void MainWindow::on_nextTimeSegment_clicked()
{
//    ui->nextTimeSegment->click();
//    for(int i =0; i < checkBoxes.count(); i++)
//        checkBoxes[i]->setChecked(false);
//    for(int i = 0; i < thermoVals.count(); i++)
//    {
//        thermoVals[i]->setText(0);
//        parameterBar[i]->setValue(0);
//    }
    ////qDebug() << "table" << ui->tableWidget->currentColumn();
    clearParTable();
    if(ui->tableWidget->currentColumn()<ui->tableWidget->columnCount()-1)
    {
        //qDebug() << "var1";
//        if(timeCellIndex < ui->tableWidget->currentColumn())
//        {
//            //qDebug() <<"1" <<timeCellIndex;
//            //qDebug() << ui->tableWidget->currentColumn();
//            moveToAnotherTimeSegment(timeCellIndex);

//            ui->tableWidget->setCurrentCell(0,timeCellIndex);
//        }
//        else
//        if(timeCellIndex!=ui->tableWidget->currentColumn())
//        {
//            if(timeCells[timeCellIndex].cellType!=2)
//            {
                //qDebug() << "1"<<timeCellIndex;
                //qDebug() << timeCells[timeCellIndex].cellType;
                //qDebug() << ui->tableWidget->currentColumn();
                moveToAnotherTimeSegment(ui->tableWidget->currentColumn()+1);
                ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn()+1);
//            }
//            else
//            {
//                            //qDebug() <<"2" <<timeCellIndex;
//                            //qDebug() <<timeCells[timeCellIndex].cellType;
//                            //qDebug() << ui->tableWidget->currentColumn();
//                            moveToAnotherTimeSegment(timeCellIndex-1);

//                            ui->tableWidget->setCurrentCell(0,timeCellIndex-1);
//            }
//        }
//        else
//        {
//            //qDebug() << "3"<<timeCellIndex;
//            //qDebug() <<timeCells[timeCellIndex].cellType;
//            //qDebug() << ui->tableWidget->currentColumn();
//            moveToAnotherTimeSegment(/*ui->tableWidget->currentColumn()*/timeCellIndex+1);
//            ui->tableWidget->setCurrentCell(0,/*ui->tableWidget->currentColumn()*/timeCellIndex+1);
//        }

    }
    else
    {
        //qDebug() << "var2";
        moveToAnotherTimeSegment(ui->tableWidget->currentColumn());
         ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn());

    }

//    on_tableWidget_clicked(const QModelIndex &index);
//    ui->tableWidget->
//    int tmp1=0,tmp2=0;
//    QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
//    QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);

//    while(tmp1<=ui->comboBox->currentIndex())
//    {
//        Iter1.next();
//        tmp1++;
//    }
//    while(tmp2<=ui->comboBox_2->currentIndex())
//    {
//        Iter2.next();
//        tmp2++;
//    }
//    ////qDebug() << ui->comboBox->currentIndex();
//    ////qDebug() << ui->comboBox_2->currentIndex();
//    ////qDebug() << Iter1.key();
//    ////qDebug() << Iter2.key();
//        openVideoFile(Iter1.key(),Iter2.key());
//        openLogFile(dataMap[pageIndex].logName);
//        if(mythread->isRunning())
//        {
//            mythread->exit();
//            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
//        }
//        if(vplayer->getVideoState()==3)
//        {
//            mythread->start();
//            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
//        }
correctFramePosition();
}

#ifdef GLOBALMODE
void MainWindow::setVideoTime()//its my handmade slot
{
//    mutex.lock();

    int time =0;
    int ms = time%1000;
    time = time/1000;
    QTime outtime;
    int h = time/3600;
    int m = (time/60)%60;
    int s = time%60;
    int tmpDelayMs=0;
    int currentVideoTime = 0;
    int frameLength = 5;//50ms

    ui->timeEdit->setTime(outtime);

    if(!videoOnly)
    {
//        if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
//        {
            time =  vplayer->getCurrentTime();
            outtime.setHMS(h,m,s,ms);
            currentVideoTime =(vplayer->_player->time() + camOffsets.at(ui->comboBox->currentIndex()-1))/10;
            emit sendTicksToWorker(currentVideoTime);
            int mainTime=0;
            if(vplayer->_player->length()>vplayer2->_player->length())
                mainTime = vplayer2->_player->time();
            else
                mainTime = vplayer->_player->time();
                tmpDelayMs = (mainTime + flowingOffset+ camOffsets.at(ui->comboBox->currentIndex()-1))/10;//(delayMs*10 + vplayer->_player->time() + camOffsets.at(ui->comboBox->currentIndex()-1))/20;//true time is a sum of maxcamoffset,
            logVideoDelta += delayMs - (vplayer->_player->time() + camOffsets.at(ui->comboBox->currentIndex()-1))/10;
                delayMs = tmpDelayMs;
            logVideoDeltaCounter++;
            tickCounter = delayMs%50;
            lastDelay = delayMs;
//        }
//        else
//        {
//            logVideoDeltaCounter++;
//            tickCounter = delayMs%50;
//            lastDelay = delayMs;
//        }
    }
    else
    {
        delayMs = (vplayer->_player->time());//(delayMs*10 + vplayer->_player->time() + camOffsets.at(ui->comboBox->currentIndex()-1))/20;//true time is a sum of maxcamoffset,
        //////qDebug() << delayMs;
    }
    if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
    {
        if(vplayer->getVideoState()==3)
        {
            if(mythread->isFinished())
            {
                mythread->start();
                ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            }
        }
    }
    else
    {
        if(mythread->isFinished())
        {
            mythread->start();
            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        }
    }
//    mutex.unlock();
}
#endif


void MainWindow::on_previousTimeSegment_clicked()
{
//        //////////qDebug()() << openConfigFile(&workingDir);
//    clearParTable();
//    pageIndex--;
//    ////qDebug() << "current page is" << pageIndex;
//    if(pageIndex < 0)
//        pageIndex = 0;
//     ui->tableWidget->setCurrentCell(0,pageIndex);
    if(ui->tableWidget->currentColumn()>0)
    {
        //qDebug() << "var3";
        moveToAnotherTimeSegment(ui->tableWidget->currentColumn());
        ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn()-1);

    }
    else
         ui->tableWidget->setCurrentCell(0,ui->tableWidget->currentColumn());
//    int tmp1=0,tmp2=0;
//    QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
//    QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);
//    while(tmp1<=ui->comboBox->currentIndex())
//    {
//        Iter1.next();
//        tmp1++;
//    }
//    while(tmp2<=ui->comboBox_2->currentIndex())
//    {
//        Iter2.next();
//        tmp2++;
//    }
////    vplayer->_player->pause();
////    vplayer2->_player->pause();
////    while(vplayer->getVideoState()!=4){}
////    while(vplayer2->getVideoState()!=4){}
//        openVideoFile(Iter1.key(),Iter2.key());
//        openLogFile(dataMap[pageIndex].logName);
//        if(mythread->isRunning())
//        {
//            mythread->exit();
//            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
//        }
//        if(vplayer->getVideoState()==3)
//        {
//            mythread->start();
//            ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
//        }
//    pageIndex++;
//    openVideoFile(dataMap[pageIndex].videoVector.at(ui->comboBox->currentIndex()-1),dataMap[pageIndex].videoVector.at(ui->comboBox_2->currentIndex()-1));
//    openLogFile(dataMap[pageIndex].logName);
//    if(mythread->isRunning())
//        mythread->exit();
//    videoFileSelector(ui->comboBox->currentIndex(), 0);


//    int index1=0,index2=0;
//    for(int i = 0; i < videoList.size(); i++)
//    {
//        if(videoList[i]==playingFile1)
//            index1=i;
//        if(videoList[i]==playingFile2)
//            index2=i;

//    }
//    ////////qDebug()() << "index1"<< index1<<" index2"<< index2;
//    if((index1-ui->comboBox->count()+1 >=0)&(index2-ui->comboBox->count()+1>=0))
//    {
//        openVideoFile(videoList[index1-ui->comboBox->count()+1],videoList[index2-ui->comboBox->count()+1]);
////        if(vplayer->getCurrentTime()>vplayer2->getCurrentTime())
////           vplayer2->moveToTime(vplayer->getCurrentTime());
//        //////qDebug() << "current index"<<index1;
//        openLogFile(logList[pageIndex]);
//        if(mythread->isRunning())
//            mythread->exit();

//    }
    correctFramePosition();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
//    int newOpenedFileIndex = findTimeSegment(value);
////    ////////qDebug()() << newOpenedFileIndex;
//    if(openedFileIndex!=newOpenedFileIndex)
//    {
//        //openLogFile(newOpenedFileIndex);
//    }
//    else
//    {

//    }
//    mutex.lock();

    delayMs = value*100;
//    ////qDebug() << "on slider value changed delayms" << delayMs;
//    ////qDebug() << value;
//    ////qDebug() << ui->horizontalSlider->value();
//    mythread
//    updateTime();
//    mutex.unlock();
//    ui->horizontalSlider->setValue(value);
//    lastVal


//    lastVal = value;

//    setVideoTime(); //
}
void MainWindow::moveToNextTimeFrame()
{
//    vplayer->stop();
//    vplayer2->stop();
//    if()

    ui->nextTimeSegment->click();
//    ui->horizontalSlider->blockSignals(false);
}

void MainWindow::terminateAll()
{
    //    vplayer->pause();
    //    vplayer2->pause();
        logWorkingDir = "";
        videoWorkingDir = "";
        ui->line->setVisible(false);
        ui->line_2->setVisible(false);
        ui->line_3->setVisible(false);
        ui->line_4->setVisible(false);
        ui->ScaleWidget->setVisible(false);
        ui->horizontalSlider->setEnabled(false);

    //    ui->ScaleWidget->close();
        ui->playButton->click();
        vplayer->stop();
        vplayer2->stop();
    //    mythread->exit();
    //    threadTimer->stop();
        delayMs = 0;
        mythread->exit();
        updateTime();
    //    updateTime();
    //    updateTime();
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(0);
        ui->tableWidget_2->clear();
    //    ui->tableWidget_3->clear();
    //    ////qDebug() << ui->tableWidget_3->rowCount();
        for(int j = 0; j< ui->tableWidget_3->rowCount(); j++)
            ui->tableWidget_3->item(j,0)->setText(" ");

    //    ui->comboBox->addItem("Нет");
    //    ui->comboBox_2->addItem("Нет");
    //    ////qDebug() << "stop me now!";
        if(!videoOnly)
        {
            dataParams *tmpDP = new dataParams;
            getRecordNumClosestToTime(/*dataMap[pageIndex].timeEdge1*/timeCells[ui->tableWidget->currentColumn()].beginTime+(int)delayMs/100,(int)((delayMs%100)*2.56),0);
            makeStructFromRecord(log->record,tmpDP);
            updateThermos(*tmpDP);
        }
    //        ////qDebug() << "or now!";
        QTime tmp;
        tmp.setHMS(0,0,0);
        ui->timeEdit->setTime(tmp);

        ui->horizontalSlider->setValue(0);

    //    parameterBar.clear();
        isFolderOpened = false;
        accepted = false;
    //    this->update();
        ui->comboBox->blockSignals(true);
        ui->comboBox_2->blockSignals(true);
    //    ui->comboBox->
        ui->comboBox->addItem("Нет");
        ui->comboBox_2->addItem("Нет");
        ui->comboBox->blockSignals(false);
        ui->comboBox_2->blockSignals(false);
        videoButton->setEnabled(true);
        setButtonsEnable(false);
        dataMap.clear();
        timeCells.clear();
        videoList.clear();
        //if(dataMap.size()!=0)
    //    ////qDebug() << timeCells.size();
    //        ////qDebug()<<dataMap.size();

        for(int a = 0 ; a< ui->tableWidget->columnCount(); a++)
            ui->tableWidget->removeColumn(0);
        ui->tableWidget->clear();
    //    ////qDebug() << ui->tableWidget->columnCount();
    //    ui->ScaleWidget->

                QwtScaleDraw *resetScale = new QwtScaleDraw;
    //            resetScale->setTimeArr(0,0);
                resetScale->setLabelAlignment(Qt::AlignRight);
                ui->ScaleWidget->setScaleDraw(resetScale);
                ui->ScaleWidget->setContentsMargins(0,0,0,0);//leveling scale labels alignment balance
    //            QwtScaleTransformation *tr= new QwtScaleTransformation(QwtScaleTransformation::Linear);
    //            ui->ScaleWidget->setScaleDiv(tr,0);
    //    ui->ScaleWidget->clearMask();
    //    delete mapTimeScale;
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
    //    ////qDebug() << "orr now!";
}

void MainWindow::on_action_4_triggered()
{

    if(mythread->isRunning())
        ui->playButton->click();
        selectLogFolder();
        qDebug() << "logfileerror"<< LogFileError;
        if(LogFileError==2)
        {
            qDebug() << "log folder error!!!!!!!!!!!!";
        }
        selectVideoFolder();
    this->setWindowTitle(logWorkingDir);
    if(logWorkingDir!="")
        ui->pushButton->click();
    if(threadTimer->isActive())
    {
        ////qDebug() << "timer is running";
    }

}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    int tmp1=0,tmp2=0;
//    QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
//    if(timeCells[ui->tableWidget->currentColumn()].currentPage!=pageIndex)
//    {
    if(readyToPlay)
    {
        pageIndex = timeCells[ui->tableWidget->currentColumn()].currentPage;
        QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);

        ////////qDebug()() << "combo2" << index;
//        ////qDebug() << "index of combobox2 changed"<< index;
        if(index==ui->comboBox->currentIndex())
        {
            if(index==ui->comboBox->count()-1)
                ui->comboBox_2->setCurrentIndex(index-1);
            else
                ui->comboBox_2->setCurrentIndex(index+1);
        }
    //    ////////qDebug()()<< vplayer2->getCurrentMediaLocation();
    //    if(vplayer->_media->currentLocation())
        if(isVideo1Opened|isVideo2Opened)
        {

            int tmptime = vplayer2->getCurrentTime()+camOffsets.at(lastIndex1-1)-camOffsets.at(index-1);//!!
                 while(tmp2<=ui->comboBox_2->currentIndex())
                {
                    Iter2.next();
                    tmp2++;
                }
                if(vplayer->getVideoState()==4)
                    vplayer->togglePause();
            vplayer2->openLocal(videoWorkingDir+"/"+Iter2.key());
            showCameraNameTimer->start(200);
//            QString str="Камера ";
//            vplayer2->showText(str.append(QString::number(ui->comboBox_2->currentIndex(),10)),1000,50,1000);

            isVideo2Opened = true;
            vplayer2->_player->setTime(tmptime);
            if(mythread->isRunning())
                mythread->exit();
                if(mythread->isRunning())
                    mythread->exit();
//                ////qDebug() << "player1 current state" << vplayer->getVideoState();
//                ////qDebug() << "player2 current state" << vplayer2->getVideoState();
                sound1IconState = vplayer->getAudioIconState();
                sound2IconState = vplayer2->getAudioIconState();
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
//                setSoundIcons();
                updateSoundMode();
        }
        lastIndex2 = index;
    }
}


int MainWindow::getBeforeIndex(int videoIndex)
{
    if(videoIndex==0)
        return 1;
    if(videoIndex==1)
        return 2;
    if(videoIndex==2)
        return 3;
    if(videoIndex==3)
        return 4;
    if(videoIndex==4)
        return 5;
    if(videoIndex==5)
        return 6;
    if(videoIndex==6)
        return 7;
    if(videoIndex==7)
        return 8;
    if(videoIndex==8)
        return 9;
    if(videoIndex==9)
        return 10;
    else return 0;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    int tmp1=0,tmp2=0;
    if(readyToPlay)
    {
        pageIndex = timeCells[ui->tableWidget->currentColumn()].currentPage;
        QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
        if(index==ui->comboBox_2->currentIndex())
        {
            if(index==ui->comboBox->count()-1)
                ui->comboBox->setCurrentIndex(index-1);
            else
                ui->comboBox->setCurrentIndex(index+1);
        }
        if(isVideo1Opened|isVideo2Opened)
        {
                int tmptime = vplayer->getCurrentTime()+camOffsets.at(lastIndex1-1)-camOffsets.at(index-1);
                while(tmp1<=ui->comboBox->currentIndex())
                {
                    Iter1.next();
                    tmp1++;
                }
                if(vplayer2->getVideoState()==4)
                    vplayer2->togglePause();
                vplayer->openLocal(videoWorkingDir+"/"+Iter1.key());
                showCameraNameTimer->start(200);
                isVideo1Opened = true;
                vplayer->_player->setTime(tmptime);
                if(mythread->isRunning())
                    mythread->exit();
        }
        lastIndex1 =index;
        sound1IconState = vplayer->getAudioIconState();
        sound2IconState = vplayer2->getAudioIconState();
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

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

}

void MainWindow::on_frameBackwardButton_clicked()
{
    if(tickCounter<=0)
        tickCounter = 20;
    tickCounter--;
    tickCounter--;

//    ////////qDebug()() << tickCounter;
    updateTime();
}

void MainWindow::on_nextFrameButton_clicked()
{
//    vplayer->s
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
//    str.append(QString::number(ui->comboBox->currentIndex(),10));
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

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
//    currentWidget1Geometry.setY(widget1Y+arg1);
//    int X1, Y1, X2, Y2;
//    currentWidget1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
//    baseVideo1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
//    currentWidget1Geometry.setCoords(X1,Y1+arg1,X2,Y2+arg1);
//    ////////qDebug()() <<"Y changed" << currentWidget1Geometry;
//    vplayer->changeGeometry(currentWidget1Geometry);
//    ////////qDebug()() << vplayer->getVideoSize();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
//    currentWidget1Geometry.setX(widget1X + arg1);
//    int X1, Y1, X2, Y2;
//    baseVideo1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
////    currentWidget1Geometry.getCoords(&X1,&Y1,&X2,&Y2);
//    currentWidget1Geometry.setCoords(X1+arg1,Y1,X2+arg1,Y2);
//    ////////qDebug()() <<"X changed"<< currentWidget1Geometry;
//    vplayer->changeGeometry(currentWidget1Geometry);
//    ////////qDebug()() << vplayer->getVideoSize();
}

void MainWindow::on_pushButton_2_clicked()
{
//    if(vplayer->_player->time()>vplayer2->_player->time())
//    //vplayer->_player->setTime();
//    int time1 = vplayer->_player->time();
//    int time2 = vplayer2->_player->time();
//    ////////qDebug()() << time1;
//    ////////qDebug()() << time2;
//    if(time1>time2)
//    {
//        vplayer2->_player->setTime(time1);
////        vplayer->_player->setTime(time1);
//    }
//    else
//    {
//        vplayer->_player->setTime(time2);
////        vplayer2->_player->setTime(time2);
//    }

//    vplayer->_player->resume();
//    vplayer2->_player->resume();
//    while(vplayer->getVideoState()!=3){}
//    while(vplayer2->getVideoState()!=3){}
//    vplayer->togglePause();
//    vplayer2->togglePause();

//    time1 = vplayer->_player->time();
//    time2 = vplayer2->_player->time();
//    ////////qDebug()() << time1;
//    ////////qDebug()() << time2;
//    if(time1>time2)
//    {
//        vplayer2->_player->setTime(time1);
////        vplayer->_player->setTime(time1);
//    }
//    else
//    {
//        vplayer->_player->setTime(time2);
////        vplayer2->_player->setTime(time2);
//    }

//    vplayer->_player->resume();
//    vplayer2->_player->resume();
//    while(vplayer->getVideoState()!=3){}
//    while(vplayer2->getVideoState()!=3){}
//    vplayer->togglePause();
//    vplayer2->togglePause();
//    vplayer->_player->pause();
//    vplayer2->_player->pause();
//    while((vplayer->getVideoState()==3)&(vplayer2->getVideoState()==3)){}
//    for(int i =0; i < 2000; i++)
//    {
//        vplayer->_player->pause();
//        vplayer2->_player->pause();
//        while(vplayer->getVideoState()!=4){}
//        while(vplayer2->getVideoState()!=4){}
//        vplayer->_player->pause();
//        vplayer2->_player->pause();
//        while(vplayer->getVideoState()!=4){}
//        while(vplayer2->getVideoState()!=4){}
//    }
    ////////qDebug()() << vplayer->_player->time();
    ////////qDebug()() << vplayer2->_player->time();
    ////////qDebug()() << vplayer->getVideoState();
    ////////qDebug()() << vplayer2->getVideoState();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    isSliderPressed = false;
    //qDebug() << "slider event release";
    mythread->start();
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
    {
        vplayer->play();
        vplayer2->play();
    }
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    isSliderPressed = true;
    //qDebug() << "slider event press";
//    mythread->exit();
//    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
//    vplayer->_player->pause();
//    vplayer2->_player->pause();
}
int MainWindow::setPause()
{
    if(mythread->isRunning())
    {
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        mythread->exit();
        if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
        {
            vplayer->pause();
            vplayer2->pause();
        }
    }
    return 0;
}
int MainWindow::setPlay()
{
    if(mythread->isFinished())
    {
        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        mythread->start();
        if(timeCells[ui->tableWidget->currentColumn()].cellType==0)
        {
            vplayer->play();
            vplayer2->play();
        }
    }
    return 0;
}

void MainWindow::getDelayMsToSet(int pos,int totalTime)
{
    ////qDebug() << "getDelayMsToSet";
    ////qDebug() << "pos" << pos;
    ////qDebug() << "totalTime" << totalTime;
    float tmpPos = 0;
    int excessTime = 0;
    bool lastCellFlag = false;
    float realLength = 0;
    float totallength =0,littlelength = 0;
    for(int i = 0; i < timeCells.count(); i++)
    {
        totallength+=(float)((ui->tableWidget->width())*timeCells[i].relativeWidth);
//        qDebug() << timeCells[i].relativeWidth << "rel width" << i <<"cell";
        littlelength+=timeCells[i].relativeWidth;
        realLength+=ui->tableWidget->columnWidth(i);
    }
    for(int i =0; i <= ui->tableWidget->columnCount(); i++)
    {
        if( i ==  ui->tableWidget->columnCount())
        {
            tmpPos = (((float)(timeCells[i-1].endTime-timeCells[0].beginTime)/totalTime))*realLength/*ui->tableWidget->width()*/;
            lastCellFlag = true;
           // qDebug() <<"tmp pos"<< tmpPos;
          //  ////qDebug() << "last cell is" << i-1;
        }
        else
        {
            tmpPos = (((float)(timeCells[i].beginTime-timeCells[0].beginTime)/totalTime))*realLength/*ui->tableWidget->width()*/;

        }
//        ////qDebug() << "pos" << pos;
//        ////qDebug() << "tmpPos"<< tmpPos;
//        ////qDebug() << "totaltime" << totalTime;
//        ////qDebug() << "time delta" << timeCells[i].beginTime-timeCells[0].beginTime;
//        ////qDebug() << "time delta2" << timeCells[i-1].endTime-timeCells[0].beginTime;
//        ////qDebug() << "timeCells[i].beginTime" << timeCells[i].beginTime;
//        ////qDebug() << "timeCells[0].beginTime" << timeCells[0].beginTime;
        if(pos>=tmpPos)
        {

        }
        else
        {
            if(i>=0)//freeze at selected i this position
            {
                if(i==0)
                {
                    ////qDebug()<< "ZEROOOO";
                }
                else
                {



                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i-1))/ui->tableWidget->width()))*totalTime;
//                    qDebug() << "totoal length" << totallength;
//                    qDebug() << "total time" << totalTime;
//                    qDebug() << "littlelength" << littlelength;
//                    qDebug() << "widget width" << ui->tableWidget->width();
//                    qDebug() << "excess time" << excessTime;
//                    qDebug() <<"tmp pos"<< tmpPos;
//                    qDebug() << "pos" << pos;
//                    qDebug() << "time edge1" << QDateTime::fromTime_t(timeCells[i-1].endTime).toUTC();
//                    qDebug() << "time edge2" << QDateTime::fromTime_t(timeCells[0].beginTime).toUTC();
//                    qDebug() << "real length" << realLength;
                    if(ui->tableWidget->currentColumn()!=i-1)
                    {
                        //qDebug() << "var4";
                        //qDebug() <<"i-1" <<i-1;
                        ////qDebug() << ui->tableWidget->currentColumn();
//                        ////qDebug() << "pos1" << pos;
//                        ////qDebug() << "tmpPos1" << tmpPos;
//                        ////qDebug() << "excesstime1" << excessTime;

                        moveToAnotherTimeSegment(i-1);
                        ui->tableWidget->setCurrentCell(0,i-1);


                    }
                    ////qDebug() << "smth1";
                    //qDebug() << "v2";
                    //qDebug() << pos;
                    //qDebug() << ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn());
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
                        //qDebug() << "var5";
                        moveToAnotherTimeSegment(i);
                        ui->tableWidget->setCurrentCell(0,i);

                    }
//                    ////qDebug() << "pos1";
                    //correctCellSeekerPosition((float)(pos/totalTime)*ui->tableWidget->width());
                    delayMsToSet = excessTime*100;
                    i = ui->tableWidget->columnCount();
//                    ////qDebug() << "ZERO POS";

            }
        }
    }
    if(mythread->isFinished())
        mythread->start();
}
void MainWindow::getCellAndTimeToMoveTo(int pos,int totalTime)
{
    ////qDebug() << "getCellAndTimeToMoveTo";
    ////qDebug() << "pos" << pos;
    ////qDebug() << "totalTime" << totalTime;
    int tmpPos = 0;
    int excessTime = 0;
    bool lastCellFlag = false;
    for(int i =0; i <= ui->tableWidget->columnCount(); i++)
    {
        if( i ==  ui->tableWidget->columnCount())
        {
            tmpPos = (((float)(timeCells[i-1].endTime-timeCells[0].beginTime)/totalTime))*ui->tableWidget->width();
            lastCellFlag = true;
          //  ////qDebug() << "last cell is" << i-1;
        }
        else
            tmpPos = (((float)(timeCells[i].beginTime-timeCells[0].beginTime)/totalTime))*ui->tableWidget->width();
//        ////qDebug() << "pos" << pos;
//        ////qDebug() << "tmpPos"<< tmpPos;
//        ////qDebug() << "timeCells[i].beginTime" << timeCells[i].beginTime;
//        ////qDebug() << "timeCells[0].beginTime" << timeCells[0].beginTime;
        if(pos>=tmpPos)
        {

        }
        else
        {

            if(i>=0)//freeze at selected i this position
            {
                if(i==0)
                {
                    ////qDebug()<< "ZEROOOO";
                }
                else
                {
//                    ////qDebug() << "move to cell" << i-1;
//                    ////qDebug() << "pos" << pos;
//                    ////qDebug() << "tmpPos"<< tmpPos;
                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i-1))/ui->tableWidget->width()))*totalTime;
                    ////qDebug()<< "excess time2 " << excessTime;
    //                ////qDebug() << "delay MS" << delayMs;
    //                ////qDebug() << "excess delay ms" << excessTime*100;
                    if(ui->tableWidget->currentColumn()!=i-1)
                    {



                         ////qDebug() << pageIndex;
                         ////qDebug() << timeCells[i-1].currentPage;
                         //qDebug() << "var6";
                         moveToAnotherTimeSegment(i-1);
                         ui->tableWidget->setCurrentCell(0,i-1);

                         ////qDebug() << "current i " << i;
                         ////qDebug() << "current column"<< ui->tableWidget->currentColumn();


                    }
//                    ////qDebug() << "pos2";
                    //correctCellSeekerPosition((float)(pos/totalTime)*ui->tableWidget->width());
                    delayMsToSet = excessTime*100;

                    i = ui->tableWidget->columnCount();
                }
//                else
//                {
//                    ////qDebug() << "move to cell" << i;
//                    ////qDebug() << "pos" << pos;
//                    ////qDebug() << "tmpPos"<< tmpPos;
//                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i))/ui->tableWidget->width()))*totalTime;
//    //                ////qDebug()<< "excess time " << excessTime;
//    //                ////qDebug() << "delay MS" << delayMs;
//    //                ////qDebug() << "excess delay ms" << excessTime*100;
//                    if(ui->tableWidget->currentColumn()!=i)
//                    {
//                        moveToAnotherTimeSegment(i);
//    //                    ui->tableWidget->setCurrentCell(0,i-1);
//                    }

//                    correctCellSeekerPosition((float)(pos/totalTime)*ui->tableWidget->width());
//                    delayMsToSet = excessTime*100;

//                    i = ui->tableWidget->columnCount();
//                }

            }
            else if(i==0)
            {
//                if(lastCellFlag)
//                {
                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i))/ui->tableWidget->width()))*totalTime;
                    if(ui->tableWidget->currentColumn()!=i)
                    {
                        //qDebug() << "var7";
                        moveToAnotherTimeSegment(i);
                         ui->tableWidget->setCurrentCell(0,i);

                    }
                    ////qDebug() << "pos1";
//                    correctCellSeekerPosition((float)(pos/totalTime)*ui->tableWidget->width());
                    delayMsToSet = excessTime*100;
                    i = ui->tableWidget->columnCount();
//                    ////qDebug() << "ZERO POS";
//                }
//                else
//                {
//                    excessTime = (((float)(pos-ui->tableWidget->columnViewportPosition(i))/ui->tableWidget->width()))*totalTime;
//                    if(ui->tableWidget->currentColumn()!=i)
//                         moveToAnotherTimeSegment(i);
//                    correctCellSeekerPosition((float)(pos/totalTime)*ui->tableWidget->width());
//                    delayMsToSet = excessTime*100;
//                    i = ui->tableWidget->columnCount();
//                }

            }
        }
    }
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
//    ////qDebug() << event->type();
//    if(event->type()==QEvent::MouseButtonPress)
//    {
//    for(int i = 0; i < thermoVals.size(); i++)
//    {
//        if(target == thermoVals.at(i))
//        {
//            ////qDebug() << "OWO";
////            thermoVals.at(i)->clear();
////            thermoVals.at(i)->setText("12");
////            return true;
//        }
//    }
//    //qDebug() << target->objectName();
//    if(target->objectName()=="")
//    {

//        //qDebug() << "blank"<< target->objectName();
//    }qDebug() << "space released";
//    if(event->type()==QEvent::KeyPress)
//    {
//        QKeyEvent *kevent = (QKeyEvent*)event;
//        if(kevent->key()==Qt::Key_Space)
//            qDebug() << "space pressed";
//    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *) event;
       // QWidget *widget = qApp->widgetAt(QCursor::pos());
       // QString widget_name = widget->objectName();
        QString parent_name = target->objectName();

        if((target== ui->line_5)||(target==  ui->tableWidget->viewport())||(parent_name=="ScaleWidget"))
        {
//            if(canMoveSeeker)
//            {
//                ui->playButton->click();
            ui->line_5->clearFocus();
            ui->tableWidget->viewport()->clearFocus();
            ui->ScaleWidget->clearFocus();
            ui->tableWidget->clearFocus();
                canMoveSeeker = false;
                seekerIsBusy = false;
//                //qDebug() << "event button released";
//                if(mythread->isFinished())
//                {
//                    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
//                    mythread->start();
//                    vplayer->play();
//                    vplayer2->play();
//                }
//                    ui->playButton->click();
//                ui->line_5->setAttribute(Qt::WA_TransparentForMouseEvents,false);
//            }
//
//            {
//                ////qDebug() << "line53";
////                ui->playButton->click();
//                int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
//                int currentPos = mouseEvent->x();//delayMs/100;

//                getCellAndTimeToMoveTo(mouseEvent->x(),totalTime);
//                currentPos = ((float)(currentPos/totalTime))*ui->tableWidget->width();
////                correctCellSeekerPosition(currentPos);
//                ////qDebug() << "mouse pos tableWidget CLICK!" << mouseEvent->x();
//                delayMs = delayMsToSet;\
//                updateTime();
//                delayMs = delayMsToSet;\
//           //     delayMsToSet = 0;
//                updateTime();
//    //            ////qDebug() << "delayMs"<<delayMs;
//                ui->horizontalSlider->setValue(delayMs/100);
//    //            ////qDebug() << "delayMs"<<delayMs;
//                setSliderPosition();
//                canMoveSeeker = false;
//            }
        }
    }
    else if(event->type() == QEvent::MouseMove|QEvent::MouseButtonPress & target != 0x0)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *) event;
       // QWidget *widget = qApp->widgetAt(QCursor::pos());
       // QString widget_name = widget->objectName();
        QString parent_name = target->objectName();
//        if(mythread->isRunning())
//        {
//            mythread->exit();
//            vplayer->_player->pause();
//            vplayer2->_player->pause();
//        }
//        ui->line_5;
//        //qDebug() << parent_name;//"event button pressed" << mythread->isRunning();
//            ui->playButton->click();
        //qDebug() << parent_name;
        if(target== ui->line_5)
        {
//            target = ui->tableWidget->viewport();
//            event->accept();
            //qDebug() << "jump?";
//            //qDebug() << "global coords1" <<  ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();
            //return QObject::eventFilter(target, event);
            target->setParent(ui->ScaleWidget);
//            correctCellSeekerPosition(ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x()-5);


        }
        if((target==  ui->tableWidget->viewport())||(parent_name=="ScaleWidget")||(parent_name == "qt_scrollarea_viewport")||(target== ui->line_5))
        {
            seekerIsBusy = true;
            ui->tableWidget->viewport()->clearFocus();
            ui->tableWidget->clearFocus();
            int tmpval = ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();//-ui->tableWidget->columnViewportPosition(ui->tableWidget->currentColumn());
//            qDebug() << "global coords1" << tmpval;
//            qDebug() << mouseEvent->x();
//            tmpval = mouseEvent->x();
//            canMoveSeeker = true;
            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
//            int currentPos = mouseEvent->x();//delayMs/100;ui->tableWidget->columnViewportPosition(i-1)
            getDelayMsToSet(tmpval,totalTime); //ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x(),totalTime);
            ////qDebug() << delayMs;
            ////qDebug() << delayMsToSet;

           // correctCellSeekerPosition(ui->tableWidget->mapFromGlobal(QCursor::pos()).x());
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
//            ////qDebug()<<"slider event!";
//            QStyleOptionSlider opt;
//             ui->horizontalSlider->initStyleOption(&opt);
//             QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
//            if (event->button() == Qt::LeftButton &&sr.contains(mouseEvent->pos()) == false)
//            {
             double halfHandleWidth = 2.5; // Correct rounding
             int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;

//                int newVal;
//                newVal = ui->horizontalSlider->minimum() + ((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum()) * mouseEvent->x()) / ui->horizontalSlider->width();
//                ////qDebug() << mouseEvent->x();
//                if (invertedAppearance() == true)
//                    setValue( maximum() - newVal );
//                else
//                    setValue(newVal);
                int adaptedPosX = mouseEvent->x();
                if ( adaptedPosX < halfHandleWidth )
                        adaptedPosX = halfHandleWidth;
                if ( adaptedPosX > ui->horizontalSlider->width() - halfHandleWidth )
                        adaptedPosX = ui->horizontalSlider->width() - halfHandleWidth;
//                // get new dimensions accounting for slider handle width
                double newWidth = (ui->horizontalSlider->width() - halfHandleWidth) - halfHandleWidth;
                double normalizedPosition = (adaptedPosX - halfHandleWidth)  / newWidth ;
                int newVal = ui->horizontalSlider->minimum() + ((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum()) * normalizedPosition);
                ui->horizontalSlider->setValue(newVal/*ui->horizontalSlider->minimum()+((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum())*mouseEvent->x())/ui->horizontalSlider->width()*/);
                newVal = ((float)ui->horizontalSlider->value()/totalTime)*ui->tableWidget->width();
                //qDebug() << "v3";
                correctCellSeekerPosition(newVal);
                if((timeCells[ui->tableWidget->currentColumn()].cellType!=1))//&(timeCells[ui->tableWidget->currentColumn()].cellType!=2))
                {
                    updateTime();
                    setSliderPosition();
                    updateTime();
                }

            return QObject::eventFilter(target, event);
//            }
        }
    }
    else if(event->type() == QEvent::GrabMouse)
    {
        //qDebug() << "grab event";
    }
    else if(event->type() == QEvent::MouseButtonPress & target!=0x0)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *) event;
//        if(mythread->isRunning())
//            mythread->exit();
//            ui->playButton->click();
       // QWidget *widget = qApp->widgetAt(QCursor::pos());
       // QString widget_name = widget->objectName();
        QString parent_name = target->objectName();
        //qDebug() <<"2" <<parent_name;
       // if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot_2")&(ui->qwtPlot_2->isEnabled()))
        if(target== ui->line_5)
        {
//            target = ui->tableWidget->viewport();
//            event->accept();
            //qDebug() << "jump??";
//            //qDebug() << "global coords1" <<  ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();
            //return QObject::eventFilter(target, event);
            target->setParent(ui->ScaleWidget);
//            correctCellSeekerPosition(ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x()-5);
//        setPause();
            return QObject::eventFilter(target, event);
        }
        if((parent_name=="ScaleWidget")||(target == ui->tableWidget->viewport())||(parent_name == "qt_scrollarea_viewport"))
        {
            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
//            int currentPos = mouseEvent->x();//delayMs/100;
            int tmpval = ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()).x();
            //qDebug() << parent_name;
//            //qDebug() << "currentPos"<<currentPos;
            //qDebug() << "tmpval"<<tmpval;
            /*getCellAndTimeToMoveTo*/getDelayMsToSet(tmpval,totalTime);
//            currentPos = ((float)(currentPos/totalTime))*ui->tableWidget->width();
//            ////qDebug() << "mouse pos scalewidget CLICK!" << mouseEvent->x();
            delayMs = delayMsToSet;\

            updateTime();
            delayMs = delayMsToSet;\
       //     delayMsToSet = 0;
            updateTime();
//            ////qDebug() << "delayMs"<<delayMs;
            ui->horizontalSlider->setValue(delayMs/100);
//            ////qDebug() << "delayMs"<<delayMs;
            setSliderPosition();
//            ////qDebug() << "WIDTH OF TABLE" << ui->tableWidget->width();
//            ////qDebug() << "WIDTH OF SCALE" << ui->ScaleWidget->width();
//            canMoveSeeker= true;
//            ////qDebug() << "delayMs"<<delayMs;
//            correctCellSeekerPosition(currentPos);
//            correctCellSeekerPosition(currentPos);
//            setSliderPosition();
//            updateTime();
            return QObject::eventFilter(target, event);
        }

//        if((target == ui->tableWidget->viewport())||(parent_name == "qt_scrollarea_viewport"))
//        {
//            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
//            int currentPos = mouseEvent->x();//delayMs/100;
////            if(mythread->isRunning())
////                mythread->exit();
////                ui->playButton->click();
//            //qDebug() << "viewport";
//            /*getCellAndTimeToMoveTo*/getDelayMsToSet(mouseEvent->x(),totalTime);
//            currentPos = ((float)(currentPos/totalTime))*ui->tableWidget->width();
////            ////qDebug() << "mouse pos tableWidget CLICK!" << mouseEvent->x();
//            delayMs = delayMsToSet;\
//            updateTime();
//            delayMs = delayMsToSet;\
//       //     delayMsToSet = 0;
//            updateTime();
////            ////qDebug() << "delayMs"<<delayMs;
//            ui->horizontalSlider->setValue(delayMs/100);
////            ////qDebug() << "delayMs"<<delayMs;
//            setSliderPosition();
////            canMoveSeeker = true;
////            ////qDebug() << "delayMs"<<delayMs;
//            return QObject::eventFilter(target, event);
//        }

//        if(parent_name =="viewPort")
//        {
////            ////qDebug() << "tw";
////            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
////            int currentPos = mouseEvent->x();//delayMs/100;
////            getCellAndTimeToMoveTo(mouseEvent->x(),totalTime);
////            currentPos = ((float)(currentPos/totalTime))*ui->ScaleWidget->width();
//           // ////qDebug() << "mouse pos TABLE WIDGET CLICK!!!!!" << mouseEvent->x();
////            int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;
////            int currentPos = mouseEvent->x();//delayMs/100;
////            getCellAndTimeToMoveTo(mouseEvent->x(),totalTime);
////            currentPos = ((float)(currentPos/totalTime))*ui->ScaleWidget->width();
////            ////qDebug() << "mouse pos TABLEWIDGET CLICK!" << mouseEvent->x();
////            delayMs = delayMsToSet;\
////            updateTime();
////            delayMs = delayMsToSet;\
////       //     delayMsToSet = 0;
////            updateTime();
////            ////qDebug() << "delayMs"<<delayMs;
////            ui->horizontalSlider->setValue(delayMs/100);
////            ////qDebug() << "delayMs"<<delayMs;
////            setSliderPosition();
////            ////qDebug() << "delayMs"<<delayMs;
////            correctCellSeekerPosition(currentPos);
//                        //updateTime();
//        }
        if(parent_name=="horizontalSlider")
        {
            setHSliderPosOnButtonPress(mouseEvent);
            return QObject::eventFilter(target, event);

//            }
        }
    }
    else if((event->type()==QEvent::MouseMove)&target!=0x0)//&isSliderPressed
    {
        ////qDebug() << "mousemove sliderpos";
        setSliderPosition();
        return QObject::eventFilter(target, event);
//        return QObject::eventFilter(target, event);
    }
    else if(target == 0x0)
    {
        //qDebug() << "blank2";
    }
//    else if(target == ui->tableWidget)
//        ////qDebug() << "event";


     return QObject::eventFilter(target, event);//QMainWindow::eventFilter(target, event);
}

void MainWindow::setHSliderPosOnButtonPress(QMouseEvent *me)
{
    ////qDebug()<<"slider event!!!";
    if(mythread->isRunning())
    {
        ////qDebug() << "thread running";
    }
//            QStyleOptionSlider opt;
//             ui->horizontalSlider->initStyleOption(&opt);
//             QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
//            if (event->button() == Qt::LeftButton &&sr.contains(mouseEvent->pos()) == false)
//            {
    double halfHandleWidth = 2.5; // Correct rounding
     int totalTime = timeCells[timeCells.size()-1].endTime - timeCells[0].beginTime;

//                int newVal;
//                newVal = ui->horizontalSlider->minimum() + ((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum()) * mouseEvent->x()) / ui->horizontalSlider->width();
//                ////qDebug() << mouseEvent->x();
//                if (invertedAppearance() == true)
//                    setValue( maximum() - newVal );
//                else
//                    setValue(newVal);
        int adaptedPosX = me->x();
        ////qDebug() << me->x();
        if ( adaptedPosX < halfHandleWidth )
                adaptedPosX = halfHandleWidth;
        if ( adaptedPosX > ui->horizontalSlider->width() - halfHandleWidth )
                adaptedPosX = ui->horizontalSlider->width() - halfHandleWidth;
//                // get new dimensions accounting for slider handle width
        double newWidth = (ui->horizontalSlider->width() - halfHandleWidth) - halfHandleWidth;
        double normalizedPosition = (adaptedPosX - halfHandleWidth)  / newWidth ;
        int newVal = ui->horizontalSlider->minimum() + ((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum()) * normalizedPosition);
        ui->horizontalSlider->setValue(newVal/*ui->horizontalSlider->minimum()+((ui->horizontalSlider->maximum()-ui->horizontalSlider->minimum())*mouseEvent->x())/ui->horizontalSlider->width()*/);
        newVal = ((float)ui->horizontalSlider->value()/totalTime)*ui->tableWidget->width();
//                ////qDebug() << "newVal2";
        //qDebug() << "v1";
        correctCellSeekerPosition(newVal);
        updateTime();
        setSliderPosition();
        updateTime();
}

void MainWindow::setSliderPosition()
{
    int changedTime1=0,changedTime2=0;
    int oneVideoLength=0;
    if((vplayer->_player->length()!=-1)&(vplayer2->_player->length()!=-1))
    {
        if(vplayer->_player->length()<vplayer2->_player->length())
            oneVideoLength = vplayer->_player->length();
        else
            oneVideoLength = vplayer2->_player->length();
    }
    else
    {
            oneVideoLength = (dataMap[pageIndex].timeEdge2 - dataMap[pageIndex].timeEdge1)*1000;

    }
    //////qDebug() << "oneVideoLength" << oneVideoLength;
    changedTime1 = ui->horizontalSlider->value()*1000;/*((float)ui->horizontalSlider->value()/ui->horizontalSlider->maximum())*((float)oneVideoLength/(ui->horizontalSlider->maximum()))*(ui->horizontalSlider->value());*/
    if(changedTime1>vplayer->_player->length())
        changedTime1 = vplayer->_player->length();
    changedTime2 = ui->horizontalSlider->value()*1000;/*((float)ui->horizontalSlider->value()/ui->horizontalSlider->maximum())*((float)oneVideoLength/(ui->horizontalSlider->maximum()))*(ui->horizontalSlider->value());*/
    if(changedTime2>vplayer2->_player->length())
        changedTime2 = vplayer2->_player->length();
    if(timeCells[ui->tableWidget->currentColumn()].cellType==0)//if we're working with  0 celltype, changing video time
    {
        if((!videoOnly)|(offsetsAvailable))
        {
            vplayer->_player->setTime(changedTime1 + maxCamOffset - camOffsets.at(ui->comboBox->currentIndex()-1));
            vplayer2->_player->setTime(changedTime2 + maxCamOffset - camOffsets.at(ui->comboBox_2->currentIndex()-1));
            delayMs = (changedTime1 + camOffsets.at(ui->comboBox->currentIndex()-1))/10;
        }
        else
        {
            vplayer->_player->setTime(changedTime1);
            vplayer2->_player->setTime(changedTime2);
            delayMs = changedTime1;// + camOffsets.at(ui->comboBox->currentIndex()-1))/10;
        }
    }
    else
    {
        changedTime1 = ui->horizontalSlider->value()*100;
        ////qDebug() << "set slider pos changedtime1" << changedTime1<<ui->horizontalSlider->value();

        delayMs = changedTime1;

    }
//    if(mythread->isFinished())
//        mythread->start();

    updateTime();
//    delayMsToSet = 0;
}

void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{

}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    ////qDebug() << "cell changed!";
////    ////qDebug() << "SETTING PAGE INDEX" << column;
//    pageIndex = column;
//    if(pageIndex>dataMap.size()-1)
//        pageIndex = dataMap.size()-1;
//    int tmp1=0,tmp2=0;
//    QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
//    QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);

//    while(tmp1<=ui->comboBox->currentIndex())
//    {
//        Iter1.next();
//        tmp1++;
//    }
//    while(tmp2<=ui->comboBox_2->currentIndex())
//    {
//        Iter2.next();
//        tmp2++;
//    }
//        openVideoFile(Iter1.key(),Iter2.key());
//        openLogFile(dataMap[pageIndex].logName);
//        if(mythread->isRunning())
//            mythread->exit();
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
//    dp.doubleTypes = QVector <double>(0);
//    dp.error = QVector <int>(0);
//    dp.flagTypes = QVector <bool>(0);
//    dp.floatTypes = QVector <float>(0);
//    dp.intTypes = QVector <int>(0);
//    dp.paramsSequence = QVector<int>(0);
//    dp.paramsVisibleArr = QVector<int>(0);
//    dp.powOnTime = QVector<time_t>(0);
//    dp.time = QVector<time_t>(0);
//    dp.timeFract = QVector<unsigned char>(0);
    updateThermos(dp);
}

void MainWindow::moveToAnotherTimeSegment(int column)
{
    bool nextpage = false;
    ////qDebug() << "column to move" << column;

    ////qDebug() << "current col" << ui->tableWidget->currentColumn();
    clearParTable();
    if((timeCells[column].cellType==0)|(timeCells[column].cellType==3))//|(timeCells[column].cellType==2))//||(timeCells[column].cellType==3))
        {

            if(pageIndex!=timeCells[column].currentPage)
            {
                ////qDebug() << "1st";
                nextpage = true;
            }
            else
            {
                ////qDebug() << "PAGE INDEX IS EQUAL!!";
                if(timeCells[column].currentPage==timeCells.count()-1)
                {
                    ////qDebug() << "2nd";
                    nextpage=true;
                    vplayer->stop();
                    vplayer2->stop();
                }
                else if(ui->tableWidget->currentColumn()!=column)
                {
                    ////qDebug() << "3rd";
                    nextpage=true;
                    vplayer->stop();
                    vplayer2->stop();
                }
                else if(column == timeCells.count()-1)
                {
                    ////qDebug() << "5th";
                    nextpage=true;
                    vplayer->stop();
                    vplayer2->stop();
                }
                else if(column != timeCellIndex)
                {
                    ////qDebug() << "6th";
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
                    ////qDebug() << "4th";
                    vplayer->stop();
                    vplayer2->stop();
                    createFakeTimeScale(timeCells[column].cellType,column);
                    nextpage=true;

                }

            }
    else createFakeTimeScale(timeCells[column].cellType,column);
//        ////qDebug() << "CURRENT COLUMN INDEX"<<column;
//        ////qDebug() << "CURRENT PAGE INDEX"<< pageIndex;
//        ////qDebug() << "PAGE FLAG VECTOR" << timeCells[column].cellType;
//        ////qDebug() << "NEXTPAGE" << nextpage;
//        ////qDebug() << "DATAPAGES TOTAL AMOUNT" << dataMap.count();
//        ////qDebug() << "CURRENT PAGE IN TIMECELLS" << timeCells[column].currentPage;
        pageIndex = timeCells[column].currentPage;
    timeCellIndex = column;
        int tmp1=0,tmp2=0;
    //    ui->tableWidget->setCurrentCell(0,pageIndex);
        QMapIterator <QString, bool> Iter1(dataMap[pageIndex].videoVector);
        QMapIterator <QString, bool> Iter2(dataMap[pageIndex].videoVector);

        while(tmp1<=ui->comboBox->currentIndex())
        {
            Iter1.next();
            tmp1++;
        }
        while(tmp2<=ui->comboBox_2->currentIndex())
        {
            Iter2.next();
            tmp2++;
        }
//        ////qDebug() << ui->comboBox->currentIndex();
//        ////qDebug() << ui->comboBox_2->currentIndex();
//        ////qDebug() << Iter1.key();
//        ////qDebug() << Iter2.key();
        if(nextpage)
        {
            ////qDebug() << "cellType" << timeCells[column].cellType;
            ////qDebug() << Iter1.key();
             if(timeCells[column].cellType==0)
             {
                vplayer->stop();
                vplayer2->stop();
                openVideoFile(Iter1.key(),Iter2.key());
             }
             else
             {
                 vplayer->stop();
                 vplayer2->stop();
             }

            ////qDebug() << "VIDEO HAS CHANGED from moveToAnotherTimeSegment";
            if((timeCells[column].cellType==0)|(timeCells[column].cellType==3))
                openLogFile(dataMap[pageIndex].logName);
            if(timeCells[column].cellType==0)
            {
                ////qDebug() << "here???";
                if(mythread->isRunning())
                {
                    mythread->exit();
                    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                    correctFramePosition();
                }
                if(vplayer->getVideoState()==3)
                {
                    mythread->start();
                    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                    correctFramePosition();
                }
            }
            else
            {
                if(mythread->isFinished())
                {
                    ////qDebug() << "finished thread1";
                    mythread->start();
                    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                    correctFramePosition();
                }
                else
                {
                    if(mythread->isRunning())
                    {
                        ////qDebug() << "finished thread2";
                        mythread->start();
                        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                        correctFramePosition();
                    }
                }
            }
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
    qDebug() << "updating sound mode" << sound1IconState << sound2IconState;
    if(sound1IconState>0)
    {
        if(sound1IconState==1)
            vplayer->setAudioMuted(true);
            //vplayer->setAudioState(Vlc::Paused);
        else
        {
            vplayer->setAudioMuted(false);
//            vplayer->setAudioState(Vlc::Playing);
        }
    }
//    else
//        vplayer->setAudioState(Vlc::Stopped);
    if(sound2IconState>0)
    {
        if(sound2IconState==1)
            vplayer2->setAudioMuted(true);
        else
            vplayer2->setAudioMuted(false);
    }
//    else
//        vplayer2->setAudioState(Vlc::Stopped);
    setSoundIcons();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    keyboardKey = event->key();
    if(event->key()==Qt::Key_Space)
        qDebug() << "space pressed";
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
