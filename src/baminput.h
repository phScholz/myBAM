/******************************************************************************

    baminput.h

    This file is part of myBAM!!!.

    myBAM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    myBAM!!! is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with myBAM!!!.  If not, see <http://www.gnu.org/licenses/>.

    Diese Datei ist Teil von myBAM!!!.

    myBAM!!! ist Freie Software: Sie können es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
    veröffentlichten Version, weiterverbreiten und/oder modifizieren.

    myBAM!!! wird in der Hoffnung, dass es nützlich sein wird, aber
    OHNE JEDE GEWÄHELEISTUNG, bereitgestellt; sogar ohne die implizite
    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License für weitere Details.

    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.

    (C)2013     Philipp Scholz
                pscholz@ikp.uni-koeln.de

********************************************************************************/
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
