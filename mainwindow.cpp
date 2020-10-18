#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("1");
    ui->listWidget->addItem("1");
    ui->listWidget->addItem("1");
    ui->listWidget->addItem("1");
    ui->listWidget->addItem("1");
    ui->listWidget->addItem("1");
    ui->listWidget->addItem("1");
    qDebug() << ui->listWidget->item(1)->text();
//    QTextCursor addCursor(ui->textEdit->textCursor());
//    addCursor.movePosition(QTextCursor::Down);
    QFile file("/Users/solianovsk/Downloads/utext/utext/text");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","PErmision ERROR !");
        messageBox.setFixedSize(500,200);
    }
    else {
        QString text(file.readAll());
        ui->textEdit->setText(text);
    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Save_triggered()
{
//    addCursor = new QTextCursor(ui->textEdit->textCursor());
//    QTextCursor addCursor(ui->textEdit->textCursor());
//    addCursor->movePosition(QTextCursor::Down);
//    addCursor.insertText("Привет");
    QFile file("/Users/solianovsk/Downloads/utext/utext/text");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","PErmision ERROR !");
        messageBox.setFixedSize(500,200);
    }
    else {
        file.write(ui->textEdit->toPlainText().toUtf8());
        file.close();
    }
}
