#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include "Polynomial.h"

#include <QString>
#include <memory>



class TransferFunction
{
public:
    TransferFunction();
    TransferFunction(TransferFunction &tf0);
    TransferFunction(const QString &zeroStr, const QString &poleStr);
    TransferFunction(const std::string &zeroStr, const std::string &poleStr);

    void setTF(const QString &zeroStr, const QString &poleStr);
    TransferFunction& operator *(const TransferFunction &tr0);    
    TransferFunction& operator /(const TransferFunction &tr0);
    TransferFunction& operator -(const TransferFunction &tr0);
    TransferFunction& operator +(const TransferFunction &tr0);

    TransferFunction &operator *(const double scalar);
    TransferFunction& operator /(const double scalar);
    TransferFunction& operator -(const double scalar);
    TransferFunction& operator +(const double scalar);

    QString setZerosPoly(const QString &polyStr,QString *errString = nullptr);
    QString setPolesPoly(const QString &polyStr,QString *errString = nullptr);
    QString getPolesStr();
    QString getZeroStr();


private:
    std::shared_ptr<Polynomial> zerosPoly() const;
    void setZerosPoly(std::shared_ptr<Polynomial> &zerosPoly);

    std::shared_ptr<Polynomial> polesPoly() const;
    void setPolesPoly(std::shared_ptr<Polynomial> &polesPoly);    

    std::shared_ptr<Polynomial> m_zerosPoly;
    std::shared_ptr<Polynomial> m_polesPoly;
    QString setPolynomialFomStr(const QString &polyStr, std::shared_ptr<Polynomial> &p, QString *errString = nullptr);
    QString getPolynomialStr(QString &polyStr, const std::shared_ptr<Polynomial> &p);
    QString getPolynomialEquation(const std::shared_ptr<Polynomial> &p);
    QString getTfEquation();
};

#endif // TRANSFERFUNCTION_H
