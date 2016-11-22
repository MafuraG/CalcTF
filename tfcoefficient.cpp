#include "tfcoefficient.h"

TfCoeff::TfCoeff()
{
    setUpperV(0.0);
    setLowerV(0.0);
}

double TfCoeff::upperV() const
{
    return m_upperV;
}

void TfCoeff::setUpperV(double upperV)
{
    m_upperV = upperV;
}

double TfCoeff::lowerV() const
{
    return m_lowerV;
}

void TfCoeff::setLowerV(double lowerV)
{
    m_lowerV = lowerV;
}
