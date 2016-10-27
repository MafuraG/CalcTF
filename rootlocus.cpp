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
    calculateLocus1();
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

QList<QList<std::shared_ptr<Root> > > RootLocus::locus1() const
{
    return m_locus1;
}

void RootLocus::setLocus1(const QList<QList<std::shared_ptr<Root> > > &locus1)
{
    m_locus1 = locus1;
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



void RootLocus::calculateLocus1()
{
    m_locus.clear();
    Polynomial N = *m_tf->zerosPoly();
    Polynomial D = *m_tf->polesPoly();

    double K_max;


    //QList<QList<std::shared_ptr<Root>>> rlocus;
    m_locus = m_tf->getRootLocus1(N,D,K_max,m_locus1);

    m_poleR = m_tf->getRootsClosedLoop(0);
    m_zeroR = m_tf->getRootsClosedLoop(K_max);
}

void RootLocus::calculateLocus()
{
    double k = 0.00001 ;
    double k_max = 50;
    int points = 10000;
    int count = 0;

    double step = 0;
    QList<std::shared_ptr<Root>>roots_p = m_tf->getRootsClosedLoop(0);
    m_poleR = m_tf->getRootsClosedLoop(0);

    for(int i = 0; i< m_poleR.count();i++){
        m_tf->dumpKValues(m_poleR[i]->real(),m_poleR[i]->imaginary());
    }


    m_locus.clear();
    for (;;){
        k = k + step;
        //qDebug()<<"k = "<< k;
        QList<std::shared_ptr<Root>>roots = m_tf->getRootsClosedLoop(k);
        m_locus.append(roots);


        double delta = calculateDelta(roots,roots_p);
        //qDebug()<<"delta = "<< delta;
        step = 1/delta;
        if (step > 1000 || step < 0.001) {
           delta = 1000;
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

