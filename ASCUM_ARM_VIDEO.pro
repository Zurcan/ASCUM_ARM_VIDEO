#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T14:07:51
#
#-------------------------------------------------

QT       += core gui #xml script
QT       += multimedia #multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
{
 QT += widgets
#QT += widgets printsupport
DEFINES += HAVE_QT5
}

TARGET = ASCUM_ARM_VIDEO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    NcFramelessHelper.cpp \
    ../../ASCUM_ARM/LOG_PROCESSOR/logprocessor.cpp\
    TMIinterpretator.cpp \
    VideoPlayer.cpp \
    msgSys.cpp \
    ../../flyingFrame/FlyingFrame.cpp
#    player.cpp

HEADERS  += mainwindow.h \
    NcFramelessHelper.h \
    ../../ASCUM_ARM/LOG_PROCESSOR/logprocessor.h\
    TMIinterpretator.h \
    VideoPlayer.h \
    msgSys.h \
    ints.h \
    ../../ASCUM_ARM/_SHARED_LIBRARIES/log.segments.h \
    ../../flyingFrame/FlyingFrame.h
#    player.h
#CONFIG += link_pkgconfig
#    PKGCONFIG += gstreamer-0.10

FORMS    += \
    myform.ui
#INCLUDEPATH+= C:\Qt\QtGStreamer\bin\libQt5GStreamer-0.10
#LIBS+= -LC:\Qt\QtGStreamer\bin
#INCLUDEPATH+= C:\Qt\QtGStreamer1\bin
#INCLUDEPATH+= C:\Qt\QtGStreamer1\lib
#LIBS+= -LC:\Qt\QtGStreamer1\bin
#LIBS+= -LC:\boost\lib
#INCLUDEPATH+= C:\boost\include\boost-1_55\
#LIBS+= -LC:\Qt\qt-5.0.2\qtbase\gstreamer-sdk\0.10\x86\lib
#LIBS+= C:\Program Files\GPLGS\gsdll32.dll
#INCLUDEPATH+= C:\Qt\QtGStreamer\lib
#INCLUDEPATH+= C:\Qt\qt-creator-2.7.0\bin
##INCLUDEPATH+= C:\Qt\qt-creator-2.7.0\original
##LIBS += libpqdll.lib
#INCLUDEPATH+= C:\Qt\mingw-4.7\i686-w64-mingw32\include   #инклудим все стандартные библиотеки
#LIBS+= -LC:\Qt\Qwt-6.0.2\lib -lqwtd #lqwtd - for debug lqwt - for release
#INCLUDEPATH+= C:\Qt\Qwt-6.0.2\include
#INCLUDEPATH+= C:\Qt\QtGStreamer\include\Qt5GStreamer\QGlib
#INCLUDEPATH+= C:\Qt\QtGStreamer\include\Qt5GStreamer\QGst
#INCLUDEPATH+= C:\Qt\QtGStreamer1\include\Qt5GStreamer
#LIBS    +=-lvlc-qt -lvlc-qt-widgets
#LIBS     += -LC:\Qt\vlc-qt_debug\lib
#INCLUDEPATH += C:\Qt\vlc-qt_debug\include
#INCLUDEPATH += C:\Qt\vlc-qt_debug\bin
#OTHER_FILES += \
#    qwt.pri
LIBS+= -LC:\Qt\Qwt-6.0.2\lib -lqwt #lqwtd - for debug lqwt - for release
INCLUDEPATH+= C:\Qt\qt-creator-2.7.0\bin
#LIBS += libpqdll.lib
INCLUDEPATH+= C:\Qt\Qwt-6.0.2\include
INCLUDEPATH+= C:\Qt\mingw-4.7\i686-w64-mingw32\include   #инклудим все стандартные библиотеки
LIBS     += -LC:\Qt\vlc-qt_release\lib -lvlc-qt -lvlc-qt-widgets
INCLUDEPATH += C:\Qt\vlc-qt_release\include
INCLUDEPATH += C:\Qt\vlc-qt_release\bin
INCLUDEPATH += C:\Program Files\VideoLAN\VLC

RESOURCES += \
    res.qrc
