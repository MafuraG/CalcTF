#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include "transferfunction.h"



class ControlSystem
{
public:
    ControlSystem();

    void setControlTF(const QString &zeroP, const QString &poleP);
    void setFeedbackTF(const QString &zeroP, const QString &poleP);
    void setPlantTF(const QString &zeroP, const QString &poleP);



    TransferFunction *getCsTF() const;
    std::shared_ptr<TransferFunction> getControlTF() const;
    std::shared_ptr<TransferFunction> getFeedbackTF() const;
    std::shared_ptr<TransferFunction> getPlantTF() const;

private:

    std::shared_ptr<TransferFunction> controllerTF;
    std::shared_ptr<TransferFunction> feedbackTF;
    std::shared_ptr<TransferFunction> plantTF;
    std::shared_ptr<TransferFunction> csTF; //by system I mean a feed back control system with plant, feedback and control transfer functions

    void setCsTF(TransferFunction &cTF, const TransferFunction &fbTF, const TransferFunction &pTF);
};

#endif // CONTROLSYSTEM_H
