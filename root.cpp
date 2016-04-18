#include "root.h"

Root::Root()
{

}

double Root::real() const
{
    return m_rootVect[0];
}

void Root::setReal(double real)
{
    m_rootVect[0] = real;
}

double Root::imaginary() const
{
    return m_rootVect[1];
}

void Root::setImaginary(double imaginary)
{
    m_rootVect[1] = imaginary;
}

QVariant Root::data(const int row) const
{
    if (row >= 0 && row < ROOTSIZE)
    {
        return m_rootVect[row];
    }else
        return QVariant();
}

void Root::setData(const int col, QVariant value)
{
    if (row >= 0 && row < ROOTSIZE)
    {
        m_rootVect[row] = value.toDouble();
    }
}

QVariant Root::header(int col)
{
    if (col >= 0 && col < ROOTSIZE){
        switch(col){
            case(0):{
            return QVariant(Root::D_Real);
        }
        case(1):{
            return QVariant(Root::D_Imaginay);
        }
        default:{
            return QVariant();
        }
        }
    }

    return QVariant();
}

QString Root::D_Imaginay = "Мнимая часть";
QString Root::D_Real = "Действительная часть";
QString Root::EntityName = "Root";
