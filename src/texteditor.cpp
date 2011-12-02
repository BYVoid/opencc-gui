#include "texteditor.h"
#include <QUrl>
#include <QDebug>

TextEditor::TextEditor(QWidget *parent) :
    QPlainTextEdit(parent),
    textreader(new TextReader)
{
    setAcceptDrops(true);
}

TextEditor::~TextEditor()
{
    delete textreader;
}

void TextEditor::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        QList<QUrl> urls = event->mimeData()->urls();
        for (int i = 0; i < urls.size(); ++i)
        {
            qDebug() << urls[i].toLocalFile();
        }
        event->accept();
    }
}

void TextEditor::dropEvent(QDropEvent *event)
{
    qDebug() << event->mimeData();
    event->acceptProposedAction();
}

void TextEditor::loadFile(QString filename)
{
    setPlainText(textreader->readAll(filename));
}
