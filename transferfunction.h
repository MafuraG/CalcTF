#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include "Polynomial.h"

#include <QString>
#include <memory>



class TransferFunction
{
public:
    TransferFunction();
    TransferFunction(const QString &zeroStr, const QString &poleStr);
    TransferFunction(const std::string &zeroStr, const std::string &poleStr);

    void setTF(const QString &zeroStr, const QString &poleStr);
    TransferFunction operator *(const TransferFunction &tr0);
    TransferFunction operator -(const TransferFunction &tr0);


private:
    std::shared_ptr<Polynomial> zerosPoly() const;
    void setZerosPoly(std::shared_ptr<Polynomial> &zerosPoly);

    std::shared_ptr<Polynomial> polesPoly() const;
    void setPolesPoly(std::shared_ptr<Polynomial> &polesPoly);

    void setZerosPoly(const QString &polyStr);
    void setPolesPoly(const QString &polyStr);
    QString getPolesStr();
    QString getZeroStr();

    std::shared_ptr<Polynomial> m_zerosPoly;
    std::shared_ptr<Polynomial> m_polesPoly;
    void setPolynomialFomStr(const QString &polyStr, std::shared_ptr<Polynomial> &p);
    void getPolynomialStr(QString &polyStr, const std::shared_ptr<Polynomial> &p);
};

#endif // TRANSFERFUNCTION_H
