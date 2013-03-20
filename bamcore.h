#ifndef BAMCORE_H
#define BAMCORE_H

#include <QObject>
#include "baminput.h"
#include "bamconst.h"

class bamCore : public QObject
{
    Q_OBJECT
public:
    explicit bamCore(QObject *parent = 0);
    bamInput myInput;
    bamConst myConst;
    
signals:
    void setProgressBar(int);
    void finished();
    void CurrentFinished();
    void N_TargetFinished();
    void PhiFinished();
    void N_ProdFinished();
    void SigmaFinished();

public slots:
    void beginCal();

private:
    void readCurrent();
    void calN_Target();
    void calPhi();
    void calN_Prod();
    void calSigma();
    void calNofT();

    
};

#endif // BAMCORE_H
