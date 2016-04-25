#ifndef ROOTLOCUSGRAPH_H
#define ROOTLOCUSGRAPH_H

#include "customgraph.h"
#include "rootlocus.h"
#include <memory>



class RootLocusGraph : public CustomGraph
{
public:
    RootLocusGraph(std::shared_ptr<TransferFunction> &tf);
    void plotGraph() override;
private:
    void plotRootLocus();
    std::shared_ptr<RootLocus> m_locus;
    QCPDataMap *getQCPDataMap(const QList<std::shared_ptr<Root> > &roots);
};

#endif // ROOTLOCUSGRAPH_H
