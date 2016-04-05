#include "tfdialog.h"
#include "ui_tfdialog.h"

TfDialog::TfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TfDialog)
{
    ui->setupUi(this);

    m_tf = std::make_shared<TransferFunction>();

    polyView = new QWebEngineView(this);

    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(polyView);

    ui->gB_poly_browser->setLayout(hbox);

    polyView->setUrl(QUrl("qrc:/html/screen.html"));

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
    clearUI();
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
    if (zerosStr == "" ) return ;
    QString err;
    QString res = m_tf->setZerosPoly(zerosStr,&err);
    m_tf->dumpValue(" Dump Zero in on_lineEdit_zeroP_editingFinished()",m_tf->zerosPoly());

//    if (err != "" ) ui->label_error->setText(err);
//    ui->label_error->setText(m_tf->getTfEquation());
}

void TfDialog::on_lineEdit_poleP_editingFinished()
{
    QString polesStr = ui->lineEdit_poleP->text();
    if (polesStr == "") return;
    QString err = "";
    QString res = m_tf->setPolesPoly(polesStr,&err);
    m_tf->dumpValue(" Dump Zero in on_lineEdit_poleP_editingFinished()",m_tf->zerosPoly());

//    if (err != "" ) ui->label_error->setText(err);
//    ui->label_error->setText(m_tf->getTfEquation());
}

void TfDialog::clearUI(){
    ui->lineEdit_poleP->setText("");
    ui->lineEdit_zeroP->setText("");
    //ui->label_error->setText("");
}
