#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTabBar *bar =  ui->tabWidget->tabBar();
    connect(bar, &QTabBar::tabCloseRequested, this, &MainWindow::closeFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeFile(int index) {
ui->tabWidget->widget(index)->~QWidget();
}

void MainWindow::addFileEdit(const QString& name, const QString& fullPath) {
    Editor *newFile = new Editor;

    if (newFile->setValue(fullPath, ui)) {
        ui->tabWidget->addTab(newFile, name);
    }
    else {
         delete newFile;
    }
}


void MainWindow::on_action_Save_triggered()
{
//    addCursor = new QTextCursor(ui->textEdit->textCursor());
//    QTextCursor addCursor(ui->textEdit->textCursor());
//    addCursor->movePosition(QTextCursor::Down);
//    addCursor.insertText("Привет");
//    QFile file("/Users/solianovsk/Downloads/utext/utext/text");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QMessageBox messageBox;
//        messageBox.critical(this,"Error","PErmision ERROR !");
//        messageBox.setFixedSize(500,200);
//    }
//    else {
//        file.write(ui->textEdit->toPlainText().toUtf8());
//        file.close();
//    }
}
