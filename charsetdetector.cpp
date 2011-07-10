#include "charsetdetector.h"

#include <QLibrary>

bool CharsetDetector::initialized = false;
bool CharsetDetector::s_loaded = false;
uchardet_t (*CharsetDetector::uchardet_new)();
void (*CharsetDetector::uchardet_delete)(uchardet_t);
void (*CharsetDetector::uchardet_handle_data)(uchardet_t, const char *, size_t);
void (*CharsetDetector::uchardet_data_end)(uchardet_t);
void (*CharsetDetector::uchardet_reset)(uchardet_t);
const char * (*CharsetDetector::uchardet_get_charset)(uchardet_t);

void CharsetDetector::initialize()
{
    initialized = true;
    QLibrary loader;
    loader.setFileNameAndVersion("uchardet", "0.0.0");

    if (!loader.load())
        return;

    if (NULL == (uchardet_new = (uchardet_t (*)()) loader.resolve("uchardet_new")))
        return;
    if (NULL == (uchardet_delete = (void (*)(uchardet_t)) loader.resolve("uchardet_delete")))
        return;
    if (NULL == (uchardet_handle_data = (void (*)(uchardet_t, const char *, size_t)) loader.resolve("uchardet_handle_data")))
        return;
    if (NULL == (uchardet_data_end = (void (*)(uchardet_t)) loader.resolve("uchardet_data_end")))
        return;
    if (NULL == (uchardet_reset = (void (*)(uchardet_t)) loader.resolve("uchardet_reset")))
        return;
    if (NULL == (uchardet_get_charset = (const char * (*)(uchardet_t)) loader.resolve("uchardet_get_charset")))
        return;

    s_loaded = true;
}

CharsetDetector::CharsetDetector()
{
    if (!initialized)
        initialize();

    handle = NULL;

    if (!s_loaded)
        return;

    handle = uchardet_new();
}

CharsetDetector::~CharsetDetector()
{
    if (!s_loaded)
        return;

    uchardet_delete(handle);
}

QString CharsetDetector::detect(QByteArray &data)
{
    uchardet_reset(handle);
    uchardet_handle_data(handle, data.data(), data.length());
    uchardet_data_end(handle);
    return QString(uchardet_get_charset(handle));
}

bool CharsetDetector::loaded()
{
    if (!initialized)
        initialize();

    return s_loaded;
}

