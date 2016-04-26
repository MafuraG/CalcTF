#include "rootlocus.h"

RootLocus::RootLocus()
{

}

std::shared_ptr<TransferFunction> RootLocus::tf() const
{
    return m_tf;
}

void RootLocus::setTf(const std::shared_ptr<TransferFunction> &tf)
{
    m_tf = tf;
    //Get poleR and zeroR
    calculateLocus();
}

QList<std::shared_ptr<Root> > RootLocus::poleR() const
{
    return m_poleR;
}

QList<std::shared_ptr<Root> > RootLocus::zeroR() const
{
    return m_zeroR;
}

QList<std::shared_ptr<Root> > RootLocus::locus() const
{
    return m_locus;
}

double RootLocus::K() const
{
    return m_K;
}

void RootLocus::calculateLocus()
{
    double k = 0 ;
    double k_max = 50;
    int points = 10000;

    double step = k_max / points;

    m_locus.clear();
    for (int i = 0 ; i < points ; i++){
        k = i * step;
        QList<std::shared_ptr<Root>>roots = m_tf->getRootsClosedLoop(k);
        m_locus.append(roots);
    }

    m_poleR = m_tf->getRootsClosedLoop(0);
    m_zeroR = m_tf->getRootsClosedLoop(k_max);

}

