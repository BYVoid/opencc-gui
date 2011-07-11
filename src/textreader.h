#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <QString>
#include "charsetdetector.h"

class TextReader
{
public:
    TextReader();
    QString getCharset();
    QString readAll(QString filename);

private:
    QString charset;
    CharsetDetector cd;
};

#endif // TEXTREADER_H
