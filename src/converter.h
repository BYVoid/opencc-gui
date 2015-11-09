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
    bool config_loaded();

    static bool loaded();

private:
    opencc_t handle;
    bool m_loaded;

    static bool initialized;
    static bool s_loaded;
    static opencc_t (*opencc_open)(const char *);
    static int (*opencc_close)(opencc_t);
    static char * (*opencc_convert_utf8)(opencc_t, const char *, size_t);
    static const char* (*opencc_error)(void);

    static void initialize();
    static void perror(const char* );
};

#endif // CONVERTER_H
