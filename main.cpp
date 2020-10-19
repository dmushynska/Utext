#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.addFileEdit("text", "/Users/dmushynska/Desktop/olanser/editor.cpp");
    w.addFileEdit("main.cpp", "/Users/dmushynska/Desktop/olanser/editor.cpp");
    w.addFileEdit("text", "/Users/dmushynska/Desktop/olanser/main.cpp");
    w.show();
		
    return a.exec();
}
