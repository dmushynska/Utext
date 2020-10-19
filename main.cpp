#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.addFileEdit("text", "/Users/solianovsk/Downloads/utext/utext/text");
    w.addFileEdit("main.cpp", "/Users/solianovsk/Downloads/utext/utext/main.cpp");
    w.addFileEdit("text", "/Users/solianovsk/Downloads/utext/utext/text");
    w.show();
		
    return a.exec();
}
