#include "rootlocusgraph.h"

RootLocusGraph::RootLocusGraph(std::shared_ptr<TransferFunction> &tf)
{
    m_locus = std::make_shared<RootLocus>();
    m_locus->setTf(tf);
}

void RootLocusGraph::plotGraph()
{
    plotRootLocus();
}

void RootLocusGraph::plotRootLocus()
{
    QCustomPlot *plot = this->plot();

    if (plot == nullptr) return;

    //draw locus
    QCPGraph *g = plot->addGraph();
    QCPDataMap *data = getQCPDataMap(m_locus->locus());
    g->setData(data);

    //Draw zeros
    g = plot->addGraph();
    data = getQCPDataMap(m_locus->zeroR());
    g->setData(data);
    g->setLineStyle(QCPGraph::lsNone);
    QCPScatterStyle zeroStlye(QCPScatterStyle::ssCircle,Qt::green,8);
    g->setScatterStyle(zeroStlye);

    //Draw poles
    g = plot->addGraph();
    data = getQCPDataMap(m_locus->poleR());
    g->setData(data);
    g->setLineStyle(QCPGraph::lsNone);
    QCPScatterStyle poleStlye(QCPScatterStyle::ssCross,Qt::red,8);
    g->setScatterStyle(poleStlye);

    setXAxisLabel("Imag");
    setYAxisLabel("Real");

    plot->replot();

}

QCPDataMap *RootLocusGraph::getQCPDataMap(const QList<std::shared_ptr<Root>> &roots){
    QCPDataMap *map = new QCPDataMap();

    int size = roots.size();

    for (int i = 0; i < size ; i++){
        Root *r = roots[i].get();
        QCPData d = QCPData(r->real(),r->imaginary());
        map->insert(r->real(),d);
    }

    return map;
}
