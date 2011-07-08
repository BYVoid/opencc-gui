#ifndef CHARSETDETECTOR_H
#define CHARSETDETECTOR_H

#include "uchardet.h"
#include <QString>

class CharsetDetector
{
public:
    CharsetDetector();
    ~CharsetDetector();
    QString detect(QByteArray & data);

private:
    uchardet_t handle;
    uchardet_t (*uchardet_new)();
    void (*uchardet_delete)(uchardet_t);
    void (*uchardet_handle_data)(uchardet_t, const char *, size_t);
    void (*uchardet_data_end)(uchardet_t);
    void (*uchardet_reset)(uchardet_t);
    const char * (*uchardet_get_charset)(uchardet_t);
};

#endif // CHARSETDETECTOR_H
