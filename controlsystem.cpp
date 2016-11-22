#include "controlsystem.h"

ControlSystem::ControlSystem()
{    
    m_rootTModel = new RootTableModel();    
}

RootTableModel *ControlSystem::getRootTModel() const
{
    return m_rootTModel;
}

void ControlSystem::updateRootTable()
{
    m_rootTModel->removeRows(0,m_rootTModel->rowCount());
    QList<std::shared_ptr<Root>> roots = m_csTF->getRootsClosedLoop(0);

    for (int i = 0; i < roots.count(); i++)
    {
        Root *r = roots[i].get();
        int last = m_rootTModel->rowCount();
        m_rootTModel->newRoot();
        Root * root = m_rootTModel->getRoot(last);

        root->setReal(r->real());
        root->setImaginary(r->imaginary());
    }
    //m_csTF->get
}

std::shared_ptr<IntervalTF> ControlSystem::getCsTF() const
{
    return m_csTF;
}

void ControlSystem::setCsTF(const std::shared_ptr<IntervalTF> &csTF)
{
    m_csTF = csTF;
}

