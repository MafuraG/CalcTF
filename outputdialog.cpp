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

    webchannel->registerObject(QStringLiteral("jshelper"), this);

    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(polyView);

    ui->groupBox_CS->setLayout(hbox);

    QString urlStr = QString("%0/%1").arg(qApp->applicationDirPath(),
                                          OutputDialog::PATH_POLY_HTML);

    //Better to use qApp->applicationDirPath coz it gives the location of executable

    polyView->setUrl(urlStr);

}

QString OutputDialog::PATH_POLY_HTML="screen.html";

OutputDialog::~OutputDialog()
{
    delete ui;
}

std::shared_ptr<ControlSystem> OutputDialog::cs() const
{
    return m_cs;
}

void OutputDialog::setCs(const std::shared_ptr<ControlSystem> &cs)
{
    m_cs = cs;
}