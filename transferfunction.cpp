#include "transferfunction.h"
#include "Polynomial.h"
#include "errorstrings.h"

#include <QList>
#include <QStringBuilder>
#include <QVector>
#include <QDebug>

TransferFunction::TransferFunction()
{    
    initTS();
}

TransferFunction::TransferFunction(double scalar)
{
    initTS();
    setZerosPoly(QString("%0").arg(scalar));
}

TransferFunction::TransferFunction(TransferFunction *tf0 )
{
    initTS();
    setTF(tf0->getZeroVectorStr(),tf0->getPolesVectorStr());
}

TransferFunction::TransferFunction(const Polynomial &zeroP, const Polynomial &poleP)
{
    QString zeroStr = getPolynomialVectorStr(zeroP);
    QString poleStr = getPolynomialVectorStr(poleP);

    initTS();
    setTF(zeroStr,poleStr);
}

TransferFunction::TransferFunction(const QString &zeroStr, const QString &poleStr)
{
    initTS();
    setTF(zeroStr,poleStr);
}

TransferFunction::TransferFunction(const std::string &zeroStr, const std::string &poleStr)
{
    setZerosPoly(QString(zeroStr.c_str()));
    setPolesPoly(QString(poleStr.c_str()));
}

void TransferFunction::initTS()
{
    m_zerosPoly = std::make_shared<Polynomial>();
    m_polesPoly = std::make_shared<Polynomial>();
}

void TransferFunction::setTF(const QString &zeroStr, const QString &poleStr)
{
    setZerosPoly(zeroStr);
    setPolesPoly(poleStr);
}

TransferFunction operator *(const TransferFunction &tr0, const TransferFunction &tr1)
{

    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    auto tr1_p = tr1.polesPoly();
    auto tr1_z = tr1.zerosPoly();

    Polynomial res_z = (*tr0_z) * (*tr1_z) ;
    Polynomial res_p = (*tr0_p) * (*tr1_p) ;

    TransferFunction res(res_z,res_p);

    return res;

}

TransferFunction operator /(const TransferFunction &tr0, const TransferFunction &tr1)
{
    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    auto tr1_p = tr1.polesPoly();
    auto tr1_z = tr1.zerosPoly();

    Polynomial res_z = (*tr0_z) * (*tr1_p) ;
    Polynomial res_p = (*tr0_p) * (*tr1_z) ;

    TransferFunction res(res_z,res_p);

    return res;

}

TransferFunction operator -(const TransferFunction &tr0, const TransferFunction &tr1)
{
    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    auto tr1_p = tr1.polesPoly();
    auto tr1_z = tr1.zerosPoly();

    Polynomial res_z = ((*tr0_z) * (*tr1_p)) - ((*tr1_z)*(*tr0_p));
    Polynomial res_p = (*tr0_p) * (*tr1_p) ;

    TransferFunction res(res_z,res_p);

    return res;
}

TransferFunction operator +(const TransferFunction &tr0, const TransferFunction &tr1)
{
    auto tr0_p = tr0.polesPoly();
    auto tr0_z = tr0.zerosPoly();

    auto tr1_p = tr1.polesPoly();
    auto tr1_z = tr1.zerosPoly();

    Polynomial res_z = ((*tr0_z) * (*tr1_p)) + ((*tr1_z)*(*tr0_p));
    Polynomial res_p = (*tr0_p) * (*tr1_p) ;

    TransferFunction res(res_z,res_p);

    return res;
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
    //dumpValue(QString("In function setZeroPoly BEFORE edit"),p);
    QString res = setPolynomialFomStr(polyStr,p,errString);   
    //qDebug()<<" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    //dumpValue(QString("In function setZeroPoly AFTER edit"),p);
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
    //dumpValue(QString("In function setPolesPoly BEFORE edit"),p);
    QString res = setPolynomialFomStr(polyStr,p,errString);
    //qDebug()<<" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n";
    //dumpValue(QString("In function setPolesPoly AFTER edit"),p);
    m_polesPoly = p;
    return res;
}

QString TransferFunction::getPolesVectorStr()
{
    auto p = m_polesPoly;
    QString pStr;
    pStr = getPolynomialVectorStr(p);
    return pStr;
}

