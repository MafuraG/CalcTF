#ifndef ROOTLOCUS_H
#define ROOTLOCUS_H

#include "intervaltf.h"
#include "transferfunction.h"

#include <memory>
class RootLocus
{
public:
    RootLocus();    

    QList<std::shared_ptr<Root> > poleR() const;

    QList<std::shared_ptr<Root> > zeroR() const;

    QList<std::shared_ptr<Root> > locus() const;

    double K() const;    

    QList<QList<std::shared_ptr<Root> > > locus1() const;
    void setLocus1(const QList<QList<std::shared_ptr<Root> > > &locus1);

    std::shared_ptr<IntervalTF> tf() const;
    void setTf(const std::shared_ptr<IntervalTF> &tf);

private:
    std::shared_ptr<IntervalTF> m_tf;
    QList<std::shared_ptr<Root>> m_poleR;
    QList<std::shared_ptr<Root>> m_zeroR;
    QList<std::shared_ptr<Root>> m_locus;
    QList<QList<std::shared_ptr<Root>>> m_locus1;

    void calculateLocus();

    double m_K;
    double calculateDelta(QList<std::shared_ptr<Root> > &rootList1, QList<std::shared_ptr<Root> > &rootList2);
};

#endif // ROOTLOCUS_H
