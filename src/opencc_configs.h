#ifndef OPENCC_CONFIGS_H
#define OPENCC_CONFIGS_H

#include <QString>
#include <QTranslator>

struct OpenccConfig
{
    QString title;
    const char * filename;
};

#define OPENCC_CONFIGS_COUNT 14

extern OpenccConfig opencc_configs[];

#endif // OPENCC_CONFIGS_H
