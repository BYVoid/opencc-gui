#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "converter.h"
#include "charsetdetector.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QString s_loaded = tr("Loaded");
    QString s_failed_to_load = tr("Failed to load");

    if (Converter::loaded())
        ui->lOpencc->setText(s_loaded);
    else
        ui->lOpencc->setText(s_failed_to_load);

    if (CharsetDetector::loaded())
        ui->lUchardet->setText(s_loaded);
    else
        ui->lUchardet->setText(s_failed_to_load);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