QString TransferFunction::getZeroVectorStr()
{
    auto p = m_zerosPoly;
    QString pStr;
    pStr = getPolynomialVectorStr(p);
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
    if (!pass && errString != nullptr) {
        return (*errString);
    }

    //qDebug() << "coefficients qlist " <<coeff_double_list;

    std::vector<double> coeff_double_vector = coeff_double_list.toVector().toStdVector();

    //qDebug() << "coefficients std vector size" << coeff_double_vector.size();

    //dumpValue(QString("In function setPolyFromStr Before assignment of p"),p);

    p = std::make_shared<Polynomial>();

    p->SetCoefficients(coeff_double_vector.data(),coeff_double_vector.size() - 1 );

    //dumpValue(QString("In function setPolyFromStr AFTER assignment of p"),p);

    return getPolynomialVectorStr(p);
}

//QString TransferFunction::getPolynomialStr(const std::shared_ptr<Polynomial> p)
//{
//    QString polyStr = "";
//    getPolynomialStr(polyStr, p);
//    return polyStr;
//}


//QString TransferFunction::getPolynomialStr(QString &polyStr, const std::shared_ptr<Polynomial> p)
//{
//    polyStr = "";
//    for(int i = 0 ; i <= p->Degree(); i++){
//       double coeff = (*p)[i];
//       polyStr += QString::number(coeff) + " ";
//    }

//    return polyStr;
//}

QString TransferFunction::getPolynomialEquation(const std::shared_ptr<Polynomial> &p, const QString &plane)
{
    QString polyStr = "(";
    QStringList terms;

    if (p->Degree() == 0) return QString("%0").arg((*p)[0]);
    for(int i = p->Degree() ; i >= 0 ; i--){
       double c = (*p)[i];
       QString term;

       if (c == 0) {
           term = "0";
       }else{
        //c not equal to zero
           if (c == 1 ){
               //c equals 1 and i > 1  s^2, s^3, s^4
               if (i > 1){
                    term = QString("%0^%1").arg(plane).arg(i);
               }
               if (i == 1){
                   term = QString("%0").arg(plane);
               }
               if (i == 0){
                   term = QString("%0").arg("1");
               }
           }else{
               if (i > 1){
                    term = QString("%0*%1^%2").arg(c).arg(plane).arg(i);
               }
               if (i == 1){
                   term = QString("%0*%1").arg(c).arg(plane);
               }
               if (i == 0){
                   term = QString("%0").arg(c);
               }
           }
       }

       if (c > 0 && i != p->Degree()){
           term = QString("+%0").arg(term);
       }

       polyStr += term;
    }

    polyStr += ") ";

    return polyStr;
}

QString TransferFunction::getPolynomialVectorStr(const std::shared_ptr<Polynomial> &p)
{
    return getPolynomialVectorStr(*p);
}

QString TransferFunction::getPolynomialVectorStr(const Polynomial &p)
{
    //return string with coeficients in ascending order
    QString polystr="";
    if (p.Degree() == -1) return "";
    if (p.Degree() == 0) return QString("%0").arg(p[0]);
    for (int i = 0 ; i <= p.Degree(); i++){
        double c = p[i];
        QString term = QString("%0").arg(c);

        polystr += term + " ";
    }
    return polystr;
}

QString TransferFunction::getTfEquation(const QString &plane)
{
    //Return string in this form
    //"`W(s) = (a1 * s ^3 + a2 * s ^ 2 + a3 * s + a4)/(b1 * s ^3 + b2 * s ^ 2 + b3 * s + b4)`"
    QString zeroStr = getPolynomialEquation(m_zerosPoly,plane);
    QString poleStr = getPolynomialEquation(m_polesPoly,plane);

    //if (zeroStr == "") return
    QString tf_eq = QString("W(%0) = %1 / %2").arg(plane)
                                              .arg(zeroStr)
                                              .arg(poleStr);
    return tf_eq;
}

QList<std::shared_ptr<Root> > TransferFunction::getRootsClosedLoop()
{
    Polynomial D = *m_polesPoly;
    Polynomial N = *m_zerosPoly;

    Polynomial R = N + D;

    std::vector<double> real_ptr

    R.FindRoots();
}

bool TransferFunction::isEmpty()
{
    if (m_polesPoly->Degree() == -1 || m_zerosPoly->Degree() == -1){
        return true;
    }
    else return false;
}

void TransferFunction::dumpValue(QString msg, const std::shared_ptr<Polynomial> &p)
{    
    qDebug()<< "Polynomial string = " << getPolynomialVectorStr(p)<<"\n";
//    qDebug()<< "Polynomial Poles string = " << getPolynomialStr(p_str, m_polesPoly)<<"\n";
    qDebug()<< "Polynomial equation = "<< getPolynomialEquation(p,"s")<<"\n";
//    qDebug()<< "Polynomial Pole equation = "<< getPolynomialEquation(m_polesPoly)<<"\n";
    qDebug()<< "Transfer function equation = "<< getTfEquation()<<"\n";
}
