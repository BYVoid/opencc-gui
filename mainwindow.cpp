/*
* GUI for Open Chinese Convert
*
* Created on: Jul 6, 2011
* Author: BYVoid <byvoid.kcp@gmail.com>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "convertfiledialog.h"
#include "fileselector.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QLocale>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    opencc(new Converter),
    trans(new QTranslator),
    textreader(new TextReader)
{
    ui->setupUi(this);
    setDefaultLanguage();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete opencc;
    delete trans;
    delete textreader;
}

void MainWindow::convertSlot()
{
    const char *config = ui->rbToChs->isChecked()? OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP
                                                 : OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD;
    opencc_t od = opencc->opencc_open(config);
    if (od == (opencc_t) -1)
    {
        opencc->opencc_perror("Opencc loading:");
        return; //TODO failed
    }

    QString txt_in = ui->textEdit->toPlainText();
    QByteArray txt_in_utf8 = txt_in.toUtf8();
    const char * buffer_in = txt_in_utf8.data();

    char * buffer_out = opencc->opencc_convert_utf8(od, buffer_in, -1);
    if (buffer_out == (char *) -1)
    {
        opencc->opencc_perror("Opencc runtime:");
        opencc->opencc_close(od);
        return; //TODO failed
    }

    QString txt_out = QString::fromUtf8(buffer_out);
    ui->textEdit->setPlainText(txt_out);

    free(buffer_out);
    opencc->opencc_close(od);
}

void MainWindow::loadSlot()
{
    FileSelector fs(this);
    if (fs.open() == QDialog::Accepted)
    {
        ui->textEdit->setPlainText(textreader->readAll(fs.selectedFile()));
    }
}

void MainWindow::saveSlot()
{
    FileSelector fs(this);
    if (fs.save() == QDialog::Accepted)
    {
        QString file_name = fs.selectedFile();
        QFile file(file_name, this);
        if (file.open(QFile::WriteOnly))
        {
            QString contents = ui->textEdit->toPlainText();
            file.write(contents.toUtf8());
            file.close();
        }
    }
}

void MainWindow::convertFileSlot()
{
    ConvertFileDialog dialog;
    dialog.exec();
}

void MainWindow::aboutSlot()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::setDefaultLanguage()
{
    QLocale loc;
    if (loc.language() == QLocale::Chinese)
    {
        if (loc.country() == QLocale::China)
            language = ZHS;
        else
            language = ZHT;
    }
    else
    {
        language = ENG;
    }
    QApplication::instance()->installTranslator(trans);
    changeLanguage();
}

void MainWindow::changeLanguageToEngSlot()
{
    language = ENG;
    changeLanguage();
}

void MainWindow::changeLanguageToZhtSlot()
{
    language = ZHT;
    changeLanguage();
}

void MainWindow::changeLanguageToZhsSlot()
{
    language = ZHS;
    changeLanguage();
}

void MainWindow::changeLanguage()
{
    ui->actionEnglish->setChecked(false);
    ui->actionTraditional_Chinese->setChecked(false);
    ui->actionSimplified_Chinese->setChecked(false);

    switch (language)
    {
    case ZHT:
        trans->load("zht.qm");
        ui->actionTraditional_Chinese->setChecked(true);
        break;
    case ZHS:
        trans->load("zhs.qm");
        ui->actionSimplified_Chinese->setChecked(true);
        break;
    case ENG:
    default:
        trans->load("");
        ui->actionEnglish->setChecked(true);
    }
    ui->retranslateUi(this);
}
