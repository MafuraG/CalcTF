
#define _USE_MATH_DEFINES

#include "transferfunction.h"
#include "Polynomial.h"
#include "errorstrings.h"
#include "root.h"

#include <QList>
#include <QStringBuilder>
#include <QVector>
#include <QDebug>
#include <complex>
#include <math.h>

TransferFunction::TransferFunction()
{    
    initTS();
}

TransferFunction::TransferFunction(double scalar)
{
    initTS();
    setZerosPoly(QString("%0").arg(scalar));
    setPolesPoly(QString("%0").arg(scalar));
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
    //simplifyTF();
}

QString TransferFunction::setZerosPoly(const QString &polyStr,QString *errString)
{
    auto p = m_zerosPoly;    
    //dumpValue(QString("In function setZeroPoly BEFORE edit"),p);
    QString res = setPolynomialFomStr(polyStr,p,errString);   
    //qDebug()<<" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    //dumpValue(QString("In function setZeroPoly AFTER edit"),p);
    m_zerosPoly = p ;
    //simplify polynomial
    //simplifyTF();
    return res;
}

std::shared_ptr<Polynomial> TransferFunction::polesPoly() const
{
    return m_polesPoly;
}

void TransferFunction::setPolesPoly(std::shared_ptr<Polynomial> &polesPoly)
{
    m_polesPoly = polesPoly;
    //simplifyTF();
}

