#include "charsetdetector.h"

#include <QLibrary>

CharsetDetector::CharsetDetector()
{
    QLibrary loader("uchardet");
    uchardet_new = (uchardet_t (*)()) loader.resolve("uchardet_new");
    uchardet_delete = (void (*)(uchardet_t)) loader.resolve("uchardet_delete");
    uchardet_handle_data = (void (*)(uchardet_t, const char *, size_t)) loader.resolve("uchardet_handle_data");
    uchardet_data_end = (void (*)(uchardet_t)) loader.resolve("uchardet_data_end");
    uchardet_reset = (void (*)(uchardet_t)) loader.resolve("uchardet_reset");
    uchardet_get_charset = (const char * (*)(uchardet_t)) loader.resolve("uchardet_get_charset");
    handle = uchardet_new();
}

CharsetDetector::~CharsetDetector()
{
    uchardet_delete(handle);
}

QString CharsetDetector::detect(QByteArray &data)
{
    uchardet_reset(handle);
    uchardet_handle_data(handle, data.data(), data.length());
    uchardet_data_end(handle);
    return QString(uchardet_get_charset(handle));
}
