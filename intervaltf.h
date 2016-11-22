#ifndef INTERVALTF_H
#define INTERVALTF_H
#include "tfcoefficient.h"

#include <QString>
#include <QList>
#include "transferfunction.h"


class IntervalTF
{
public:
    IntervalTF();    
    void setN(const QString value);
    void setD(const QString value);
    QString getN();
    QString getD();

    QString getTfEquation(const QString &plane="s");
    QList<std::shared_ptr<Root>> getRootsClosedLoop(const double K = 1.0);
    QList<std::shared_ptr<Root> > getRootLocus();

private:
    void purseString(const QString value, QList<TfCoeff> &coeffList);    

    QList<TfCoeff> m_numerator;
    QList<TfCoeff> m_denomenator;

    QList<TransferFunction> m_tfList;
    void kharitonovP(const QList<TfCoeff> &c, std::vector<double> &v, const int n);
    void generateTF(const QList<TfCoeff> &N, const QList<TfCoeff> &D, QList<TransferFunction> &Tf);
    QString getStr(const QList<TfCoeff> &c);
    QString getCoeffEq(const QList<TfCoeff> &p, const QString &plane);
};

#endif // INTERVALTF_H
