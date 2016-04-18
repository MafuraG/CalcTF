#ifndef ROOT_H
#define ROOT_H

#include <QString>
#include <QVariant>
#include <QVector>



class Root
{
public:
    Root();
    static QString EntityName;
    static QString D_Real;
    static QString D_Imaginay;

    double real() const;
    void setReal(double real);

    double imaginary() const;
    void setImaginary(double imaginary);

    QVariant data(const int row) const;
    void setData(const int col, QVariant value);

    static QVariant header(int col);

private:
    static int ROOTSIZE = 2;
    QVector<double> m_rootVect = QVector<double>(ROOTSIZE);
};

#endif // ROOT_H
