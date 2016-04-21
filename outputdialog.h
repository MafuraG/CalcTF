#ifndef OUTPUTDIALOG_H
#define OUTPUTDIALOG_H

#include "jshelper.h"
#include "plotdialog.h"

#include <QDialog>
#include <QWebChannel>
#include <QWebEngineView>
#include <controlsystem.h>
#include <memory>

namespace Ui {
class OutputDialog;
}

class OutputDialog : public QDialog
{
    Q_OBJECT

public:
    static QString PATH_POLY_HTML;
    explicit OutputDialog(QWidget *parent = 0);
    ~OutputDialog();

    std::shared_ptr<ControlSystem> cs() const;
    void setCs(const std::shared_ptr<ControlSystem> &cs);

public slots:
    void displayEquation(QString equation);

private slots:

    void on_pushButton_rootlocus_clicked();

private:
    Ui::OutputDialog *ui;
    QWebEngineView *polyView;
    QWebChannel *webchannel;
    std::shared_ptr<ControlSystem> m_cs;
    JsHelper *jshelper;
    PlotDialog *plotDialog;
};

#endif // OUTPUTDIALOG_H
