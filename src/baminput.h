#ifndef BAMINPUT_H
#define BAMINPUT_H

#include <QObject>
#include <QVector>
#include <vector>

class bamInput : public QObject
{
    Q_OBJECT
public:
    explicit bamInput(QObject *parent = 0);

    //Target current
    QVector<double> currentTime;
    QVector<double> currentCount;
    QVector<double> currentCountdiff;
    QString currentFile;


    //Target material
    double targetThickness;
    double errorTargetThickness;
    double targetArea;
    double errorTargetArea;
    double molMass;
    double errorMolMass;
    double halfLife;
    double errorHalfLife;


    //analysis input - efficiency, counts, intensity, deadtime
    QVector<double> energy;

    QVector<double>  absoluteEfficiency;
    QVector<double>  errorAbsoluteEfficiency;

    QVector<double> peakCounts;
    QVector<double> errorPeakCounts;

    QVector<double> gammaIntensity;
    QVector<double> errorGammaIntensity;

    double relativeDeadTime;
    double errorRelativeDeadTime;

    double countingTime;
    double errorCountingTime;

    double waitingTime;
    double errorWaitingTime;

    QVector<double> waitingT;
    QVector<double> countingT;
    QVector<double> relLifeT;


    //calculation
    double N_Target;
    double errorN_Target;

    QVector<double> N_Prod;
    QVector<double> errorN_Prod;

    std::vector< QVector<double> > NofT;
    std::vector< QVector<double> > diffNofT;
    QVector<double> TfromN;

    QVector<double> sigma;
    QVector<double> errorSigma;
    QVector<double> errorSigma2;

    QVector<double> phi;
    QVector<double> errorPhi;
    
signals:
    
public slots:
    
};

#endif // BAMINPUT_H
