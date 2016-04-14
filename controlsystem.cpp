#include "controlsystem.h"

ControlSystem::ControlSystem()
{
    m_controllerTF = std::make_shared<TransferFunction>();
    m_feedbackTF = std::make_shared<TransferFunction>();
    m_plantTF = std::make_shared<TransferFunction>();
    updateCs();
}

void ControlSystem::setControlTF(const QString &zeroP, const QString &poleP)
{

    m_controllerTF = std::make_shared<TransferFunction>();
    m_controllerTF->setTF(zeroP,poleP);
    updateCs();
}


void ControlSystem::setFeedbackTF(const QString &zeroP, const QString &poleP)
{
    m_feedbackTF = std::make_shared<TransferFunction>();
    m_feedbackTF->setTF(zeroP,poleP);
    updateCs();
}



void ControlSystem::setPlantTF(const QString &zeroP, const QString &poleP)
{
    m_plantTF = std::make_shared<TransferFunction>();
    m_plantTF->setTF(zeroP,poleP);
    updateCs();
}

std::shared_ptr<TransferFunction> ControlSystem::getCsTF()
{
    return m_csTF;
}

void ControlSystem::updateCs()
{    
    setCsTF(m_controllerTF,m_feedbackTF,m_plantTF);
}



std::shared_ptr<TransferFunction> ControlSystem::getControlTF() const
{
    return m_controllerTF;
}

std::shared_ptr<TransferFunction> ControlSystem::getFeedbackTF() const
{
    return m_feedbackTF;
}

std::shared_ptr<TransferFunction> ControlSystem::getPlantTF() const
{
    return m_plantTF;
}

void ControlSystem::setCsTF(std::shared_ptr<TransferFunction> &cTF, std::shared_ptr<TransferFunction> &fbTF, std::shared_ptr<TransferFunction> &pTF)
{
    //csTF = cTF;cTF
    auto ctf = TransferFunction(cTF->getZeroVectorStr(),cTF->getPolesVectorStr());
    auto ftf = TransferFunction(fbTF->getZeroVectorStr(),fbTF->getPolesVectorStr());
    auto ptf = TransferFunction(pTF->getZeroVectorStr(),pTF->getPolesVectorStr());

    auto res = ((ctf * ptf * -1) / (ctf * ptf * ftf)) + 1 ;
    //auto res = TransferFunction(pTF->getZeroVectorStr(),pTF->getPolesVectorStr());

    m_csTF = std::make_shared<TransferFunction>();
    m_csTF->setTF(res.getZeroVectorStr(),res.getPolesVectorStr());
}


