/******************************************************************************

    bamcore.h

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
    void calPhi();
    void calN_Prod();
    void calSigma();
    void calNofT();

    double actFac(double hl, double tw, double tc);

    
};

#endif // BAMCORE_H
