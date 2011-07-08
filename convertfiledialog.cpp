#include "convertfiledialog.h"
#include "ui_convertfiledialog.h"
#include "fileselector.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>

ConvertFileDialog::ConvertFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertFileDialog),
    opencc(new Converter),
    textreader(new TextReader)
{
    ui->setupUi(this);
}

ConvertFileDialog::~ConvertFileDialog()
{
    delete ui;
    delete opencc;
    delete textreader;
}

void ConvertFileDialog::convertSlot()
{
    QString input_file_name = ui->leInput->text();
    QFile input_file(input_file_name, this);
    if (!input_file.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this, tr("OpenCC"), tr("Input file not readable."));
        return;
    }
    input_file.close();

    QString contents = textreader->readAll(input_file_name);

    QString output_file_name = ui->leOutput->text();
    QFile output_file(output_file_name, this);
    if (!output_file.open(QFile::WriteOnly))
    {
        QMessageBox::critical(this, tr("OpenCC"), tr("Output file not writable."));
        return;
    }

    const char *config = ui->rbToChs->isChecked()? OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP
                                                 : OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD;
    opencc_t od = opencc->opencc_open(config);
    if (od == (opencc_t) -1)
    {
        opencc->opencc_perror("Opencc loading:");
        return; //TODO failed
    }

    QByteArray txt_in_utf8 = contents.toUtf8();
    const char * buffer_in = txt_in_utf8.data();

    char * buffer_out = opencc->opencc_convert_utf8(od, buffer_in, -1);
    if (buffer_out == (char *) -1)
    {
        opencc->opencc_perror("Opencc runtime:");
        opencc->opencc_close(od);
        return; //TODO failed
    }

    output_file.write(buffer_out);
    output_file.close();

    free(buffer_out);
    opencc->opencc_close(od);
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
