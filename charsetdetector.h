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

    static bool loaded();

private:
    uchardet_t handle;

    static bool initialized;
    static bool s_loaded;
    static uchardet_t (*uchardet_new)();
    static void (*uchardet_delete)(uchardet_t);
    static int (*uchardet_handle_data)(uchardet_t, const char *, size_t);
    static void (*uchardet_data_end)(uchardet_t);
    static void (*uchardet_reset)(uchardet_t);
    static const char * (*uchardet_get_charset)(uchardet_t);

    static void initialize();
};

#endif // CHARSETDETECTOR_H
