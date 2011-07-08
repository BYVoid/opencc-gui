#include "convertfiledialog.h"
#include "ui_convertfiledialog.h"

ConvertFileDialog::ConvertFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertFileDialog)
{
    ui->setupUi(this);
}

ConvertFileDialog::~ConvertFileDialog()
{
    delete ui;
}
