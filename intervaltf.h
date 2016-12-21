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
    QList<std::shared_ptr<Root>> getRootsClosedLoop(const bool max_K);
    QList<std::shared_ptr<Root> > getRootLocus();

    void generateTF();
private:
    void purseString(const QString value, QList<TfCoeff> &coeffList);    

    QList<TfCoeff> m_numerator;
    QList<TfCoeff> m_denomenator;

    QList<TransferFunction> m_tfList;
    void kharitonovP(const QList<TfCoeff> &c, std::vector<double> &v, const int n);
    void generateTF(const QList<TfCoeff> &N, const QList<TfCoeff> &D, QList<TransferFunction> &Tf);
    void generateTF1(const QList<TfCoeff> &N, const QList<TfCoeff> &D, QList<TransferFunction> &Tf);
    QString getStr(const QList<TfCoeff> &c);
    QString getCoeffEq(const QList<TfCoeff> &p, const QString &plane);
    double generateRandDouble(double min, double max, int nth_tf);
    void generateRandVector(const QList<TfCoeff> &c, std::vector<double> &v, int nth_tf);
    double generateRandDouble1(double min, double max, int nth_tf);
//    void reduce(QList<std::shared_ptr<Root> > &rlist, const QList<std::shared_ptr<Root> > &roots);
//    QList<std::shared_ptr<Root> > mapFunction(const TransferFunction &tf);
};

static QList<std::shared_ptr<Root> > mapFunction(const TransferFunction &tf){
//    TransferFunction _tf(tf.getZeroVectorStr(),tf.getPolesVectorStr());
//    _tf.setMaxK(tf.getMaxK());
    return tf.getRootsClosedLoop1();
}

static void reduceFunction(QList<std::shared_ptr<Root> > &rlist, const QList<std::shared_ptr<Root> > &roots){
    rlist.append(roots);
}

#endif // INTERVALTF_H
