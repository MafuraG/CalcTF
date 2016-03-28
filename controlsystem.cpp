#include "controlsystem.h"

ControlSystem::ControlSystem()
{

}

void ControlSystem::setControlTF(const QString &zeroP, const QString &poleP)
{

    controlTF = std::make_shared<TransferFunction>();
    controlTF->setTF(zeroP,poleP);
}


void ControlSystem::setFeedbackTF(const QString &zeroP, const QString &poleP)
{
    feedbackTF = std::make_shared<TransferFunction>();
    feedbackTF->setTF(zeroP,poleP);
}



void ControlSystem::setPlantTF(const QString &zeroP, const QString &poleP)
{
    plantTF = std::make_shared<TransferFunction>();
    plantTF->setTF(zeroP,poleP);
}



std::shared_ptr<TransferFunction> ControlSystem::getControlTF() const
{
    return controlTF;
}

std::shared_ptr<TransferFunction> ControlSystem::getFeedbackTF() const
{
    return feedbackTF;
}

std::shared_ptr<TransferFunction> ControlSystem::getPlantTF() const
{
    return plantTF;
}

void ControlSystem::setCsTF(TransferFunction &cTF, const TransferFunction &fbTF, const TransferFunction &pTF)
{
    //csTF = cTF;
}
