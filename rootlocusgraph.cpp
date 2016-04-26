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
    plot->clearGraphs();
    //draw locus
    QVector<double> x,y;
    getXYvectors(m_locus->locus(),x,y);
    QCPGraph *g = plot->addGraph();
    //QCPDataMap *data = getQCPDataMap(m_locus->locus());
    g->setData(x,y);
    g->setLineStyle(QCPGraph::lsNone);
    QCPScatterStyle locusStlye(QCPScatterStyle::ssCircle,Qt::black,2);
    g->setScatterStyle(locusStlye);
    //qDebug()<<"Number of locus poits to be plotted:"<<data->size();

    //Draw zeros   
    g = plot->addGraph();
    //data = getQCPDataMap(m_locus->zeroR());
    getXYvectors(m_locus->zeroR(),x,y);
    g->setData(x,y);
    g->setLineStyle(QCPGraph::lsNone);
    QCPScatterStyle zeroStlye(QCPScatterStyle::ssCircle,Qt::green,8);
    g->setScatterStyle(zeroStlye);

    //Draw poles
    g = plot->addGraph();
    //data = getQCPDataMap(m_locus->poleR());
    getXYvectors(m_locus->poleR(),x,y);
    g->setData(x,y);
    g->setLineStyle(QCPGraph::lsNone);
    QCPScatterStyle poleStlye(QCPScatterStyle::ssCross,Qt::red,8);
    g->setScatterStyle(poleStlye);

    setXAxisLabel("Real");
    setYAxisLabel("Imag");

    plot->rescaleAxes();
    plot->replot();    

}

void RootLocusGraph::getXYvectors(const QList<std::shared_ptr<Root>> &roots, QVector<double> &x, QVector<double> &y){
    int size = roots.size();
    x.resize(size);
    x.squeeze();
    y.resize(size);
    y.squeeze();

    for (int i = 0; i < size ; i++){
        Root *r = roots[i].get();
        x[i] = r->real();
        y[i] = r->imaginary();
    }
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
