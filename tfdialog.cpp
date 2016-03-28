#include "tfdialog.h"
#include "ui_tfdialog.h"

TfDialog::TfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TfDialog)
{
    ui->setupUi(this);
}

TfDialog::~TfDialog()
{
    delete ui;
}
