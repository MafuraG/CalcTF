#include "transferfunction.h"
#include "Polynomial.h"

#include <QList>
#include <QStringBuilder>
#include <QVector>

TransferFunction::TransferFunction()
{    

}

TransferFunction::TransferFunction(const QString &zeroStr, const QString &poleStr)
{
    setTF(zeroStr,poleStr);
}

TransferFunction::TransferFunction(const std::string &zeroStr, const std::string &poleStr)
{
    setZerosPoly(QString(zeroStr.c_str()));
    setPolesPoly(QString(poleStr.c_str()));
}

void TransferFunction::setTF(const QString &zeroStr, const QString &poleStr)
{
    setZerosPoly(zeroStr);
    setPolesPoly(poleStr);
}

TransferFunction TransferFunction::operator *(const TransferFunction &tr0)
{

    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    Polynomial res_z = (*tr0_z) * (*(this->m_zerosPoly)) ;
    Polynomial res_p = (*tr0_p) * (*(this->m_polesPoly)) ;

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);
    this->m_polesPoly = std::make_shared<Polynomial>(res_p);

    return (*this);

}

TransferFunction TransferFunction::operator -(const TransferFunction &tr0)
{
    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    Polynomial res_z = (*(this->m_zerosPoly)) - (*tr0_z);
    Polynomial res_p = (*(this->m_polesPoly)) - (*tr0_p);

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);
    this->m_polesPoly = std::make_shared<Polynomial>(res_p);

    return (*this);
}

std::shared_ptr<Polynomial> TransferFunction::zerosPoly() const
{
    return m_zerosPoly;
}

void TransferFunction::setZerosPoly(std::shared_ptr<Polynomial> &zerosPoly)
{
    m_zerosPoly = zerosPoly;
}

void TransferFunction::setZerosPoly(const QString &polyStr)
{
    auto p = m_zerosPoly;
    setPolynomialFomStr(polyStr,p);
}

std::shared_ptr<Polynomial> TransferFunction::polesPoly() const
{
    return m_polesPoly;
}

void TransferFunction::setPolesPoly(std::shared_ptr<Polynomial> &polesPoly)
{
    m_polesPoly = polesPoly;
}

void TransferFunction::setPolesPoly(const QString &polyStr)
{
    auto p = m_polesPoly;
    setPolynomialFomStr(polyStr,p);
}

QString TransferFunction::getPolesStr()
{
    auto p = m_polesPoly;
    QString pStr;
    getPolynomialStr(pStr,p);
    return pStr;
}

QString TransferFunction::getZeroStr()
{
    auto p = m_zerosPoly;
    QString pStr;
    getPolynomialStr(pStr,p);
    return pStr;
}

void TransferFunction::setPolynomialFomStr(const QString &polyStr, std::shared_ptr<Polynomial> &p)
{
    QStringList coeff_str_list = polyStr.split(' ');
    QString coeff_str;
    QList<double> coeff_double_list;
    double coeff;
    bool ok;
    foreach (coeff_str , coeff_str_list) {
        coeff = coeff_str.toDouble(&ok);
        if (ok){
            coeff_double_list.append(coeff);
        }
    }    

    std::vector<double> coeff_double_vector = coeff_double_list.toVector().toStdVector();

    p = std::make_shared<Polynomial>();

    p->SetCoefficients(coeff_double_vector.data(),coeff_double_vector.size());

}

void TransferFunction::getPolynomialStr(QString &polyStr, const std::shared_ptr<Polynomial> &p)
{
    polyStr = "";
    for(int i = 0 ; i < p->Degree(); i++){
       double coeff = (*p)[i];
       polyStr += QString::number(coeff);
    }
}
