#include "bamcore.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <math.h>
#include <QDebug>

bamCore::bamCore(QObject *parent) :
    QObject(parent)
{

}

void bamCore::beginCal(){
    qDebug() << "readCurrent()";
    readCurrent();
    emit setProgressBar(20);
    //calN_Target();
    emit setProgressBar(36);
    qDebug() << "calPhi()";
    calPhi();
    emit setProgressBar(52);
    qDebug() << "calN_Prod()";
    calN_Prod();
    emit setProgressBar(68);
    qDebug() << "calSigma()";
    calSigma();
    emit setProgressBar(84);
    qDebug() << "calNofT()";
    //calNofT();
    emit setProgressBar(100);

    emit finished();
}

void bamCore::readCurrent(){
    emit setProgressBar(0);
    qDebug() << "\nRead Current:";
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

                qDebug() << values.at(i).at(0).toDouble() << values.at(i).at(1).toDouble();

            }
        }
    }

    emit CurrentFinished();
}

void bamCore::calN_Target(){
    qDebug() << "\nTarget Thickness:"<< myInput.targetThickness;

    qDebug() << "\nNumber of Target Nuclei:";
    myInput.N_Target=myInput.targetThickness * myInput.targetArea / myInput.molMass * myConst.avogadro;
    qDebug() << myInput.N_Target;
    emit N_TargetFinished();
}

void bamCore::calPhi(){

    qDebug() << "\n t Phi(t)";

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

        qDebug() << myInput.currentTime.at(i) << myInput.phi.at(i) << myInput.errorPhi.at(i);
    }


    emit PhiFinished();
}

void bamCore::calN_Prod(){

    qDebug() << "\n Number of produced nuclei:";

    for(int i=0; i<myInput.energy.size(); i++){

        double dummy;
        double errorDummy;

        dummy=(myInput.peakCounts.at(i) * exp((log(2)/myInput.halfLife) * myInput.waitingTime))/(myInput.absoluteEfficiency.at(i) * myInput.gammaIntensity.at(i) * myInput.relativeDeadTime * (1-exp(-1.0 * (log(2)/myInput.halfLife) * myInput.countingTime)));
        errorDummy=dummy*sqrt(pow(myInput.errorGammaIntensity.at(i)/myInput.gammaIntensity.at(i),2) + pow(myInput.errorAbsoluteEfficiency.at(i)/myInput.absoluteEfficiency.at(i),2)+pow(myInput.errorRelativeDeadTime/myInput.relativeDeadTime,2)
                              +pow(log(2)*myInput.errorWaitingTime/myInput.halfLife,2)+pow(log(2)/myInput.halfLife*exp(-log(2)/myInput.halfLife*myInput.countingTime)/(1-exp(-log(2)/myInput.halfLife*myInput.countingTime))*myInput.errorCountingTime,2)
                              +pow(log(2)/pow(myInput.halfLife,2)*(myInput.waitingTime + exp(-log(2)/myInput.halfLife*myInput.countingTime)/(1-exp(-log(2)/myInput.halfLife*myInput.countingTime))) * myInput.errorHalfLife,2));

        qDebug() << dummy;

        myInput.N_Prod.push_back(dummy);
        myInput.errorN_Prod.push_back(errorDummy);
    }

    emit N_ProdFinished();
}

void bamCore::calSigma(){
    
    for(int i = 0 ; i< myInput.N_Prod.size(); i++){
        double X=0.0;
        double errorX=0;

        qDebug() << "\nX value:";
        for(int j=0; j< myInput.phi.size(); j++){
            if(j){
                X*=exp(-1.0 * (log(2.0)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)));
                X+=(myInput.phi.at(j) * (1 - exp(-1.0 * (log(2.0)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)))));
            }
            else{
                X+= (myInput.phi.at(j) * (1 - exp(-1.0 * (log(2.0)/myInput.halfLife) * myInput.currentTime.at(j))));
            }
        }
    qDebug() << X;
    X*= myInput.targetThickness/ (log(2.0)/myInput.halfLife);
	qDebug() << "\nX value:";
	qDebug() << X;
	qDebug() << "\n Cross Sections:";
        myInput.sigma.push_back(myInput.N_Prod.at(i)/X);
        myInput.errorSigma.push_back(myInput.N_Prod.at(i)/X * sqrt(pow(myInput.errorN_Prod.at(i)/myInput.N_Prod.at(i), 2)));
        qDebug() << myInput.N_Prod.at(i)/X;
    }

    emit SigmaFinished();
}

void bamCore::calNofT(){
    QVector<double> dummy, dummy2;
    double X=0;
    for(int i = 0; i< myInput.N_Prod.size(); i++){
        dummy2.push_back(0);
        X=0;

        for(int j=0; j<myInput.phi.size();j++){
            if(!j){
                X+=(myInput.phi.at(j) * (1 - exp(-1 * (log(2)/myInput.halfLife) * myInput.currentTime.at(j))) * myInput.targetThickness * myInput.sigma.at(i))/ (log(2)/myInput.halfLife);
            }
            else{
                X*=exp(-1.0 * (log(2.0)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)));
                X+= (myInput.phi.at(j) * (1 - exp(-1 * (log(2)/myInput.halfLife) * (myInput.currentTime.at(j)-myInput.currentTime.at(j-1)))) * myInput.targetThickness * myInput.sigma.at(i))/ (log(2)/myInput.halfLife);
            }

            dummy.push_back(X);

            /*if(j){
                dummy2.push_back(dummy.at(j)-dummy.at(j-1));
            }*/
        }

        myInput.NofT.push_back(dummy);
        //myInput.diffNofT.push_back(dummy2);
        dummy.clear();
        dummy2.clear();


        for(int k=0; k<myInput.currentTime.size(); k++){
            myInput.TfromN.push_back(myInput.currentTime.at(k));
        }
        
    }
    

    int stop=myInput.phi.size()-1;

    for(int m = 0 ; m< myInput.N_Prod.size(); m++){
        myInput.diffNofT.at(m).push_back(0);
        for(int i=0; i< 2*(myInput.waitingTime+myInput.countingTime)/2000; i++){
		double Nnew=myInput.NofT.at(m).at(stop+i)*exp(-1*(log(2)*2000/myInput.halfLife));
                myInput.NofT.at(m).push_back(Nnew);
                /*if(i){
                    myInput.diffNofT.at(m).push_back(myInput.NofT.at(m).at(stop+i+1)-myInput.NofT.at(m).at(stop+i));
                }*/

                if(!m){
                    myInput.TfromN.push_back(myInput.TfromN.at(stop+i)+2000);
                }
        }
    }   
}
