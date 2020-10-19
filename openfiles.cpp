#include "openfiles.h"
#include "ui_openfiles.h"

openFiles::openFiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::openFiles)
{
    ui->setupUi(this);
}

openFiles::~openFiles()
{
    delete ui;
}


openFiles::openFiles(QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::openFiles)
{
    ui->setupUi(this);
    ui->nameFiles->setText(path);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","PErmision ERROR !");
        messageBox.setFixedSize(500,200);
    }
    else {
        QString textFile(file.readAll());
        text.setText(textFile);
    }
    file.close();
}

void openFiles::on_closeFile_clicked()
{

}
