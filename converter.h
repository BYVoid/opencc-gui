#ifndef CONVERTER_H
#define CONVERTER_H

#include "opencc.h"

class Converter
{
public:
    Converter();
    opencc_t (*opencc_open)(const char *);
    int (*opencc_close)(opencc_t);
    char * (*opencc_convert_utf8)(opencc_t, const char *, size_t);
    opencc_error (*opencc_errno)(void);
    void (*opencc_perror)(const char * spec);

};

#endif // CONVERTER_H
