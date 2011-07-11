#include "textreader.h"
#include <QFile>
#include <QTextStream>

TextReader::TextReader()
{
}

QString TextReader::getCharset()
{
    return charset;
}

QString TextReader::readAll(QString filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
        return ""; //TODO exception
    }

    QByteArray buffer = file.readAll();
    QTextStream stream(buffer);
    if (cd.loaded())
    {
        charset = cd.detect(buffer);
    }
    else
    {
        charset = "UTF-8";
    }
    QByteArray charset_name_utf8 = charset.toUtf8();

    stream.setCodec(charset_name_utf8.data());
    QString contents = stream.readAll();
    file.close();
    return contents;
}
