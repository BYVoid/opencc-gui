#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent) :
    QPlainTextEdit(parent),
    textreader(new TextReader)
{
}

TextEditor::~TextEditor()
{
    delete textreader;
}

void TextEditor::loadFile(QString filename)
{
    setPlainText(textreader->readAll(filename));
}
