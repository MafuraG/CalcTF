#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include "Polynomial.h"
#include "root.h"

#include <QList>
#include <QString>
#include <memory>



class TransferFunction
{
public:
    TransferFunction();
    TransferFunction(double scalar);
    TransferFunction(TransferFunction *tf0);
    TransferFunction(const Polynomial &zeroP, const Polynomial &poleP);
    TransferFunction(const QString &zeroStr, const QString &poleStr);
    TransferFunction(const std::string &zeroStr, const std::string &poleStr);

    void setTF(const QString &zeroStr, const QString &poleStr);    

    QString setZerosPoly(const QString &polyStr,QString *errString = nullptr);
    QString setPolesPoly(const QString &polyStr,QString *errString = nullptr);
//    QString getPolesStr();
//    QString getZeroStr();
    QString getPolesVectorStr();
    QString getZeroVectorStr();


    std::shared_ptr<Polynomial> zerosPoly() const;
    void setZerosPoly(std::shared_ptr<Polynomial> &zerosPoly);

    std::shared_ptr<Polynomial> polesPoly() const;
    void setPolesPoly(std::shared_ptr<Polynomial> &polesPoly);

    void dumpValue(QString msg, const std::shared_ptr<Polynomial> &p);

    QString getTfEquation(const QString &plane="s");
    QList<std::shared_ptr<Root>> getRootsClosedLoop();

    bool isEmpty();
private:


    std::shared_ptr<Polynomial> m_zerosPoly;
    std::shared_ptr<Polynomial> m_polesPoly;
    QString setPolynomialFomStr(const QString &polyStr, std::shared_ptr<Polynomial> &p, QString *errString = nullptr);
    QString getPolynomialStr(QString &polyStr, const std::shared_ptr<Polynomial> p);
//    QString getPolynomialStr(const std::shared_ptr<Polynomial> p);
    QString getPolynomialEquation(const std::shared_ptr<Polynomial> &p, const QString &plane);
    QString getPolynomialVectorStr(const std::shared_ptr<Polynomial> &p);
    QString getPolynomialVectorStr(const Polynomial &p);
    void initTS();
};

TransferFunction operator *(const TransferFunction &tr0, const TransferFunction &tr1);
TransferFunction operator /(const TransferFunction &tr0, const TransferFunction &tr1);
TransferFunction operator +(const TransferFunction &tr0, const TransferFunction &tr1);
TransferFunction operator -(const TransferFunction &tr0, const TransferFunction &tr1);


#endif // TRANSFERFUNCTION_H
