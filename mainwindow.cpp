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

#include <QLibrary>
#include <QDir>
#include <QCoreApplication>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    loadOpencc();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadOpencc()
{
    QLibrary libopencc("opencc");
    if (!libopencc.load())
        ; //TODO Library load failed

    opencc_open = (opencc_t (*)(const char *))libopencc.resolve("opencc_open");
    if (opencc_open == NULL)
        ; //TODO Resolve load failed

    opencc_close = (int (*)(opencc_t))libopencc.resolve("opencc_close");
    if (opencc_close == NULL)
        ; //TODO Resolve load failed

    opencc_convert_utf8 = (char * (*)(opencc_t, const char *, size_t))libopencc.resolve("opencc_convert_utf8");
    if (opencc_convert_utf8 == NULL)
        ; //TODO Resolve load failed

    opencc_errno = (opencc_error (*)(void))libopencc.resolve("opencc_errno");
    if (opencc_errno == NULL)
        ; //TODO Resolve load failed

    opencc_perror = (void (*)(const char *))libopencc.resolve("opencc_perror");
    if (opencc_perror == NULL)
        ; //TODO Resolve load failed
}

void MainWindow::convertSlot()
{
    const char *config = ui->rbToChs->isChecked()? OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP
                                                 : OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD;
    opencc_t od = opencc_open(config);
    if (od == (opencc_t) -1)
    {
        opencc_perror("Opencc loading:");
        return; //TODO failed
    }

    QString txt_in = ui->textEdit->toPlainText();
    QByteArray txt_in_utf8 = txt_in.toUtf8();
    const char * buffer_in = txt_in_utf8.data();

    char * buffer_out = opencc_convert_utf8(od, buffer_in, -1);
    if (buffer_out == (char *) -1)
    {
        opencc_perror("Opencc runtime:");
        opencc_close(od);
        return; //TODO failed
    }

    QString txt_out = QString::fromUtf8(buffer_out);
    ui->textEdit->setPlainText(txt_out);

    free(buffer_out);
    opencc_close(od);
}

void MainWindow::loadSlot()
{
    QFileDialog * fd = new QFileDialog(this);
    QString filters = tr("Text file(*.txt);;All files(*.*)");
    fd->setNameFilter(filters);
    fd->setFileMode(QFileDialog::ExistingFile);
    fd->setAcceptMode(QFileDialog::AcceptOpen);
    if (fd->exec() == QDialog::Accepted)
    {
        QString file_name = fd->selectedFiles().at(0);
        QFile file(file_name, this);
        if (file.open(QFile::ReadOnly))
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            QString contents = stream.readAll();
            ui->textEdit->setPlainText(contents);
            file.close();
        }
    }
    delete fd;
}

void MainWindow::saveSlot()
{
    QFileDialog * fd = new QFileDialog(this);
    QString filters = tr("Text file(*.txt);;All files(*.*)");
    fd->setNameFilter(filters);
    fd->setFileMode(QFileDialog::AnyFile);
    fd->setAcceptMode(QFileDialog::AcceptSave);
    fd->setDefaultSuffix("txt");
    if (fd->exec() == QDialog::Accepted)
    {
        QString file_name = fd->selectedFiles().at(0);
        QFile file(file_name, this);
        if (file.open(QFile::WriteOnly))
        {
            QString contents = ui->textEdit->toPlainText();
            file.write(contents.toUtf8());
            file.close();
        }
    }
    delete fd;
}

void MainWindow::convertFileSlot()
{

}

void MainWindow::aboutSlot()
{
    AboutDialog dialog;
    dialog.exec();
}
