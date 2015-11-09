#include "fileselector.h"

FileSelector::FileSelector(QWidget *parent) :
    QFileDialog(parent)
{
    QString filters = tr("Text file(*.txt);;All files(*.*)");
    setNameFilter(filters);
}

QDialog::DialogCode FileSelector::openDialog()
{
    setFileMode(QFileDialog::ExistingFile);
    setAcceptMode(QFileDialog::AcceptOpen);
    return static_cast<QDialog::DialogCode> (exec());
}

QDialog::DialogCode FileSelector::save()
{
    setFileMode(QFileDialog::AnyFile);
    setAcceptMode(QFileDialog::AcceptSave);
    setDefaultSuffix("txt");
    return static_cast<QDialog::DialogCode> (exec());
}

QString FileSelector::selectedFile()
{
    return selectedFiles().at(0);
}
