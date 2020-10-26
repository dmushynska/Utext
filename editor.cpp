#include "editor.h"
#include "mainwindow.h"
#include "ui_editor.h"
#include "ui_mainwindow.h"


QTextEdit *Editor::getTextEdit () {
    return ui->textEditor;
}


Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
    mx_highlighter = new Highlighter(ui->textEditor->document());
}


const QString& Editor::getFullPath(void) {
    return fullPath;
}

int Editor::setValue(const QString& newFullPath, Ui::MainWindow *mui) {
    for (int i = 0; i < mui->tabWidget->count(); i++) {
        if (newFullPath == qobject_cast<Editor*>(mui->tabWidget->widget(i))->getFullPath())
            return i;
    }
    QFile file(newFullPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","PErmision ERROR !");
        messageBox.setFixedSize(500,200);
        file.close();
        return -1;
    }
    QString text(file.readAll());
    ui->textEditor->setText(text);
    ui->fullPathFile->setText(newFullPath);
    fullPath = newFullPath;
    return mui->tabWidget->count();
}

void Editor::saveFile(void) {
    QFile file(this->fullPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","PErmision ERROR !");
        messageBox.setFixedSize(500,200);
    }
    else {
        file.write(ui->textEditor->toPlainText().toUtf8());

    }
    file.close();
}

void Editor::findFile(const QString& text) {
    if (this->ui->textEditor->find(text) == 0) {
        auto cursor = this->ui->textEditor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        this->ui->textEditor->setTextCursor(cursor);
        this->ui->textEditor->find(text);
    }
}

void Editor::replaceFile(const QString& textFind, const QString& textReaplace) {
    if (this->ui->textEditor->find(textFind) == 0) {
        auto cursor = this->ui->textEditor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        this->ui->textEditor->setTextCursor(cursor);
        if (this->ui->textEditor->find(textFind)) {
            auto cursor = this->ui->textEditor->textCursor();
            cursor.insertText(textReaplace);
            cursor.setPosition(cursor.position() - textReaplace.size());
            cursor.setPosition(cursor.position() + textReaplace.size(), QTextCursor::KeepAnchor);
            this->ui->textEditor->setTextCursor(cursor);
        }
    }
    else {
        auto cursor = this->ui->textEditor->textCursor();
        cursor.insertText(textReaplace);
        cursor.setPosition(cursor.position() - textReaplace.size());
        cursor.setPosition(cursor.position() + textReaplace.size(), QTextCursor::KeepAnchor);
        this->ui->textEditor->setTextCursor(cursor);
    }
}

Editor::~Editor()
{
    delete ui;
}
