#ifndef ROOT_H
#define ROOT_H

#include <QString>
#include <QVariant>
#include <QVector>



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

    static QVariant header(int col);

private:
    static int ROOTSIZE;
    QVector<double> m_rootVect = QVector<double>(ROOTSIZE);
};

#endif // ROOT_H
