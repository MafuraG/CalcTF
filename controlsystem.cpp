#include "controlsystem.h"

ControlSystem::ControlSystem()
{
    m_controllerTF = std::make_shared<TransferFunction>();
    m_feedbackTF = std::make_shared<TransferFunction>();
    m_plantTF = std::make_shared<TransferFunction>();
}

void ControlSystem::setControlTF(const QString &zeroP, const QString &poleP)
{

    m_controllerTF = std::make_shared<TransferFunction>();
    m_controllerTF->setTF(zeroP,poleP);
}


void ControlSystem::setFeedbackTF(const QString &zeroP, const QString &poleP)
{
    m_feedbackTF = std::make_shared<TransferFunction>();
    m_feedbackTF->setTF(zeroP,poleP);
}



void ControlSystem::setPlantTF(const QString &zeroP, const QString &poleP)
{
    m_plantTF = std::make_shared<TransferFunction>();
    m_plantTF->setTF(zeroP,poleP);
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

void ControlSystem::setCsTF(TransferFunction &cTF, const TransferFunction &fbTF, const TransferFunction &pTF)
{
    //csTF = cTF;
    auto res = ((cTF * pTF * -1) / (cTF * pTF * fbTF)) + 1 ;

    m_csTF = std::make_shared<TransferFunction>(res);
}
