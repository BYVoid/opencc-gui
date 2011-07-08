#ifndef CONVERTFILEDIALOG_H
#define CONVERTFILEDIALOG_H

#include "textreader.h"

#include <QDialog>

namespace Ui {
    class ConvertFileDialog;
}

class ConvertFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConvertFileDialog(QWidget *parent = 0);
    ~ConvertFileDialog();

private:
    Ui::ConvertFileDialog *ui;
    TextReader * textreader;


public slots:
    void convertSlot();
    void openSlot();
    void saveSlot();
};

#endif // CONVERTFILEDIALOG_H
