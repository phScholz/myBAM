/******************************************************************************

    bamcore.cpp

    This file is part of myBAM!!!.

    myBAM!!! is free software: you can redistribute it and/or modify
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
#include "bamcore.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <math.h>
#include <QDebug>
#define DEBUG

bamCore::bamCore(QObject *parent) :
    QObject(parent)
{
    calMode="normal";
}

void bamCore::beginCal(){
//    if(calMode=="normal"){
//        qDebug() << "readCurrent()";
//        readCurrent();
//        emit setProgressBar(20);
//        //calN_Target();
//        emit setProgressBar(36);
//        qDebug() << "calPhi()";
//        calPhi();
//        emit setProgressBar(52);
//        qDebug() << "calN_Prod()";
//        calN_Prod();
//        emit setProgressBar(68);
//        qDebug() << "calSigma()";
//        calSigma();
//        emit setProgressBar(84);
//        qDebug() << "calNofT()";
//        //calNofT();
//        emit setProgressBar(100);

//        emit finished();
//    }

    if(calMode=="creator"){
        qDebug() << "Read Current ...";
        readCurrent();
        qDebug() << "Calculating Phi ...";
        calPhi();
        qDebug() << "Calculating produced nuclei ... ";
        calN_Prod();
        qDebug() << "Calculating crosssection ...";
        calSigma();
        emit finished();
    }
}

void bamCore::readCurrent(){
    emit setProgressBar(0);
#ifdef DEBUG
    qDebug() << "\nRead Current:";
#endif
    QStringList lines;
    QString text, line;

    QFile file(myInput.currentFile);

    if(file.exists()){
        if(file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);

            while(!in.atEnd()){
                /*Here the reading of the file starts line by line.
                  Every line will be append with a linebreak flag
                  before it is going to be added to a string, which
                  contains the whole file. Lines which contain "#"
                  will be ignored.*/
                line=in.readLine().append("\n");
                if(!line.contains("#")){
                    text.append(line);
                }
            }
            file.close();
            lines = text.split("\n");
            QVector<QStringList> values; //Array of QStringlists of size of the number of lines

            for(int i=0; i<lines.size()-1; i++){
                if(lines.at(i).size()>0){
                values.push_back(lines.at(i).split(QRegExp( "[ \\t]+"), QString::SkipEmptyParts));
                }
            }

            for(int i=0; i<values.size(); i++){
                emit setProgressBar(i/values.size());
                if(!i){
                    myInput.currentTime.push_back(values.at(i).at(0).toDouble());
                    myInput.currentCount.push_back(values.at(i).at(1).toDouble());
                    myInput.currentCountdiff.push_back(values.at(i).at(1).toDouble());
                }
                else{
                    myInput.currentTime.push_back(values.at(i).at(0).toDouble());
                    myInput.currentCountdiff.push_back(values.at(i).at(1).toDouble()-values.at(i-1).at(1).toDouble());
                    myInput.currentCount.push_back(values.at(i).at(1).toDouble());
                }
#ifdef DEBUG
                qDebug() << values.at(i).at(0).toDouble() << values.at(i).at(1).toDouble();
#endif

            }
        }
    }

    emit CurrentFinished();
}


void bamCore::calPhi(){
#ifdef DEBUG
    qDebug() << "\n t Phi(t)";
#endif

    for(int i=0; i<myInput.currentTime.size(); i++){

        //Error of Current is 1% according to 141Pr-paper of Anne Sauerwein - ONLY for PTB!!!

        if(i){
            myInput.phi.push_back((myInput.currentCount.at(i)-myInput.currentCount.at(i-1)) / (myInput.currentTime.at(i)-myInput.currentTime.at(i-1)));
            myInput.errorPhi.push_back(0.01*(myInput.currentCount.at(i)-myInput.currentCount.at(i-1)) / (myInput.currentTime.at(i)-myInput.currentTime.at(i-1)));
        }
        else{
            myInput.phi.push_back(myInput.currentCount.at(i) / myInput.currentTime.at(i));
            myInput.errorPhi.push_back(0.01*myInput.currentCount.at(i) / myInput.currentTime.at(i));
        }
#ifdef DEBUG
        qDebug() << myInput.currentTime.at(i) << myInput.phi.at(i) << myInput.errorPhi.at(i);
#endif
    }


    emit PhiFinished();
}

