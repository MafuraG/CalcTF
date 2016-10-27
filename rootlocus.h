#ifndef ROOTLOCUS_H
#define ROOTLOCUS_H

#include "transferfunction.h"

#include <memory>
class RootLocus
{
public:
    RootLocus();
    std::shared_ptr<TransferFunction> tf() const;
    void setTf(const std::shared_ptr<TransferFunction> &tf);



    QList<std::shared_ptr<Root> > poleR() const;

    QList<std::shared_ptr<Root> > zeroR() const;

    QList<std::shared_ptr<Root> > locus() const;

    double K() const;    

    QList<QList<std::shared_ptr<Root> > > locus1() const;
    void setLocus1(const QList<QList<std::shared_ptr<Root> > > &locus1);

private:
    std::shared_ptr<TransferFunction> m_tf;
    QList<std::shared_ptr<Root>> m_poleR;
    QList<std::shared_ptr<Root>> m_zeroR;
    QList<std::shared_ptr<Root>> m_locus;
    QList<QList<std::shared_ptr<Root>>> m_locus1;

    void calculateLocus();
    void calculateLocus1();

    double m_K;
    double calculateDelta(QList<std::shared_ptr<Root> > &rootList1, QList<std::shared_ptr<Root> > &rootList2);
};

#endif // ROOTLOCUS_H
