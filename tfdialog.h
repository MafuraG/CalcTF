#ifndef TFDIALOG_H
#define TFDIALOG_H

#include "transferfunction.h"

#include <QDialog>
#include <memory>

namespace Ui {
class TfDialog;
}

class TfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TfDialog(QWidget *parent = 0);
    ~TfDialog();

    std::shared_ptr<TransferFunction> tf() const;
    void setTf(const std::shared_ptr<TransferFunction> &tf);
signals:
    void tfDialogueClosed(bool);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_lineEdit_zeroP_editingFinished();

    void on_lineEdit_poleP_editingFinished();

private:
    Ui::TfDialog *ui;
    std::shared_ptr<TransferFunction> m_tf;
};

#endif // TFDIALOG_H
