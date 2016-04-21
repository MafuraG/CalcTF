#include "controlsystem.h"
#include "outputdialog.h"
#include "ui_outputdialog.h"

OutputDialog::OutputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutputDialog)
{
    ui->setupUi(this);

    polyView = new QWebEngineView(this);

    webchannel = new QWebChannel(polyView->page());

    polyView->page()->setWebChannel(webchannel);

    jshelper = new JsHelper();

    webchannel->registerObject(QStringLiteral("jshelper"), jshelper);

    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(polyView);

    ui->groupBox_CS->setLayout(hbox);

    QString urlStr = QString("%0/%1").arg(qApp->applicationDirPath(),
                                          OutputDialog::PATH_POLY_HTML);

    //Better to use qApp->applicationDirPath coz it gives the location of executable

    polyView->setUrl(urlStr);

    plotDialog = new PlotDialog();


}

QString OutputDialog::PATH_POLY_HTML="screen1.html";

OutputDialog::~OutputDialog()
{
    delete ui;
    webchannel->deregisterObject(jshelper);
}

std::shared_ptr<ControlSystem> OutputDialog::cs() const
{
    return m_cs;
}

void OutputDialog::setCs(const std::shared_ptr<ControlSystem> &cs)
{
    m_cs = cs;    
    ui->tableView_roots->setModel(m_cs->getRootTModel());
    m_cs->simplifyCS();
    m_cs->updateRootTable();
    displayEquation(m_cs->getCsTF()->getTfEquation());
}

void OutputDialog::displayEquation(QString equation){
    //auto ts = m_cs->getCsTF();
    //QString eq = m_cs->getCsTF()->getTfEquation();
    //qDebug()<<"Equation to display at output: "<< eq ;
    //if (!this->isHidden())
    jshelper->displayEquation(equation);
}




void OutputDialog::on_pushButton_rootlocus_clicked()
{
    //display root locus plot of given transfer function
    plotDialog->show();
}
