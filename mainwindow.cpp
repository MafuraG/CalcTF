#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tfdiag = new TfDialog();
    outdialog = new  OutputDialog();
    m_cs = std::make_shared<ControlSystem>();

    //connect(btype,&BuildingType::run_calculations,this,&MainWindow::run_calculations);
    connect(tfdiag,&TfDialog::tfDialogueClosed,this,&MainWindow::on_tfdialog_closed);
    connect(this,&MainWindow::displayEquation,outdialog,&OutputDialog::displayEquation);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tfdiag;
    delete outdialog;
}

void MainWindow::on_tfdialog_closed(bool status)
{
    if (status){
        //update cs
        m_cs->updateCs();
        emit displayEquation();
    }
}


void MainWindow::on_toolButton_controller_clicked()
{
    tfdiag->setTf(m_cs->getControlTF());
    tfdiag->show();
}

void MainWindow::on_toolButton_plant_clicked()
{
    tfdiag->setTf(m_cs->getPlantTF());
    tfdiag->show();
}

void MainWindow::on_toolButton_feedback_clicked()
{
    tfdiag->setTf(m_cs->getFeedbackTF());
    tfdiag->show();
}

void MainWindow::on_pushButton_clicked()
{
    outdialog->setCs(m_cs);
    outdialog->show();
}
