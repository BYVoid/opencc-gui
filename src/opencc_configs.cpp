#include "opencc_configs.h"

OpenccConfig opencc_configs[] = {
    {QTranslator::tr("Simplified to Traditional"), "zhs2zht.ini"},
    {QTranslator::tr("Traditional to Simplified"), "zht2zhs.ini"},
    {QTranslator::tr("Simplified to Taiwan"), "zhs2zhtw_vp.ini"},
    {QTranslator::tr("Simplified to Taiwan (only variants)"), "zhs2zhtw_v.ini"},
    {QTranslator::tr("Simplified to Taiwan (only phrases)"), "zhs2zhtw_p.ini"},
    {QTranslator::tr("Traditional to Taiwan"), "zht2zhtw_vp.ini"},
    {QTranslator::tr("Traditional to Taiwan (only variants)"), "zht2zhtw_v.ini"},
    {QTranslator::tr("Traditional to Taiwan (only phrases)"), "zht2zhtw_p.ini"},
    {QTranslator::tr("Taiwan to Traditional"), "zhtw2zht.ini"},
    {QTranslator::tr("Taiwan to Simplified"), "zhtw2zhs.ini"},
    {QTranslator::tr("Taiwan to Mainland China (Simplified)"), "zhtw2zhcn_s.ini"},
    {QTranslator::tr("Taiwan to Mainland China (Traditional)"), "zhtw2zhcn_t.ini"},
    {QTranslator::tr("Mixed to Traditional"), "mix2zht.ini"},
    {QTranslator::tr("Mixed to Simplified"), "mix2zhs.ini"},
};
