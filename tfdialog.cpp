#include "tfdialog.h"
#include "ui_tfdialog.h"

TfDialog::TfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TfDialog)
{
    ui->setupUi(this);

    m_tf = std::make_shared<TransferFunction>();
}

TfDialog::~TfDialog()
{
    delete ui;
}

std::shared_ptr<TransferFunction> TfDialog::tf() const
{
    return m_tf;
}

void TfDialog::setTf(const std::shared_ptr<TransferFunction> &tf)
{
    m_tf = tf;
}

void TfDialog::on_buttonBox_accepted()
{
    emit tfDialogueClosed(true);
}

void TfDialog::on_buttonBox_rejected()
{
    emit tfDialogueClosed(false);
}


void TfDialog::on_lineEdit_zeroP_editingFinished()
{
    QString zerosStr = ui->lineEdit_zeroP->text();
    QString err = "";
    m_tf->setZerosPoly(zerosStr,&err);

    ui->label_error->setText(err);
}

void TfDialog::on_lineEdit_poleP_editingFinished()
{
    QString polesStr = ui->lineEdit_poleP->text();
    QString err = "";
    m_tf->setPolesPoly(polesStr,&err);

    ui->label_error->setText(err);
}
