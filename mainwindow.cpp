#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tfdiag = nullptr;
    //outdialog = nullptr;
//    m_cs = std::make_shared<ControlSystem>();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tfdiag;
    //delete outdialog;
}

void MainWindow::on_tfdialog_closed(bool status)
{
    if (status){
        //update cs
        m_cs->updateCs();
        //qDebug()<<"Display Equation signal to be called";
        //emit displayEquation(m_cs->getCsTF()->getTfEquation());
    }
}


void MainWindow::on_toolButton_controller_clicked()
{
    if (tfdiag != nullptr){
        tfdiag->setTf(m_cs->getControlTF());
        tfdiag->setWindowTitle("Контроллер");
        tfdiag->show();
    }
}

void MainWindow::on_toolButton_plant_clicked()
{
    if (tfdiag != nullptr){
        tfdiag->setTf(m_cs->getPlantTF());
        tfdiag->setWindowTitle("Объект управления");
        tfdiag->show();
    }
}

void MainWindow::on_toolButton_feedback_clicked()
{
    if (tfdiag != nullptr){
        tfdiag->setTf(m_cs->getFeedbackTF());
        tfdiag->setWindowTitle("Датчик обратного связи");
        tfdiag->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
//    if (outdialog != nullptr){
//        outdialog->setCs(m_cs);
//        outdialog->setWindowTitle("Общая передаточная функция системы управления");
//        outdialog->show();
//    }
    m_cs->updateCs();
    on_mainwindow_closed(true);
    this->close();
}

TfDialog *MainWindow::getTfdiag() const
{
    return tfdiag;
}

void MainWindow::setTfdiag(TfDialog *value)
{
    tfdiag = value;
}

std::shared_ptr<ControlSystem> MainWindow::getCs() const
{
    return m_cs;
}

void MainWindow::setCs(const std::shared_ptr<ControlSystem> &cs)
{
    m_cs = cs;
}


