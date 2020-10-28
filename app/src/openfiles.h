#ifndef OPENFILES_H
#define OPENFILES_H

#include <QWidget>
#include <QTextEdit>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class openFiles;
}

class openFiles : public QWidget
{
    Q_OBJECT

public:
    explicit openFiles(QWidget *parent = nullptr);
    explicit openFiles(QString path, QWidget *parent = nullptr);
    ~openFiles();

private slots:
    void on_closeFile_clicked();

private:
    Ui::openFiles *ui;
    QTextEdit text;
};

#endif // OPENFILES_H
