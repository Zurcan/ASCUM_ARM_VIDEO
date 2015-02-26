#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCheckBox c("Test resized");
//   c.setStyleSheet("QCheckBox::indicator { width: 32px; height: 32px; } ");
//   c.show();

//   QCheckBox d("Test Default");
//   d.show();
    MainWindow w;
//    w.setWindowState(w.windowState()|Qt::WindowMaximized);
//    w.setWindowFlags(w.windowFlags()|Qt::WindowCloseButtonHint|Qt::WindowMaximizeButtonHint|Qt::CustomizeWindowHint);

    w.show();
    
    return a.exec();
}
