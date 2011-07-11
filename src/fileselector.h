#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QFileDialog>

class FileSelector : private QFileDialog
{
    Q_OBJECT
public:
    explicit FileSelector(QWidget *parent = 0);
    DialogCode open();
    DialogCode save();
    QString selectedFile();

signals:

public slots:

};

#endif // FILESELECTOR_H
