#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include "transferfunction.h"
#include <memory>
#include "roottablemodel.h"



class ControlSystem
{
public:
    ControlSystem();

    void setControlTF(const QString &zeroP, const QString &poleP);
    void setFeedbackTF(const QString &zeroP, const QString &poleP);
    void setPlantTF(const QString &zeroP, const QString &poleP);



    std::shared_ptr<TransferFunction> getCsTF();
    std::shared_ptr<TransferFunction> getControlTF() const;
    std::shared_ptr<TransferFunction> getFeedbackTF() const;
    std::shared_ptr<TransferFunction> getPlantTF() const;

    void updateCs();
    RootTableModel *getRootTModel() const;

    void updateRootTable();
    void simplifyCS();
    void setCsTF(const std::shared_ptr<TransferFunction> &csTF);

private:

    std::shared_ptr<TransferFunction> m_controllerTF;
    std::shared_ptr<TransferFunction> m_feedbackTF;
    std::shared_ptr<TransferFunction> m_plantTF;
    std::shared_ptr<TransferFunction> m_csTF; //by system I mean a feed back control system with plant, feedback and control transfer functions

    RootTableModel *m_rootTModel;
    void setCsTF(std::shared_ptr<TransferFunction> &cTF, std::shared_ptr<TransferFunction>  &fbTF, std::shared_ptr<TransferFunction> &pTF);
};

#endif // CONTROLSYSTEM_H
