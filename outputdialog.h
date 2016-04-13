#ifndef OUTPUTDIALOG_H
#define OUTPUTDIALOG_H

#include <QDialog>
#include <QWebChannel>
#include <QWebEngineView>

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

signals:
    void showEquation(QString);

private:
    Ui::OutputDialog *ui;
    QWebEngineView *polyView;
    QWebChannel *webchannel;
    std::shared_ptr<ControlSystem> m_cs;
};

#endif // OUTPUTDIALOG_H
