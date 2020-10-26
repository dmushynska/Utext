#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
#include "Highlighter.h"
namespace Ui {
class Editor;
}

namespace Ui {
class MainWindow;
}

class Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    int setValue(const QString& newFullPath, Ui::MainWindow *mui);
    void saveFile(void);
    const QString& getFullPath(void);
    ~Editor();
    QTextEdit *getTextEdit();
    void findFile(const QString& text);
    void replaceFile(const QString& textFind, const QString& textReaplace);
private:
    Ui::Editor *ui;
    QString fullPath;
    Highlighter *mx_highlighter;
};
#endif // EDITOR_H
