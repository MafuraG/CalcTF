#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlsystem.h"
#include "outputdialog.h"
#include "tfdialog.h"

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void displayEquation();

public slots:
    void on_tfdialog_closed(bool status);

private slots:


    void on_toolButton_controller_clicked();

    void on_toolButton_plant_clicked();

    void on_toolButton_feedback_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    TfDialog *tfdiag;
    OutputDialog *outdialog;
    std::shared_ptr<ControlSystem> m_cs;

};

#endif // MAINWINDOW_H
