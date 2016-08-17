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
    std::shared_ptr<ControlSystem> getCs() const;
    void setCs(const std::shared_ptr<ControlSystem> &cs);

    TfDialog *getTfdiag() const;
    void setTfdiag(TfDialog *value);

signals:
    //void displayEquation(QString equation);
    void on_mainwindow_closed(bool status);

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
    //OutputDialog *outdialog;
    std::shared_ptr<ControlSystem> m_cs;

};

#endif // MAINWINDOW_H
