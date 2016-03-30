#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tfdiag = new TfDialog();
    m_cs = std::make_shared<ControlSystem>();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tfdiag;
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
