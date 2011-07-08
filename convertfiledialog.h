#ifndef CONVERTFILEDIALOG_H
#define CONVERTFILEDIALOG_H

#include "converter.h"

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
    Converter * opencc;

public slots:
    void convertSlot();
    void openSlot();
    void saveSlot();
};

#endif // CONVERTFILEDIALOG_H
