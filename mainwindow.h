#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlsystem.h"
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

private slots:


    void on_toolButton_controller_clicked();

    void on_toolButton_plant_clicked();

    void on_toolButton_feedback_clicked();

private:
    Ui::MainWindow *ui;

    TfDialog *tfdiag;
    std::shared_ptr<ControlSystem> m_cs;

};

#endif // MAINWINDOW_H
