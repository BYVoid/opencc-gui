#include "converter.h"

#include <QLibrary>
#include <cstdlib>
#include <iostream>

bool Converter::initialized = false;
bool Converter::s_loaded = false;
opencc_t (*Converter::opencc_open)(const char *);
int (*Converter::opencc_close)(opencc_t);
char * (*Converter::opencc_convert_utf8)(opencc_t, const char *, size_t);
const char* (*Converter::opencc_error)(void);

void Converter::initialize()
{
    initialized = true;
    QLibrary libopencc;
    libopencc.setFileNameAndVersion("opencc", "1.0.0");

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

    opencc_error = (const char* (*)(void))libopencc.resolve("opencc_error");
    if (opencc_error == NULL)
        return;

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
    m_loaded = false;
    setConfig(config);
}

Converter::~Converter()
{
    if (!s_loaded)
        return;

    if (handle != NULL && handle != (opencc_t) -1)
        opencc_close(handle);
}

void Converter::perror(const char *s) {
	  std::cout << s << " " << opencc_error() << "\n";
}

void Converter::setConfig(const char *config)
{
    if (!s_loaded)
        return;

    if (handle != NULL)
        opencc_close(handle);

    handle = opencc_open(config);
    if (handle == (opencc_t) -1)
    {
        perror("Opencc loading:");
        return;
    }
    m_loaded = true;
}

bool Converter::config_loaded()
{
    return m_loaded;
}

QString Converter::convert(QString & text)
{
    QByteArray text_utf8 = text.toUtf8();
    const char * buffer_in = text_utf8.data();
    char * buffer_out = opencc_convert_utf8(handle, buffer_in, -1);
    if (buffer_out == (char *) -1)
    {
        perror("Opencc runtime:");
        opencc_close(handle);
        return ""; //TODO failed
    }
    QString retval = QString::fromUtf8(buffer_out);
    free(buffer_out);
    return retval;
}