void bamCore::calN_Prod(){
    qDebug() << "calN_Prod()";

//    if(calMode=="normal"){
//        qDebug() << "normal Mode";
//        qDebug() << "\n Number of produced nuclei:";

//        for(int i=0; i<myInput.energy.size(); i++){

//            double dummy;
//            double errorDummy;

//            dummy=(myInput.peakCounts.at(i) * exp((log(2)/myInput.halfLife) * myInput.waitingTime))/(myInput.absoluteEfficiency.at(i) * myInput.gammaIntensity.at(i) * myInput.relativeDeadTime * (1-exp(-1.0 * (log(2)/myInput.halfLife) * myInput.countingTime)));
//            errorDummy=dummy*sqrt(pow(myInput.errorGammaIntensity.at(i)/myInput.gammaIntensity.at(i),2) + pow(myInput.errorAbsoluteEfficiency.at(i)/myInput.absoluteEfficiency.at(i),2)+pow(myInput.errorRelativeDeadTime/myInput.relativeDeadTime,2)
//                              +pow(log(2)*myInput.errorWaitingTime/myInput.halfLife,2)+pow(log(2)/myInput.halfLife*exp(-log(2)/myInput.halfLife*myInput.countingTime)/(1-exp(-log(2)/myInput.halfLife*myInput.countingTime))*myInput.errorCountingTime,2)
//                              +pow(log(2)/pow(myInput.halfLife,2)*(myInput.waitingTime + exp(-log(2)/myInput.halfLife*myInput.countingTime)/(1-exp(-log(2)/myInput.halfLife*myInput.countingTime))) * myInput.errorHalfLife,2));

//            qDebug() << dummy;

//            myInput.N_Prod.push_back(dummy);
//            myInput.errorN_Prod.push_back(errorDummy);
//        }

//        emit N_ProdFinished();
//    }

    if(calMode=="creator"){

#ifdef DEBUG
        qDebug() << "creator Mode";
        qDebug() << myInput.energy.size();
#endif

        for(int i=0; i<myInput.energy.size(); i++){

            double facA=0;
            qDebug() << "Activity factor...";
            for(int j=0; j<myInput.waitingT.size(); j++){
                qDebug() << myInput.waitingT.at(j);
                if(myInput.waitingT.at(j)){

                    facA+=actFac(myInput.halfLife, myInput.waitingT.at(j),myInput.countingT.at(j));
                }
                qDebug() << facA;
            }

            double counts=0;
            double errorCounts=0;

//            for(int j=0; j<myInput.peakCounts.size(); j++){

            counts+=myInput.peakCounts.at(i);
            errorCounts+=myInput.errorPeakCounts.at(i);
            qDebug() << counts;
            double relLife=0;
            int m=0;
            for(int k=0; k< myInput.relLifeT.size(); k++){
                if(myInput.relLifeT.at(k)){
                    m++;
                    relLife+=myInput.relLifeT.at(k);
                }
            }
            relLife/=m;
            qDebug() << relLife;
            counts/=relLife/100;
        //}

            double dummy;
            double errorDummy;
#ifdef DEBUG
            qDebug() << myInput.absoluteEfficiency.at(i);
            qDebug() << myInput.gammaIntensity.at(i);
#endif
            dummy=counts/(myInput.absoluteEfficiency.at(i)*myInput.gammaIntensity.at(i)*facA);
            errorDummy=dummy*sqrt(pow(errorCounts/counts,2)+pow(myInput.errorAbsoluteEfficiency.at(i)/myInput.absoluteEfficiency.at(i),2)+pow(myInput.errorGammaIntensity.at(i)/myInput.gammaIntensity.at(i),2));
#ifdef DEBUG
            qDebug() << dummy;
#endif

            myInput.N_Prod.push_back(dummy);
            myInput.errorN_Prod.push_back(errorDummy);
        }

        emit N_ProdFinished();

    }
}

double bamCore::actFac(double hl, double tw, double tc){
    double x;
    x=-exp(-log(2)*(tw+tc)/hl)+exp(-log(2)*(tw)/hl);
    if(x>0){ return x;}
    else{ return -x;}
}

