#include "rootlocus.h"
#include <QDebug>

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

double RootLocus::calculateDelta(QList<std::shared_ptr<Root>> &rootList1 , QList<std::shared_ptr<Root>> &rootList2)
{
    if (rootList1.count() != rootList2.count()) return 0;

    double delta = 0 ;
    double delta_r = 0;
    for (int i = 0; i < rootList1.count(); i++)
    {
        std::shared_ptr<Root> r1 = rootList1[i];
        std::shared_ptr<Root> r2 = rootList2[i];

        delta_r = std::abs(r1->magnitude() - r2->magnitude());
        if (delta < delta_r)
            delta = delta_r ;
    }

    return delta;

}

void RootLocus::calculateLocus()
{
    double k = 0.0001 ;
    double k_max = 50;
    int points = 1000;
    int count = 0;

    double step = 0;
    QList<std::shared_ptr<Root>>roots_p = m_tf->getRootsClosedLoop(0);
    m_poleR = m_tf->getRootsClosedLoop(0);


    m_locus.clear();
    for (;;){
        k = k + step;
        //qDebug()<<"k = "<< k;
        QList<std::shared_ptr<Root>>roots = m_tf->getRootsClosedLoop(k);
        m_locus.append(roots);


        double delta = calculateDelta(roots,roots_p);
        qDebug()<<"delta = "<< delta;
        step = 1/delta;
        if (step > 1000) {
           delta = 100;
           //qDebug()<<"less delta = "<< delta;
        }
        step = 1/delta;


        roots_p = roots;
        count ++;

        if (count > points) break;
    }



    m_poleR = m_tf->getRootsClosedLoop(0);
    m_zeroR = m_tf->getRootsClosedLoop(k);

}

