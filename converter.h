#ifndef CONVERTER_H
#define CONVERTER_H

#include "opencc.h"
#include <QString>

class Converter
{
public:
    Converter(const char * config = OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD);
    ~Converter();
    void setConfig(const char * config);
    QString convert(QString & text);

private:
    opencc_t handle;

    static bool initialized;
    static opencc_t (*opencc_open)(const char *);
    static int (*opencc_close)(opencc_t);
    static char * (*opencc_convert_utf8)(opencc_t, const char *, size_t);
    static opencc_error (*opencc_errno)(void);
    static void (*opencc_perror)(const char * spec);

    static void initialize();
};

#endif // CONVERTER_H
