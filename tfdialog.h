#ifndef TFDIALOG_H
#define TFDIALOG_H

#include <QDialog>

namespace Ui {
class TfDialog;
}

class TfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TfDialog(QWidget *parent = 0);
    ~TfDialog();

private:
    Ui::TfDialog *ui;
};

#endif // TFDIALOG_H
