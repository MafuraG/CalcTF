#include "tfdialog.h"
#include "ui_tfdialog.h"
#include <QDir>

TfDialog::TfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TfDialog)
{
    ui->setupUi(this);

    m_tf = std::make_shared<TransferFunction>();

//    polyView = new QWebEngineView(this);

//    webchannel = new QWebChannel(polyView->page());

//    polyView->page()->setWebChannel(webchannel);

//    jshelper = new JsHelper();

//    webchannel->registerObject(QStringLiteral("jshelper"), jshelper);

//    QHBoxLayout *hbox = new QHBoxLayout();

//    hbox->addWidget(polyView);

//    ui->gB_poly_browser->setLayout(hbox);

//    QString urlStr = QString("%0/%1").arg(qApp->applicationDirPath(),
//                                          TfDialog::PATH_POLY_HTML);

    //Better to use qApp->applicationDirPath coz it gives the location of executable

//    polyView->setUrl(urlStr);

    //qDebug()<<urlStr;

}

TfDialog::~TfDialog()
{
    //webchannel->deregisterObject(jshelper);
    delete ui;    
}

std::shared_ptr<TransferFunction> TfDialog::tf() const
{
    return m_tf;
}

void TfDialog::setTf(const std::shared_ptr<TransferFunction> &tf)
{
    m_tf = tf;
    m_tf_original = std::make_shared<TransferFunction>(tf.get());
    //m_tf_original->setTF(tf->getZeroVectorStr());
    ui->lineEdit_poleP->setText(m_tf->getPolesVectorStr());
    ui->lineEdit_zeroP->setText(m_tf->getZeroVectorStr());
    //jshelper->displayEquation(m_tf->getTfEquation());
}

void TfDialog::on_buttonBox_accepted()
{
    emit tfDialogueClosed(true);
}

void TfDialog::on_buttonBox_rejected()
{
    m_tf = m_tf_original;
    emit tfDialogueClosed(false);
}


void TfDialog::on_lineEdit_zeroP_editingFinished()
{
    QString zerosStr = ui->lineEdit_zeroP->text();
    zerosStr = zerosStr.simplified();
    if (zerosStr == "" ) return ;
    QString err;
    QString res = m_tf->setZerosPoly(zerosStr,&err);
    m_tf->dumpValue(" Dump Zero in on_lineEdit_zeroP_editingFinished()",m_tf->zerosPoly());
    //jshelper->displayEquation(m_tf->getTfEquation());

//    if (err != "" ) ui->label_error->setText(err);
//    ui->label_error->setText(m_tf->getTfEquation());
     ui->TF_textEdit->setText(m_tf->getTfEquation());
}

void TfDialog::on_lineEdit_poleP_editingFinished()
{
    QString polesStr = ui->lineEdit_poleP->text();
    polesStr = polesStr.simplified();
    if (polesStr == "") return;
    QString err = "";
    QString res = m_tf->setPolesPoly(polesStr,&err);
    m_tf->dumpValue(" Dump Zero in on_lineEdit_poleP_editingFinished()",m_tf->zerosPoly());
    //jshelper->displayEquation(m_tf->getTfEquation());

//    if (err != "" ) ui->label_error->setText(err);
//    ui->label_error->setText(m_tf->getTfEquation());
    ui->TF_textEdit->setText(m_tf->getTfEquation());
}

void TfDialog::clearUI(){
    ui->lineEdit_poleP->setText("");
    ui->lineEdit_zeroP->setText("");
    //ui->label_error->setText("");
}

QString TfDialog::PATH_POLY_HTML="screen.html";
