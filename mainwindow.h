#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCursor>
#include <QTextEdit>
#include "editor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addFileEdit(const QString& name, const QString& fullPath);
    void closeFile(int index);

private slots:
    void on_action_Save_triggered();

private:
    Ui::MainWindow *ui;
    QTextCursor *addCursor;
};

#endif // MAINWINDOW_H