QString TransferFunction::setPolesPoly(const QString &polyStr,QString *errString)
{
    auto p = m_polesPoly;
    //dumpValue(QString("In function setPolesPoly BEFORE edit"),p);
    QString res = setPolynomialFomStr(polyStr,p,errString);
    //qDebug()<<" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n";
    //dumpValue(QString("In function setPolesPoly AFTER edit"),p);
    m_polesPoly = p;
    //simplifyTF();
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
           continue;
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

void TransferFunction::simplifyTF()
{
    QVector<double> z_real_v;
    QVector<double> z_imag_v;

    QVector<double> p_real_v;
    QVector<double> p_imag_v;

    Polynomial p = *m_polesPoly;
    Polynomial z = *m_zerosPoly;

    if (p.Degree() == 0 || z.Degree() == 0) return; // no simplifcation needed

    if (p.Degree() < z.Degree()) return; //this is not a proper transfer function

    z_real_v.resize(z.Degree());
    z_imag_v.resize(z.Degree());
    p_real_v.resize(p.Degree());
    p_imag_v.resize(p.Degree());

    p.FindRoots(&p_real_v[0],&p_imag_v[0]);
    z.FindRoots(&z_real_v[0],&z_imag_v[0]);

    qDebug()<<"pole real roots"<<p_real_v;
    qDebug()<<"poles imag roots"<<p_imag_v;

    qDebug()<<"zero real roots"<<z_real_v;
    qDebug()<<"zero imag roots"<<z_imag_v;


    QList<Root> eliminated;
    int max_p = p.Degree();
    int max_z = z.Degree();

    for(int i = 0; i < max_p; i ++ ){
        Root p_r = Root(getRootAt(p_real_v,i),getRootAt(p_imag_v,i));
        for(int j = 0; j < max_z; j++){
            Root z_r = Root(getRootAt(z_real_v,j),getRootAt(z_imag_v,j));
            if (p_r == z_r){
                qDebug()<<"eliminated root = "<< p_r.real()<<", "<<p_r.imaginary();
                eliminated.append(p_r);
                break;
            }
        }
    }

    if (eliminated.count() == 0) return; //coz simplification is not needed

    Polynomial z_simple = Polynomial(1);
    Polynomial p_simple = Polynomial(1);

    for(int i = 0; i < max_p; i ++ ){
        Root p_r = Root(getRootAt(p_real_v,i),getRootAt(p_imag_v,i));
        qDebug()<< "poles roots in loop = > "<< p_r.real()<<", "<<p_r.imaginary();
        if (!eliminated.contains(p_r)){
            qDebug()<< "poles roots not emiminated = > "<< p_r.real()<<", "<<p_r.imaginary();
            if (p_r.imaginary() != 0){
                p_simple.IncludeComplexConjugateRootPair(p_r.real(),p_r.imaginary());
            }else{
                p_simple.IncludeRealRoot(p_r.real());
            }

        }
    }

    for(int i = 0; i < max_z; i ++ ){
        Root z_r = Root(getRootAt(z_real_v,i),getRootAt(z_imag_v,i));
        if (!eliminated.contains(z_r)){
            qDebug()<< "zeros roots not emiminated = > "<< z_r.real()<<", "<< z_r.imaginary();
            if (z_r.imaginary() != 0){
                z_simple.IncludeComplexConjugateRootPair(z_r.real(),z_r.imaginary());
            }else{
                z_simple.IncludeRealRoot(z_r.real());
            }
        }
    }

//    if (z_simple.Degree() == - 1) z_simple = Polynomial(1);
//    if (p_simple.Degree() == - 1) p_simple = Polynomial(1);

    m_zerosPoly = std::make_shared<Polynomial>(z_simple);
    m_polesPoly = std::make_shared<Polynomial>(p_simple);

}

double TransferFunction::getRootAt(QVector<double> &vect, int i)
{
    if (i < 0 || i >= vect.size()){
        return 0;
    }else
        return vect[i];
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

QList<std::shared_ptr<Root> > TransferFunction::getRootsClosedLoop(const double K)
{
    Polynomial *D = m_polesPoly.get();
    Polynomial *N = m_zerosPoly.get();
    QList<std::shared_ptr<Root>> rList;

    Polynomial R = (*D) + K*(*N);

    rList = getRoots(R);

    return rList;
}

QList<std::shared_ptr<Root> > TransferFunction::getRootsClosedLoop(Polynomial &N,Polynomial &D,
                                                                   const double K)
{
    QList<std::shared_ptr<Root>> rList;

    Polynomial R = D + K * N;

    rList = getRoots(R);

    return rList;
}

QList<std::shared_ptr<Root>> TransferFunction::getRootLocus(Polynomial &N,Polynomial &D,
                                                            bool positive_K,
                                                            double min_x,double min_y,
                                                            double max_x,double &max_y)
{
    QList<std::shared_ptr<Root>> rZeros = getRoots(N);
    QList<std::shared_ptr<Root>> rPoles = getRoots(D);

    Polynomial D1 = D.Derivative();
    Polynomial N1 = N.Derivative();

    Polynomial C = D1*N - D*N1;

    double delta = 0;
    double POINTS = 500;
    if (max_x > max_y) delta = max_x / POINTS ;
    else delta = max_y / POINTS;

    QList<std::shared_ptr<Root>> rCond = getRoots(C);

    removeRoots(rCond,rZeros);
    removeRoots(rCond,rPoles);

    QList<double> KList;

    KList.clear();

    for (int i = 0 ; i < rCond.count(); i++)
    {
        auto r = rCond[i]->complexRoot();
        std::complex<double> k = calculateK(N,D,r);
        if (k.imag() == 0 && k.real() > 0) {
            KList.removeAll(k.real());
            KList.append(k.real());
            qDebug()<<"K val = "<< k.real()<<".";
        }
    }

    double K_MIN = 0 , K_MAX = 2000;

    KList.append(K_MIN);
    KList.append(K_MAX);

    std::sort(KList.begin(),KList.end());
    QList<std::shared_ptr<Root>> result;
    QList<QList<std::shared_ptr<Root>>> segments;

    double K = 0;
    double step = 0;
    auto start = getRootsClosedLoop(N,D,K);

    for (int i = 0 ; i < start.count() ; i++){
        QList<std::shared_ptr<Root>> segment;
        segment.append(start[i]);
        segments.append(segment);
    }
    auto curr_roots = start;
    int count = 0;
    int MAX_POINTS = 10000;
    double radius = 1;
    while (true){
        QList<double> steps;
        for(int i = 0 ; i < curr_roots.count() ; i++)
        {
            double K_p = K;
            auto p = curr_roots[i]->complexRoot();
            auto s = getRootsInCircle(N,D,radius,K_p,p);
            if (s.real() != 0)
                steps.append(s.real());
            //qDebug()<<"step => "<<steps[steps.count()-1];
        }
        if (steps.count() != 0){
            std::sort(steps.begin(),steps.end());
            step = steps[0]; //Leap of faith, assuming imag = 0
        }else{
            step = K + 0.01;

        }


        //step = 0.01;
        K = step;
        qDebug()<<"step = "<< step<< "val K"<<K<<" count = "<<count;
        
        curr_roots = getRootsClosedLoop(N,D,K);
        
        result.append(curr_roots);

        if (count == MAX_POINTS) break;
        count++;
    }

    max_y = K;
    return result;
}

std::complex<double> TransferFunction::calculateStep(Polynomial &N,Polynomial &D,
                                       double delta, double K,
                                       std::complex<double> &p)
{
    
    return getRootsInCircle(N,D,K,delta,p);
}

std::complex<double> TransferFunction::getRootsInCircle(Polynomial &N, Polynomial &D,
                                                                double radius,double K, std::complex<double> center)
{
    int MAX_POINTS = 1000;
    double rad = 0;
    double step = (2 * M_PI)/ MAX_POINTS;
    std::complex<double> root;
    int i = 0;
    for(;;){
        root = getPointOnCircle(radius,rad,center);
        auto k_c = calculateK(N,D,root);
        double K_new;
        if (std::abs(k_c.imag()) < 0.00000001 || k_c.real() > 0 ) K_new = k_c.real();

        if (K_new > K) {
            //qDebug()<<"K_new =>"<< K_new;
            return std::complex<double>(K_new,0);
        }
        i++;
        rad = step* i;

        if (rad > 2 * M_PI) {
            root= std::complex<double>(0,0);
            break;
        }
    }

    return std::complex<double>(0.0001,0);
}

std::complex<double> TransferFunction::getPointOnCircle(double radius, double radians, std::complex<double> &center)
{
//    float x = (float)(radius * Math.Cos(angleInDegrees * Math.PI / 180F)) + origin.X;
//    float y = (float)(radius * Math.Sin(angleInDegrees * Math.PI / 180F)) + origin.Y;
    double x = radius * std::cos(radians) + center.real();
    double y = radius * std::sin(radians) + center.imag();

    return std::complex<double>(x,y);
}

unsigned int TransferFunction::getL(Polynomial &N,Polynomial &D, double K, std::complex<double> &p)
{
    Polynomial D_s = D + K*N;
    auto roots = getRoots(D_s);

    std::shared_ptr<Root> pr = std::make_shared<Root>(p.real(),p.imag());

    int res = roots.count(pr);
    //res = 1;
    return res;
}

std::complex<double> TransferFunction::evaluateComplex(const Polynomial &P, std::complex<double> p)
{
    double pr,pi;
    P.EvaluateComplex(p.real(),p.imag(),pr,pi);

    return std::complex<double>(pr,pi);
}

unsigned int TransferFunction::factorial(unsigned int n)
{
    unsigned int ret = 1;
    for (unsigned int i = 1; i <=n; i++)
        ret *=i;
    return ret;
}

std::complex<double> TransferFunction::calculateK(const Polynomial &N, const Polynomial &D,
                                                  const std::complex<double> &root)
{
    double dr,di,nr,ni;
    Polynomial D_neg = -1 * D ;
    D_neg.EvaluateComplex(root.real(),root.imag(),dr,di);
    N.EvaluateComplex(root.real(),root.imag(),nr,ni);

    std::complex<double> dc(dr,di);
    std::complex<double> nc(nr,ni);

    std::complex<double> res;

    res = dc / nc ;


    //qDebug() << "Value of K at point xr="<<root.real()<<" and xi="<<root.imag()<<" equals = "<<res.real()<<" "<<res.imag()<<"i.";

    return res;
}

void TransferFunction::removeRoots(QList<std::shared_ptr<Root>> &rootList ,
                                   const QList<std::shared_ptr<Root>> &removeList )
{
    for (int i = 0 ; i < removeList.count(); i++)
    {
        rootList.removeAll(removeList[i]);
    }
}

QList<std::shared_ptr<Root>> TransferFunction::getRoots(Polynomial &P){
    QList<std::shared_ptr<Root>> rList;

    QVector<double> real_vect;
    QVector<double>imag_vect;

    real_vect.resize(P.Degree());
    imag_vect.resize(P.Degree());

    int num_of_roots = 0;

    if (P.Degree() == 0) return rList;

    P.FindRoots(&real_vect[0],&imag_vect[0],&num_of_roots);

    for(int i = 0 ; i < num_of_roots; i++){
        auto r = std::make_shared<Root>(real_vect[i],imag_vect[i]);
        rList.append(r);
    }

    return rList;
}

std::complex<double>  TransferFunction::dumpKValues(double xr,double xi){
    Polynomial D = *m_polesPoly.get();
    Polynomial N = *m_zerosPoly.get();

    double dr,di,nr,ni;
    D = -1 * D ;
    D.EvaluateComplex(xr,xi,dr,di);
    N.EvaluateComplex(xr,xi,nr,ni);

    std::complex<double> dc(dr,di);
    std::complex<double> nc(nr,ni);

    std::complex<double> res;

    res = dc / nc ;


    qDebug() << "Value of K at point xr="<<xr<<" and xi="<<xi<<" equals = "<<res.real()<<" "<<res.imag()<<"i.";

    return res;
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
