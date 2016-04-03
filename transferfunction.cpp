#include "transferfunction.h"
#include "Polynomial.h"
#include "errorstrings.h"

#include <QList>
#include <QStringBuilder>
#include <QVector>
#include <QDebug>

TransferFunction::TransferFunction()
{    
    m_zerosPoly = std::make_shared<Polynomial>();
    m_polesPoly = std::make_shared<Polynomial>();
}

TransferFunction::TransferFunction(TransferFunction &tf0)
{
    setTF(tf0.getZeroStr(),tf0.getPolesStr());
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

TransferFunction& TransferFunction::operator *(const TransferFunction &tr0)
{

    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    Polynomial res_z = (*tr0_z) * (*(this->m_zerosPoly)) ;
    Polynomial res_p = (*tr0_p) * (*(this->m_polesPoly)) ;

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);
    this->m_polesPoly = std::make_shared<Polynomial>(res_p);

    return (*this);

}

TransferFunction &TransferFunction::operator /(const TransferFunction &tr0)
{
    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    Polynomial res_z = (*tr0_z) * (*(this->m_polesPoly)) ;
    Polynomial res_p = (*tr0_p) * (*(this->m_zerosPoly));

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);
    this->m_polesPoly = std::make_shared<Polynomial>(res_p);

    return (*this);
}

TransferFunction& TransferFunction::operator -(const TransferFunction &tr0)
{
    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    Polynomial res_z = (*(this->m_zerosPoly)) - (*tr0_z);
    Polynomial res_p = (*(this->m_polesPoly)) - (*tr0_p);

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);
    this->m_polesPoly = std::make_shared<Polynomial>(res_p);

    return (*this);
}

TransferFunction& TransferFunction::operator +(const TransferFunction &tr0)
{
    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    Polynomial res_z = (*(this->m_zerosPoly)) + (*tr0_z);
    Polynomial res_p = (*(this->m_polesPoly)) + (*tr0_p);

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);
    this->m_polesPoly = std::make_shared<Polynomial>(res_p);

    return (*this);
}

TransferFunction &TransferFunction::operator *(const double scalar)
{
    Polynomial res_z = (*(this->m_zerosPoly)) * scalar;

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);

    return (*this);
}

TransferFunction &TransferFunction::operator /(const double scalar)
{
    Polynomial res_p = (*(this->m_polesPoly)) * scalar;

    this->m_polesPoly = std::make_shared<Polynomial>(res_p);

    return (*this);
}

TransferFunction &TransferFunction::operator + (const double scalar)
{

    Polynomial res_z = scalar * (*(this->m_polesPoly)) + (*(this->m_zerosPoly)) ;

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);

    return (*this);
}

TransferFunction &TransferFunction::operator -(const double scalar)
{
    Polynomial res_z = scalar * (*(this->m_polesPoly)) - (*(this->m_zerosPoly)) ;

    this->m_zerosPoly = std::make_shared<Polynomial>(res_z);

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

QString TransferFunction::setZerosPoly(const QString &polyStr,QString *errString)
{
    auto p = m_zerosPoly;    
    dumpValue(QString("In function setZeroPoly BEFORE edit"),p);
    QString res = setPolynomialFomStr(polyStr,p,errString);   
    qDebug()<<" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    dumpValue(QString("In function setZeroPoly AFTER edit"),p);
    m_zerosPoly = p ;
    return res;
}

std::shared_ptr<Polynomial> TransferFunction::polesPoly() const
{
    return m_polesPoly;
}

void TransferFunction::setPolesPoly(std::shared_ptr<Polynomial> &polesPoly)
{
    m_polesPoly = polesPoly;
}

QString TransferFunction::setPolesPoly(const QString &polyStr,QString *errString)
{
    auto p = m_polesPoly;
    dumpValue(QString("In function setPolesPoly BEFORE edit"),p);
    QString res = setPolynomialFomStr(polyStr,p,errString);
    qDebug()<<" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n";
    dumpValue(QString("In function setPolesPoly AFTER edit"),p);
    m_polesPoly = p;
    return res;
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

QString TransferFunction::setPolynomialFomStr(const QString &polyStr, std::shared_ptr<Polynomial> &p, QString *errString)
{
    QStringList coeff_str_list = polyStr.split(' ');
    QString coeff_str;
    QList<double> coeff_double_list;
    double coeff;
    bool ok,pass = true;
    foreach (coeff_str , coeff_str_list) {
        coeff = coeff_str.toDouble(&ok);
        if (ok){
            coeff_double_list.append(coeff);
        }
        else{
            if (errString != nullptr && coeff_str != ""){
                (*errString) += QString(ErrorStrings::NOT_A_NUMBER).arg(coeff_str) + " \n";
            }
            pass = false;
        }
    }
    if (!pass) return (*errString);

    qDebug() << "coefficients qlist " <<coeff_double_list;

    std::vector<double> coeff_double_vector = coeff_double_list.toVector().toStdVector();

    qDebug() << "coefficients std vector size" << coeff_double_vector.size();

    dumpValue(QString("In function setPolyFromStr Before assignment of p"),p);

    p = std::make_shared<Polynomial>();

    p->SetCoefficients(coeff_double_vector.data(),coeff_double_vector.size());

    dumpValue(QString("In function setPolyFromStr AFTER assignment of p"),p);    

    return getPolynomialStr(p);
}

QString TransferFunction::getPolynomialStr(const std::shared_ptr<Polynomial> p)
{
    QString polyStr = "";
    getPolynomialStr(polyStr, p);
    return polyStr;
}


QString TransferFunction::getPolynomialStr(QString &polyStr, const std::shared_ptr<Polynomial> p)
{
    polyStr = "";
    for(int i = 0 ; i <= p->Degree(); i++){
       double coeff = (*p)[i];
       polyStr += QString::number(coeff) + " ";
    }

    return polyStr;
}

QString TransferFunction::getPolynomialEquation(const std::shared_ptr<Polynomial> p)
{
    QString polyStr = "";
    QString power_line ;
    QString coeff_line ;
    if (p->Degree() == 0) return polyStr;
    for(int i = p->Degree() ; i >= 0 ; i--){
       double coeff = (*p)[i];
       power_line += QString("  %0    ").arg(i);
       coeff_line += QString("%0   +  ").arg(coeff);
    }

    polyStr = power_line + " \n" + coeff_line;

    return polyStr;
}

QString TransferFunction::getTfEquation()
{
    QString zeroStr = getPolynomialEquation(m_zerosPoly);
    QString poleStr = getPolynomialEquation(m_polesPoly);

    int size = zeroStr.size();

    if (size < poleStr.size()) size = poleStr.size();
    QString divider = "\n";
    for(int i = 0; i < size; i++){
        divider +="-";
    }
    divider += "\n";

    return zeroStr + divider + poleStr;


}

void TransferFunction::dumpValue(QString msg, const std::shared_ptr<Polynomial> &p)
{
    qDebug()<<msg<<"\n";
    QString p_str;
    qDebug()<< "Polynomial string = " << getPolynomialStr(p_str, p)<<"\n";
//    qDebug()<< "Polynomial Poles string = " << getPolynomialStr(p_str, m_polesPoly)<<"\n";
    qDebug()<< "Polynomial equation = "<< getPolynomialEquation(p)<<"\n";
//    qDebug()<< "Polynomial Pole equation = "<< getPolynomialEquation(m_polesPoly)<<"\n";
//    qDebug()<< "Transfer function equation = "<< getTfEquation()<<"\n";
}
