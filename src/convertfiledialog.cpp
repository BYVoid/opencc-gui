#include "convertfiledialog.h"
#include "ui_convertfiledialog.h"
#include "fileselector.h"
#include "converter.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>

ConvertFileDialog::ConvertFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertFileDialog),
    textreader(new TextReader)
{
    ui->setupUi(this);
    ui->cbConfig->addItem(tr("Simplified to Traditional"), "zhs2zht.ini");
    ui->cbConfig->addItem(tr("Traditional to Simplified"), "zht2zhs.ini");
    ui->cbConfig->addItem(tr("Simplified to Taiwan"), "zhs2zhtw_vp.ini");
    ui->cbConfig->addItem(tr("Simplified to Taiwan (only variants)"), "zhs2zhtw_v.ini");
    ui->cbConfig->addItem(tr("Simplified to Taiwan (only phrases)"), "zhs2zhtw_p.ini");
    ui->cbConfig->addItem(tr("Traditional to Taiwan"), "zht2zhtw_vp.ini");
    ui->cbConfig->addItem(tr("Traditional to Taiwan (only variants)"), "zht2zhtw_v.ini");
    ui->cbConfig->addItem(tr("Traditional to Taiwan (only phrases)"), "zht2zhtw_p.ini");
    ui->cbConfig->addItem(tr("Taiwan to Traditional"), "zhtw2zht.ini");
    ui->cbConfig->addItem(tr("Taiwan to Simplified"), "zhtw2zhs.ini");
    ui->cbConfig->addItem(tr("Taiwan to Mainland China (Simplified)"), "zhtw2zhcn_s.ini");
    ui->cbConfig->addItem(tr("Taiwan to Mainland China (Traditional)"), "zhtw2zhcn_t.ini");
}

ConvertFileDialog::~ConvertFileDialog()
{
    delete ui;
    delete textreader;
}

void ConvertFileDialog::convertSlot()
{
    if (!Converter::loaded())
    {
        QMessageBox::critical(this, tr("OpenCC"), tr("Failed to load opencc."));
        return;
    }

    QString input_file_name = ui->leInput->text();
    QFile input_file(input_file_name, this);
    if (!input_file.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this, tr("OpenCC"), tr("Input file not readable."));
        return;
    }
    input_file.close();

    QString output_file_name = ui->leOutput->text();
    QFile output_file(output_file_name, this);
    if (!output_file.open(QFile::WriteOnly))
    {
        QMessageBox::critical(this, tr("OpenCC"), tr("Output file not writable."));
        return;
    }

    QString config_file = ui->cbConfig->itemData(ui->cbConfig->currentIndex()).toString();
    QByteArray config_file_utf8 = config_file.toUtf8();

    Converter conv(config_file_utf8.data());
    if (!conv.config_loaded())
    {
        QMessageBox::critical(this, tr("OpenCC"), tr("Failed to load opencc configuration."));
        return;
    }

    QString txt_in = textreader->readAll(input_file_name);
    QString txt_out = conv.convert(txt_in);
    QByteArray txt_out_utf8 = txt_out.toUtf8();

    output_file.write(txt_out_utf8);
    output_file.close();

    QMessageBox::information(this, tr("OpenCC"), tr("Successfully converted."));
}

void ConvertFileDialog::openSlot()
{
    FileSelector fs(this);
    if (fs.open() == QDialog::Accepted)
    {
        QString file_name = fs.selectedFile();
        ui->leInput->setText(file_name);
    }
}

void ConvertFileDialog::saveSlot()
{
    FileSelector fs(this);
    if (fs.save() == QDialog::Accepted)
    {
        QString file_name = fs.selectedFile();
        ui->leOutput->setText(file_name);
    }
}
