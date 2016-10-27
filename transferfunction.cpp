
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
                    term = QString("%0%1^%2").arg(c).arg(plane).arg(i);
               }
               if (i == 1){
                   term = QString("%0%1").arg(c).arg(plane);
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

QList<std::shared_ptr<Root> > TransferFunction::getIntersectPoints(Polynomial &N,Polynomial &D)

{
    QList<std::shared_ptr<Root>> rList;

    Polynomial dN = N.Derivative();
    Polynomial dD = D.Derivative();

    Polynomial p = (N*dD) - (dN*D);

    rList = getRoots(p);

    return rList;
}

QList<std::shared_ptr<Root>> TransferFunction::getRootLocus(Polynomial &N,Polynomial &D,double & K_max,
                                                            QList<QList<std::shared_ptr<Root>>> &locus)
{
    auto poleRoots = getRootsClosedLoop(N,D,0);    
    double R = 0.01;
    int MAX_COUNT = 1000, count = 0;
    for (int i = 0; i < poleRoots.count(); i++){
        QList<std::shared_ptr<Root>> segment;
        auto c = poleRoots[i]->complexRoot();



        std::complex<double>  c_next;
        double K = 0;
        count = 0;
        do{
            K = getRootsInCircle(N,D,R,K,c,c_next);
            std::shared_ptr<Root> root = std::make_shared<Root>(c.real(),c.imag());
            segment.append(root);
            c = c_next;
            if (K != 0 && K > K_max ) K_max = K;
            count++;
            //qDebug()<<"K = "<<K;
        }while (K != 0 && count < MAX_COUNT);
        //qDebug()<<"K = "<<K;
        locus.append(segment);
    }
    QList<std::shared_ptr<Root>> result;
    for(int i = 0; i < locus.count(); i ++){
        for (int j = 0; j < locus[i].count(); j++){
            result.append(locus[i][j]);
        }
    }
    return result;
}

QList<std::shared_ptr<Root>> TransferFunction::getRootLocus1(Polynomial &N,Polynomial &D,double & K_max,
                                                            QList<QList<std::shared_ptr<Root>>> &locus)
{
    auto poleRoots = getRootsClosedLoop(N,D,0);
    auto intersectRoots = getIntersectPoints(N,D);
    QList<double> calculatedRoots;
    bool conjugateRoot = false;

    poleRoots.append(intersectRoots);

    for (int i = 0; i < poleRoots.count(); i++){
        auto c = poleRoots[i]->complexRoot();
        double K = 0;
        QList<std::shared_ptr<Root>> segment;
        qDebug()<<"Generating locus for pole starting at :"<< poleRoots[i]->real()<<" "<<poleRoots[i]->imaginary()<<"i";
        fillSegments(N,D,K_max,K,c,segment,locus,conjugateRoot);
    }


    QList<std::shared_ptr<Root>> result;
    for(int i = 0; i < locus.count(); i++){
        for (int j = 0; j < locus[i].count(); j++){
            result.append(locus[i][j]);
        }
    }
    return result;
}

void TransferFunction::fillSegments(Polynomial &N,Polynomial &D,double & K_max,double & K,
                                   std::complex<double> &center,QList<std::shared_ptr<Root>> &segment,
                                   QList<QList<std::shared_ptr<Root>>> &locus,bool conjugate)
{
    QList<double> Klist;
    QList<std::complex<double>> roots;
    int MAX_COUNT = 2000, count = 0;
    double R = 0.001;
    do{
        Klist = getRootsInCircle(N,D,R,K,center,roots);
        //qDebug()<<"Klist.count"<<Klist.count();
        if (Klist.count() == 1){
            //qDebug()<<"in first case";            
            K = Klist[0];
            //auto rlist = getRootsClosedLoop(N,D,K);
            //int idx = getClosestRoot(rlist,roots[0]);
            auto r_ = roots[0];
            //if (idx > -1 && idx < rlist.count())  r_ = rlist[idx]->complexRoot();
            qDebug()<<"1root :"<<r_.real()<<" "<<r_.imag()<<"i";
            std::shared_ptr<Root> newroot = std::make_shared<Root>(r_.real(),r_.imag());
            segment.append(newroot);
            center = r_;
            if (K != 0 && K > K_max ) K_max = K;
        }else{
            for (int i = 0; i< Klist.count(); i++){
                //qDebug()<<"in case 2";
                QList<std::shared_ptr<Root>> newsegment;
                center = roots[i];
                //qDebug()<<"root :"<<roots[i].real()<<" "<<roots[i].imag()<<"i";
                K = Klist[i];
                //auto rlist = getRootsClosedLoop(N,D,K);
                //int idx = getClosestRoot(rlist,roots[i]);
                auto r_ = roots[i];
                //if (idx > -1 && idx < rlist.count())  r_ = rlist[idx]->complexRoot();
                qDebug()<<"2root :"<<r_.real()<<" "<<r_.imag()<<"i"<<" count:"<<Klist.count()<<" K = "<<K;
                center = r_;
                fillSegments(N,D,K_max,K,center,newsegment,locus,false);
            }
        }
        count++;
        //qDebug()<<"K = "<<K<<" counter ="<<count; Klist.count()> 0 &&
    }while (K < 10 &&  count < MAX_COUNT);

    locus.append(segment);

    if (conjugate == true){
        QList<std::shared_ptr<Root>> segment1;
        for(int i = 0; i < segment.count(); i++){
            auto r_ = segment[i];
            std::shared_ptr<Root> newroot = std::make_shared<Root>(r_->real(),-1*r_->imaginary());
            segment1.append(newroot);
        }

        locus.append(segment1);
    }
}

double TransferFunction::getRootsInCircle(Polynomial &N, Polynomial &D,
                                            double radius,double K, std::complex<double> center,
                                            std::complex<double> &root)
{
    int MAX_POINTS = 1000;
    double rad = 0;
    double step = (2 * M_PI)/ MAX_POINTS;    
    int i = 0;
    for(;;){
        root = getPointOnCircle(radius,rad,center);
        auto k_c = calculateK(N,D,root);
        double K_new = 0;
        if (std::abs(k_c.imag()) < 0.001 && k_c.real() > 0 ) K_new = k_c.real();

        if (K_new > K) {
            //qDebug()<<"K_new =>"<< K_new;
            return K_new;
        }
        i++;
        rad = step* i;

        if (rad > 2 * M_PI) {
            return 0;
        }
    }

    return 0;
}

QList<double> TransferFunction::getRootsInCircle(Polynomial &N, Polynomial &D,
                                            double radius,double K, std::complex<double> center,
                                            QList<std::complex<double>> &roots)
{
    int MAX_POINTS = 500;
    double rad = 0;
    double step = (2 * M_PI)/ MAX_POINTS;
    int i = 0;
    QList<double>res_K;
    roots.clear();
    for(;;){
        auto root = getPointOnCircle(radius,rad,center);
        auto k_c = calculateK(N,D,root);
        double K_new = 0;
        if (std::abs(k_c.imag())  < 0.000001 && k_c.real() > 0 ) K_new = k_c.real();

        if (K_new > K) {
           //qDebug()<<"K_new =>"<< K_new;
            if (res_K.count() > 0){
                double prev_K = res_K[res_K.count() - 1];
                //eliminate 'identical' roots (roots closer than 0.001)
                if (std::abs(K_new - prev_K) > 0.0001){
                   res_K.append(K_new);
                   roots.append(root);
                }
//                res_K.append(K_new);
//                roots.append(root);
            }else{
                res_K.append(K_new);
                //qDebug()<<"Roots in circle: New k = "<<K_new;
                roots.append(root);
            }
        }
        i++;
        rad = step* i;

        if (rad > 2 * M_PI) {
            //qDebug()<<"break";
            //qDebug()<<"Number of roots in circle: "<<roots.count();
            break;
        }
    }

    return res_K;
}



int TransferFunction::getClosestRoot(QList<std::shared_ptr<Root>> &roots, std::complex<double> &root)
{
    int index = -1;
    double diff = 0, diff_prev = 0;
    for(int i = 0; i < roots.count(); i++){
        diff_prev = diff;
        auto r1 = roots[i]->complexRoot();
        auto r2 = root;
        diff = norm(r2 - r1);
        if (i == 0 && diff < 0.0001) index = i;
        if (i > 0 && diff < diff_prev) index = i;
    }

    return index;
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
