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
    void renameFile(const QString& newFullPath);
    const QString& getFullPath(void);
    ~Editor();
    QTextEdit *getTextEdit();
    bool findFile(const QString& text, bool isRegex, QTextDocument::FindFlags flags);
    void replaceFile(const QString& textFind, const QString& textReaplace, bool isRegex, QTextDocument::FindFlags flags);
private:
    Ui::Editor *ui;
    QString mx_fullPath;
    Highlighter *mx_highlighter;
};
#endif // EDITOR_H
