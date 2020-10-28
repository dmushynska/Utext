#include "mainwindow.h"

#include <QDebug>
#include <QFileSystemModel>
#include <QLabel>
#include <QTreeView>

#include "ui_mainwindow.h"
#include "window_find_replace.h"


void MainWindow::addTree(QString string) {
    QTreeView *view = new QTreeView;
    QFileSystemModel *model = new QFileSystemModel;
    model->setReadOnly(false);
    view->setModel(model);
    view->setRootIndex(model->setRootPath(string));
    view->setDragEnabled(true);
    view->setAcceptDrops(true);
    view->setDragDropMode(QAbstractItemView ::InternalMove);
    view->setDropIndicatorShown(true);
    for (int i = 1; i < model->columnCount(); i++)
        view->hideColumn(i);
    view->setHeaderHidden(false);
    for (int i = 0; i < ui->toolBox->count(); i++) {
        if (ui->toolBox->itemText(i) == string) {
            delete model;
            delete view;
            return;
        }
    }
    if (ui->toolBox->count() == 0)
        ui->toolBox->show();
    ui->toolBox->addItem(view, string);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view, &QTreeView::clicked, this, &MainWindow::click);
    connect(view, &QTreeView::customContextMenuRequested, this, &MainWindow::clickMouse);
    connect(model, &QFileSystemModel::fileRenamed, this, &MainWindow::renameFile);
}

void MainWindow::renameFile(const QString &path, const QString &oldName, const QString &newName) {
    QString oldFile = path + "/" + oldName;
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (oldFile == qobject_cast<Editor*>(ui->tabWidget->widget(i))->getFullPath()) {
            qobject_cast<Editor*>(ui->tabWidget->widget(i))->renameFile(path + "/" + newName);
            ui->tabWidget->setTabText(i, newName);
            return;
        }
    }
}

void MainWindow::click(const QModelIndex &index) {
    ui->toolBox->currentIndex();
    QFileSystemModel *model = new QFileSystemModel;
    QFileInfo check_file(model->filePath(index));

    if (check_file.exists() && check_file.isFile()) {
        addFileEdit(model->fileName(index), model->filePath(index));
    }
    delete model;
}

void MainWindow::clickMouse(const QPoint &point) {
    QPoint globalPos = qobject_cast<QTreeView *>(ui->toolBox->widget(ui->toolBox->currentIndex()))->mapToGlobal(point);
    QMenu myMenu;
    QTreeView *treeView = qobject_cast<QTreeView *>(this->ui->toolBox->widget(this->ui->toolBox->currentIndex()));
    QFileSystemModel *model = new QFileSystemModel;
    QString string = model->filePath(treeView->indexAt(point));
    QString dir_where_are_u = string;
    dir_where_are_u.resize(string.count() - model->fileName(treeView->indexAt(point)).count());
    QFileInfo check_file(string);

    myMenu.addAction("create file", this, [dir_where_are_u]() {
        QFileInfo check_file(dir_where_are_u + "new file");
        if (!check_file.exists()) {
            QFile mfile(dir_where_are_u + "new file");
            mfile.open(QIODevice::WriteOnly);
            mfile.close();
        } else {
            int i = 1;
            for (; check_file.exists(); i++) {
                check_file.setFile(dir_where_are_u + "new file" + QString::number(i));
            }
            QFile mfile(dir_where_are_u + "new file" + QString::number(--i));
            mfile.open(QIODevice::WriteOnly);
            mfile.close();
        }
    });

    if (check_file.isFile())
        myMenu.addAction("delete file", this, [point, model, treeView]() {
            QFile(model->filePath(treeView->indexAt(point))).remove();
        });

    myMenu.addAction("create directory", this, [dir_where_are_u]() {
        QDir dir;
        QFileInfo check_file(dir_where_are_u + "new directory");

        if (!check_file.exists())
            dir.mkdir(dir_where_are_u + "new directory");
        else {
            int i = 1;
            for (; check_file.exists(); i++) {
                check_file.setFile(dir_where_are_u + "new directory" + QString::number(i));
            }
            dir.mkdir(dir_where_are_u + "new directory" + QString::number(--i));
        }
    });

    if (check_file.isDir())
        myMenu.addAction("delete directory", this, [point, model, treeView]() {
            QDir(model->filePath(treeView->indexAt(point))).removeRecursively();
        });

    if (!check_file.isFile() && !check_file.isDir()) {
        myMenu.addAction("open mkdir", this, [this]() {
            this->add_mkdir();
        });
        myMenu.addAction("close mkdir " + ui->toolBox->itemText(ui->toolBox->currentIndex()), this, [this]() {
            this->ui->toolBox->removeItem(ui->toolBox->currentIndex());
            if (this->ui->toolBox->count() == 0) {
                this->ui->toolBox->hide();
            }
        });
    }
    myMenu.exec(globalPos);
    delete model;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QTabBar *bar = ui->tabWidget->tabBar();
    connect(bar, &QTabBar::tabCloseRequested, this, &MainWindow::closeFile);
    addTree(QDir::currentPath());
    connect(ui->actionadd_mkdir, &QAction::triggered, this, &MainWindow::add_mkdir);
    connect(ui->action_Cut, &QAction::triggered, this, [this]() {
        for (int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->cut();
        }
    });
    connect(ui->action_Copy, &QAction::triggered, this, [this]() {
        for (int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->copy();
        }
    });
    connect(ui->action_Undo, &QAction::triggered, this, [this]() {
        for (int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->undo();
        }
    });
    connect(ui->action_Redo, &QAction::triggered, this, [this]() {
        for (int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->redo();
        }
    });
    connect(ui->action_Paste, &QAction::triggered, this, [this]() {
        for (int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor *>(this->ui->tabWidget->widget(i))->getTextEdit()->paste();
        }
    });
    auto style_sheet = QString("font-size: 16px;");
    this->setStyleSheet(style_sheet);
    mx_helpWidget = new Help;
    ui->lRight->addWidget(mx_helpWidget);
    mx_helpWidget->show();
    ui->tabWidget->hide();
}

