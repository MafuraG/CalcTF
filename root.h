#ifndef ROOT_H
#define ROOT_H

#include <QString>
#include <QVariant>
#include <QVector>
#include <complex>



class Root
{
public:
    Root();
    Root(const double real, const double imag);
    static QString EntityName;
    static QString D_Real;
    static QString D_Imaginay;

    double real() const;
    void setReal(double real);

    double imaginary() const;
    void setImaginary(double imaginary);

    QVariant data(const int row) const;
    bool setData(const int row, QVariant value);
    double magnitude();

    bool isEqualTo(Root &rhs);    

    static QVariant header(int col);

private:
    static int ROOTSIZE;
    QVector<double> m_rootVect = QVector<double>(ROOTSIZE);
};

inline bool operator==(const Root& lhs, const Root& rhs){
    /* do actual comparison */
    if (lhs.real() == rhs.real() && lhs.imaginary() == rhs.imaginary())
        return true;
    return false;
}

#endif // ROOT_H
