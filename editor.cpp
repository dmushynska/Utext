#include "editor.h"
#include "ui_editor.h"
#include "ui_mainwindow.h"

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
}


const QString& Editor::getFullPath(void) {
    return fullPath;
}

bool Editor::setValue(const QString& newFullPath, Ui::MainWindow *mui) {
    for (int i = 0; i < mui->tabWidget->count(); i++) {
        if (newFullPath == qobject_cast<Editor*>(mui->tabWidget->widget(i))->getFullPath())
            return 0;
    }
    QFile file(newFullPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","PErmision ERROR !");
        messageBox.setFixedSize(500,200);
        file.close();
        return 0;
    }
    QString text(file.readAll());
    ui->textEditor->setText(text);
    ui->fullPathFile->setText(newFullPath);
    fullPath = newFullPath;
    return 1;
}

Editor::~Editor()
{
    delete ui;
}