MainWindow::~MainWindow() {
    delete ui;
    delete mx_helpWidget;
}

void MainWindow::closeFile(int index) {
    ui->tabWidget->widget(index)->~QWidget();
    if (ui->tabWidget->count() == 0) {
        if (ui->tabWidget->isVisible()) {
            ui->tabWidget->hide();
            if (!mx_helpWidget->isVisible()) {
                mx_helpWidget->show();
            }
        }
    }
}

void MainWindow::addFileEdit(const QString &name, const QString &fullPath) {
    Editor *newFile = new Editor;

    int pos = newFile->setValue(fullPath, ui);
    if (pos > -1) {
        if (!ui->tabWidget->isVisible()) {
            ui->tabWidget->show();
            if (mx_helpWidget->isVisible()) {
                mx_helpWidget->hide();
            }
        }
        if (pos == ui->tabWidget->count())
            ui->tabWidget->addTab(newFile, name);
        else
            delete newFile;
        ui->tabWidget->setCurrentIndex(pos);
    } else {
        delete newFile;
    }
}

void MainWindow::on_action_Save_triggered() {
    if (ui->tabWidget->count())
        qobject_cast<Editor *>(ui->tabWidget->currentWidget())->saveFile();
}

void MainWindow::on_action_Find_triggered() {
    window_Find_Replace *check = new window_Find_Replace(this);
    check->show();
}

void MainWindow::windowFind(const QString& text, bool isRegex, QTextDocument::FindFlags flags) {
    if (ui->tabWidget->count())
        qobject_cast<Editor*>(ui->tabWidget->currentWidget())->findFile(text, isRegex, flags);
}

void MainWindow::windowReplace(const QString& textFind, const QString& textReplace, bool isRegex, QTextDocument::FindFlags flags) {
    if (ui->tabWidget->count())
        qobject_cast<Editor*>(ui->tabWidget->currentWidget())->replaceFile(textFind, textReplace, isRegex, flags);
}

void MainWindow::on_actionOpen_File_triggered()
{

     QString string = QFileDialog::getOpenFileName(this, tr("Open file"), "/");
    if (string.count() != 0) {
        QFileInfo file(string);

        addFileEdit(file.baseName(), string);
    }
}
