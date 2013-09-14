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
    QString calMode;
    
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
    double activity(int days, double activity, double halflife);

private:
    void readCurrent();
    void calN_Target();
    void calPhi();
    void calN_Prod();
    void calSigma();
    void calNofT();

    double actFac(double hl, double tw, double tc);

    
};

#endif // BAMCORE_H
