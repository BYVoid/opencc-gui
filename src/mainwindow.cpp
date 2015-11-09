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
#include "converter.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QLocale>
#include <QMessageBox>
#include <QUrl>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    trans(new QTranslator)
{
    ui->setupUi(this);
    setDefaultLanguage();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete trans;
}

void MainWindow::convertSlot()
{
    if (!Converter::loaded())
    {
        QMessageBox::critical(this, tr("OpenCC"), tr("Failed to load opencc."));
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

    QString txt_in = ui->textEdit->toPlainText();
    QString txt_out = conv.convert(txt_in);
    ui->textEdit->setPlainText(txt_out);
}

void MainWindow::loadSlot()
{
    FileSelector fs(this);
    if (fs.openDialog() == QDialog::Accepted)
    {
        ui->textEdit->loadFile(fs.selectedFile());
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

    ui->cbConfig->clear();
    ui->cbConfig->addItem(tr("Simplified to Traditional"), "s2t.json");
    ui->cbConfig->addItem(tr("Traditional to Simplified"), "t2s.json");
    ui->cbConfig->addItem(tr("Simplified to Traditional (Taiwan Standard)"), "s2tw.json");
    ui->cbConfig->addItem(tr("Traditional (Taiwan Standard) to Simplified"), "tw2s.json");
    ui->cbConfig->addItem(tr("Simplified to Traditional (Hong Kong Standard)"), "s2hk.json");
    ui->cbConfig->addItem(tr("Traditional (Hong Kong Standard) to Simplified"), "hk2s.json");
    ui->cbConfig->addItem(tr("Simplified to Traditional (Taiwan Standard) with Taiwanese idiom"), "s2twp.json");
    ui->cbConfig->addItem(tr("Traditional (Taiwan Standard) to Simplified with Mainland idiom"), "tw2sp.json");
    ui->cbConfig->addItem(tr("Traditional (OpenCC Standard) to Taiwan Standard"), "t2tw.json");
    ui->cbConfig->addItem(tr("Traditional (OpenCC Standard) to Hong Kong Standard"), "t2hk.json");
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;
    QString filename = urls.first().toLocalFile();
    if (filename.isEmpty())
        return;
    ui->textEdit->loadFile(filename);
}
