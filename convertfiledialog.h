#ifndef CONVERTFILEDIALOG_H
#define CONVERTFILEDIALOG_H

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
};

#endif // CONVERTFILEDIALOG_H
