#include "window_find_replace.h"
#include "ui_window_find_replace.h"
#include "mainwindow.h"

window_Find_Replace::window_Find_Replace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_Find_Replace)
{
    ui->setupUi(this);
    this->setModal(true);
}

window_Find_Replace::~window_Find_Replace()
{
    delete ui;
}

void window_Find_Replace::on_button_Find_clicked()
{
    bool isRegex = false;
    QTextDocument::FindFlags flag;

    if (ui->cRegex->checkState())
        isRegex = true;
    if (ui->cFindBackward->checkState())
        flag = flag| QTextDocument::FindBackward;
    if (ui->cFindCaseSensitively->checkState())
        flag = flag| QTextDocument::FindCaseSensitively;
    if (ui->cFindWholeWords->checkState())
        flag = flag| QTextDocument::FindWholeWords;
    qobject_cast<MainWindow*>(this->parent())->windowFind(ui->text_Find->text(), isRegex, flag);
}

void window_Find_Replace::on_button_Replace_clicked()
{
    bool isRegex = false;
    QTextDocument::FindFlags flag;

    if (ui->cRegex->checkState())
        isRegex = true;
    if (ui->cFindBackward->checkState())
        flag = flag| QTextDocument::FindBackward;
    if (ui->cFindCaseSensitively->checkState())
        flag = flag| QTextDocument::FindCaseSensitively;
    if (ui->cFindWholeWords->checkState())
        flag = flag| QTextDocument::FindWholeWords;
    qobject_cast<MainWindow*>(this->parent())->windowReplace(ui->text_Find->text(), ui->text_Replace->text(), isRegex, flag);
}
