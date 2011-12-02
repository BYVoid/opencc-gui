#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "textreader.h"

#include <QPlainTextEdit>

class TextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = 0);
    ~TextEditor();
    void loadFile(QString filename);

private:
    TextReader * textreader;

signals:

public slots:

};

#endif // TEXTEDITOR_H
