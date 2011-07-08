#include "converter.h"

#include <QLibrary>
#include <QDir>
#include <QCoreApplication>

Converter::Converter()
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QLibrary libopencc("opencc");

    if (!libopencc.load())
        ; //TODO Library load failed

    opencc_open = (opencc_t (*)(const char *))libopencc.resolve("opencc_open");
    if (opencc_open == NULL)
        ; //TODO Resolve load failed

    opencc_close = (int (*)(opencc_t))libopencc.resolve("opencc_close");
    if (opencc_close == NULL)
        ; //TODO Resolve load failed

    opencc_convert_utf8 = (char * (*)(opencc_t, const char *, size_t))libopencc.resolve("opencc_convert_utf8");
    if (opencc_convert_utf8 == NULL)
        ; //TODO Resolve load failed

    opencc_errno = (opencc_error (*)(void))libopencc.resolve("opencc_errno");
    if (opencc_errno == NULL)
        ; //TODO Resolve load failed

    opencc_perror = (void (*)(const char *))libopencc.resolve("opencc_perror");
    if (opencc_perror == NULL)
        ; //TODO Resolve load failed
}