void bamCore::calSigma(){    
    
    for(int i = 0 ; i< myInput.N_Prod.size(); i++){
        double X=0.0;
        double errorX=0;


        for(int j=0; j< myInput.phi.size(); j++){
            if(j){                
                X*=exp(-1.0 * (log(2.0)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)));
                errorX+=myInput.errorPhi.at(j)*(1 - exp(-1.0 * (log(2.0)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1))));
                X+=(myInput.phi.at(j) * (1 - exp(-1.0 * (log(2.0)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)))));
            }
            else{
                errorX+=myInput.errorPhi.at(j)* (1 - exp(-1.0 * (log(2.0)/myInput.halfLife) * myInput.currentTime.at(j)));
                X+= (myInput.phi.at(j) * (1 - exp(-1.0 * (log(2.0)/myInput.halfLife) * myInput.currentTime.at(j))));
            }
        }

        X*= myInput.targetThickness/ (log(2.0)/myInput.halfLife);
        errorX*=myInput.targetThickness/ (log(2.0)/myInput.halfLife);

#ifdef DEBUG
        qDebug() << "\nproduced nuclei:" << myInput.N_Prod.at(i);
#endif

        myInput.sigma.push_back(myInput.N_Prod.at(i)/X);
        myInput.errorSigma.push_back(myInput.N_Prod.at(i)/X *(myInput.errorN_Prod.at(i)/myInput.N_Prod.at(i)));
        myInput.errorSigma2.push_back(myInput.N_Prod.at(i)/X*(myInput.errorTargetThickness/myInput.targetThickness + myInput.errorHalfLife/myInput.halfLife+errorX/X));
#ifdef DEBUG
        qDebug() << "Cross Section:" << myInput.N_Prod.at(i)/X;
        qDebug()<< "Target thickness: " << myInput.targetThickness << myInput.errorTargetThickness;
        qDebug()<< "half life:: " << myInput.halfLife << myInput.errorHalfLife;
        qDebug()<< "X-value " << X << errorX;
#endif
    }

    emit SigmaFinished();
}

void bamCore::calNofT(){
//    QVector<double> dummy, dummy2;
//    double X=0;
//    for(int i = 0; i< myInput.N_Prod.size(); i++){
//        dummy2.push_back(0);
//        X=0;

//        for(int j=0; j<myInput.phi.size();j++){
//            if(!j){
//                X+=(myInput.phi.at(j) * (1 - exp(-1 * (log(2)/myInput.halfLife) * myInput.currentTime.at(j))) * myInput.targetThickness * myInput.sigma.at(i))/ (log(2)/myInput.halfLife);
//            }
//            else{
//                X*=exp(-1.0 * (log(2.0)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)));
//                X+= (myInput.phi.at(j) * (1 - exp(-1 * (log(2)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)))) * myInput.targetThickness * myInput.sigma.at(i))/ (log(2)/myInput.halfLife);
//            }

//            dummy.push_back(X);
//          }

//        myInput.NofT.push_back(dummy);
//        //myInput.diffNofT.push_back(dummy2);
//        dummy.clear();
//        dummy2.clear();


//        for(int k=0; k<myInput.currentTime.size(); k++){
//            myInput.TfromN.push_back(myInput.currentTime.at(k));
//        }
        
//    }
    

//    int stop=myInput.phi.size()-1;

//    for(int m = 0 ; m< myInput.N_Prod.size(); m++){
//        myInput.diffNofT.at(m).push_back(0);
//        for(int i=0; i< 2*(myInput.waitingTime+myInput.countingTime)/2000; i++){
//		double Nnew=myInput.NofT.at(m).at(stop+i)*exp(-1*(log(2)*2000/myInput.halfLife));
//                myInput.NofT.at(m).push_back(Nnew);
//                /*if(i){
//                    myInput.diffNofT.at(m).push_back(myInput.NofT.at(m).at(stop+i+1)-myInput.NofT.at(m).at(stop+i));
//                }*/

//                if(!m){
//                    myInput.TfromN.push_back(myInput.TfromN.at(stop+i)+2000);
//                }
//        }
//    }
}

double bamCore::activity(int days, double act, double halflife){
    double ac=0;
    ac=act*exp(-log(2)/halflife * (double) days/365.25);

#ifdef DEBUG
    qDebug() << "bamCore: value: " << -log(2)/halflife * (double) days/365.25;
    qDebug() << "bamCore: halflife: " << halflife << " years";
    qDebug() << "bamCore: New Activity: " << ac << " Bq";
#endif

    return ac;
}
