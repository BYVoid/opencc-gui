#include "converter.h"

#include <QLibrary>
#include <cstdlib>

bool Converter::initialized = false;
bool Converter::s_loaded = false;
opencc_t (*Converter::opencc_open)(const char *);
int (*Converter::opencc_close)(opencc_t);
char * (*Converter::opencc_convert_utf8)(opencc_t, const char *, size_t);
opencc_error (*Converter::opencc_errno)(void);
void (*Converter::opencc_perror)(const char * spec);

void Converter::initialize()
{
    QLibrary libopencc("opencc");

    if (!libopencc.load())
        return;

    opencc_open = (opencc_t (*)(const char *))libopencc.resolve("opencc_open");
    if (opencc_open == NULL)
        return;

    opencc_close = (int (*)(opencc_t))libopencc.resolve("opencc_close");
    if (opencc_close == NULL)
        return;

    opencc_convert_utf8 = (char * (*)(opencc_t, const char *, size_t))libopencc.resolve("opencc_convert_utf8");
    if (opencc_convert_utf8 == NULL)
        return;

    opencc_errno = (opencc_error (*)(void))libopencc.resolve("opencc_errno");
    if (opencc_errno == NULL)
        return;

    opencc_perror = (void (*)(const char *))libopencc.resolve("opencc_perror");
    if (opencc_perror == NULL)
        return;

    initialized = true;
    s_loaded = true;
}

bool Converter::loaded()
{
    if (!initialized)
        initialize();

    return s_loaded;
}

Converter::Converter(const char * config)
{
    if (!initialized)
        initialize();

    handle = NULL;
    setConfig(config);
}

Converter::~Converter()
{
    if (handle != NULL)
        opencc_close(handle);
}

void Converter::setConfig(const char *config)
{
    if (handle != NULL)
        opencc_close(handle);

    handle = opencc_open(config);
    if (handle == (opencc_t) -1)
    {
        opencc_perror("Opencc loading:");
        return; //TODO failed
    }
}

QString Converter::convert(QString & text)
{
    QByteArray text_utf8 = text.toUtf8();
    const char * buffer_in = text_utf8.data();
    char * buffer_out = opencc_convert_utf8(handle, buffer_in, -1);
    if (buffer_out == (char *) -1)
    {
        opencc_perror("Opencc runtime:");
        opencc_close(handle);
        return ""; //TODO failed
    }
    QString retval = QString::fromUtf8(buffer_out);
    free(buffer_out);
    return retval;
}

