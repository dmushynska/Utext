#ifndef WINDOW_FIND_REPLACE_H
#define WINDOW_FIND_REPLACE_H

#include <QDialog>

namespace Ui {
class window_Find_Replace;
}

class window_Find_Replace : public QDialog
{
    Q_OBJECT

public:
    explicit window_Find_Replace(QWidget *parent = nullptr);
    ~window_Find_Replace();

private slots:
    void on_button_Find_clicked();

    void on_button_Replace_clicked();

private:
    Ui::window_Find_Replace *ui;
};

#endif // WINDOW_FIND_REPLACE_H
