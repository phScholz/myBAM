/******************************************************************************

    creatorwindow.cpp

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

#include "creatorwindow.h"
#include "ui_creatorwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDate>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include "bamcore.h"
#include "resultdialog.h"
#include <QEventLoop>
#include <cmath>
#define debug

creatorWindow::creatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::creatorWindow)
{
    ui->setupUi(this);
    setWindowTitle("myBAM!!!");
    myBAM = new bamCore(this);
    connect(this, SIGNAL(beginCal()), myBAM, SLOT(beginCal()));
    connect(myBAM, SIGNAL(finished()), this, SLOT(displayResults()));
    myBAM->calMode="creator";



    for (unsigned int j=0; j<ui->countingTable->rowCount(); j++){
        for(int i=0; i<3; i++){
            ui->countingTable->setItem(j,i, new QTableWidgetItem(""));
        }
    }

    for (unsigned int j=0; j<ui->peakTable->rowCount(); j++){
        for(int i=0; i<7; i++){
            ui->peakTable->setItem(j,i, new QTableWidgetItem(""));
        }
    }

    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveForm()));
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseCurrent()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->calcButton, SIGNAL(clicked()), this, SLOT(calculate()));

    file=0;


}

creatorWindow::~creatorWindow()
{
    delete ui;
}

void creatorWindow::resetInput(){
        myBAM->myInput.waitingT.clear();
        myBAM->myInput.countingT.clear();
        myBAM->myInput.relLifeT.clear();
        myBAM->myInput.energy.clear();
        myBAM->myInput.gammaIntensity.clear();
        myBAM->myInput.errorGammaIntensity.clear();
        myBAM->myInput.absoluteEfficiency.clear();
        myBAM->myInput.errorAbsoluteEfficiency.clear();
        myBAM->myInput.peakCounts.clear();
        myBAM->myInput.errorPeakCounts.clear();
        myBAM->myInput.phi.clear();
        myBAM->myInput.currentCount.clear();
        myBAM->myInput.currentTime.clear();


        myBAM->myInput.sigma.clear();
        myBAM->myInput.errorSigma.clear();
        myBAM->myInput.errorSigma2.clear();
        myBAM->myInput.N_Prod.clear();
        myBAM->myInput.errorN_Prod.clear();
        myBAM->myInput.NofT.clear();
}

void creatorWindow::resetForm(){

    for (unsigned int j=0; j<ui->countingTable->rowCount(); j++){
        for(int i=0; i<3; i++){
            ui->countingTable->removeCellWidget(j,i);
        }
    }

    for (unsigned int j=0; j<ui->peakTable->rowCount(); j++){
        for(int i=0; i<7; i++){
            ui->peakTable->removeCellWidget(j,i);
        }
    }

    for (unsigned int j=0; j<ui->countingTable->rowCount(); j++){
        for(int i=0; i<3; i++){
            ui->countingTable->setItem(j,i, new QTableWidgetItem(""));
        }
    }

    for (unsigned int j=0; j<ui->peakTable->rowCount(); j++){
        for(int i=0; i<7; i++){
            ui->peakTable->setItem(j,i, new QTableWidgetItem(""));
        }
    }

    ui->halflifeValue->setText("");
    ui->halflifeError->setText("");
    ui->targetValue->setText("");
    ui->targetError->setText("");
    ui->pathLine->setText("");

}

void creatorWindow::getInput(){

    myBAM->myInput.targetThickness = ui->targetValue->text().toDouble()*1.0e15 ;

    myBAM->myInput.errorTargetThickness = ui->targetError->text().toDouble()*1.0e15;

    myBAM->myInput.halfLife = ui->halflifeValue->text().toDouble();
    myBAM->myInput.errorHalfLife = ui->halflifeError->text().toDouble();

    myBAM->myInput.currentFile = ui->pathLine->text();    

    for(int i=0; i<5; i++){
        if(ui->countingTable->item(i,0)->text().toInt())
            myBAM->myInput.waitingT.push_back(ui->countingTable->item(i,0)->text().toDouble());
        if(ui->countingTable->item(i,1)->text().toInt())
            myBAM->myInput.countingT.push_back(ui->countingTable->item(i,1)->text().toDouble());
        //if(ui->countingTable->item(i,2)->text().toInt())
            myBAM->myInput.relLifeT.push_back(ui->countingTable->item(i,2)->text().toDouble());
        qDebug() << ui->countingTable->item(i,2)->text().toDouble();
    }

    for(int i=0; i<10; i++){
        if(ui->peakTable->item(i,0)->text().toDouble())
            myBAM->myInput.energy.push_back(ui->peakTable->item(i,0)->text().toDouble());

        if(ui->peakTable->item(i,1)->text().toDouble())
            myBAM->myInput.gammaIntensity.push_back(ui->peakTable->item(i,1)->text().toDouble()/100);

        if(ui->peakTable->item(i,2)->text().toDouble())
            myBAM->myInput.errorGammaIntensity.push_back(ui->peakTable->item(i,2)->text().toDouble()/100);

        if(ui->peakTable->item(i,3)->text().toDouble())
            myBAM->myInput.absoluteEfficiency.push_back(ui->peakTable->item(i,3)->text().toDouble()/100);

        if(ui->peakTable->item(i,4)->text().toDouble())
            myBAM->myInput.errorAbsoluteEfficiency.push_back(ui->peakTable->item(i,4)->text().toDouble()/100);

        if(ui->peakTable->item(i,5)->text().toInt())
            myBAM->myInput.peakCounts.push_back(ui->peakTable->item(i,5)->text().toDouble());

        if(ui->peakTable->item(i,6)->text().toInt())
            myBAM->myInput.errorPeakCounts.push_back(ui->peakTable->item(i,6)->text().toDouble());
    }

#ifdef debug
    qDebug() << "TargetThickness: " << myBAM->myInput.targetThickness << myBAM->myInput.errorTargetThickness;
    qDebug() << "Half-Life: " << myBAM->myInput.halfLife<< myBAM->myInput.errorHalfLife;
    qDebug() << "Current File: " << myBAM->myInput.currentFile;
    qDebug() << "Counting:";
    for(int i=0; i<myBAM->myInput.waitingT.size(); i++){
        qDebug() << myBAM->myInput.waitingT.at(i) << myBAM->myInput.countingT.at(i) << myBAM->myInput.relLifeT.at(i);
    }
    qDebug() << "Peaks:";
    for(int i=0; i<myBAM->myInput.energy.size(); i++){
        qDebug() << myBAM->myInput.energy.at(i) << myBAM->myInput.gammaIntensity.at(i) << myBAM->myInput.errorGammaIntensity.at(i)
                    << myBAM->myInput.absoluteEfficiency.at(i) << myBAM->myInput.errorAbsoluteEfficiency.at(i)
                       << myBAM->myInput.peakCounts.at(i) << myBAM->myInput.errorPeakCounts.at(i);
    }
#endif

}

void creatorWindow::calculate(){
    resetInput();
    getInput();
    myBAM->calMode="creator";
    emit beginCal();
}

void creatorWindow::displayResults(){
    QEventLoop loop;
    resultDialog *a=new resultDialog;
    connect(a, SIGNAL(isOpened()), this, SLOT(sendResults()));
    connect(this, SIGNAL(results(QString)), a, SLOT(showResults(QString)));

    if(!file){
        a->show();
        if(a->isVisible()) sendResults();
        loop.exec();
    }
    else{
        sendResults();
        loop.quit();
    }

}

void creatorWindow::sendResults(){
    qDebug() << "Sending Results ...";
    QString energy,cross, line, dcross, dcross2, mittel, dmittel,dmittel2, text;
    double av, dav, dav2, sumSigmas, varIntern, varExtern;

    av=0;
    dav=0;
    dav2=0;
    text="";
    sumSigmas=0;
    varIntern=0;
    varExtern=0;


    for(int i=0; i<myBAM->myInput.sigma.size(); i++){
        energy.setNum(myBAM->myInput.energy.at(i));

        cross.setNum(myBAM->myInput.sigma.at(i));

        dcross.setNum(myBAM->myInput.errorSigma.at(i));
        dcross2.setNum(myBAM->myInput.errorSigma2.at(i));

        line=energy +" keV:\t" + cross + "\t " + dcross + "\t "+dcross2;

        av+=myBAM->myInput.sigma.at(i)/myBAM->myInput.errorSigma.at(i);
        sumSigmas+=1/myBAM->myInput.errorSigma.at(i);

        dav+=pow(myBAM->myInput.errorSigma.at(i)/myBAM->myInput.sigma.at(i),2);
        dav2+=pow(myBAM->myInput.errorSigma2.at(i)/myBAM->myInput.sigma.at(i),2);
        text+=line+"\n";
    }
    dav=sqrt(dav)*av/sumSigmas/myBAM->myInput.sigma.size();
    dav2=sqrt(dav2)*av/sumSigmas/myBAM->myInput.sigma.size();
    text+="--------------------------\n";
    mittel.setNum(av/sumSigmas);
    dmittel.setNum(dav);
    dmittel2.setNum(dav2);

   // text+="Average:\t" + mittel + "  +/-  " + dmittel + "  +/-  " + dmittel2;

    //system("clear");
    qDebug() << "Energy\t\tValue\t\tError stat\t\tsys";
    qDebug() << "\n"+text+"\n";

    if(!file){    emit results(text);}
}

void creatorWindow::closeWindow(){
    close();
}

void creatorWindow::saveForm(){
    saveFileName = QFileDialog::getSaveFileName(this,tr("Save file"), tr("./"), tr("*.myBAM"));
    setWindowTitle("myBAMCreator (..."+saveFileName.right(20)+")");
    saveInput();
}

void creatorWindow::browseCurrent(){
    currentFileName = QFileDialog::getOpenFileName(this, tr("Getting a myBAM-current file"), tr("./"), tr("*.mystrom"));
    ui->pathLine->setText(currentFileName);
}

void creatorWindow::loadFile(){
    resetForm();
    loadFileName = QFileDialog::getOpenFileName(this, tr("Getting a myBAM-input file"), tr("./"), tr("*.myBAM"));
    resetInput();
    loadInput();

}

void creatorWindow::loadInput(){
    waitingTime.clear();
    relativeLifeTime.clear();
    energy.clear();
    intensity.clear();
    intensityError.clear();
    countingTime.clear();
    peakCounts.clear();
    peakCountsError.clear();
    efficiency.clear();
    efficiencyError.clear();

    QFile file(loadFileName);

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,
                              "Load last settings",
                              "Couldn't open ..."+loadFileName.right(20),
                              QMessageBox::Ok);
    }
    else{


        QXmlStreamReader xml(&file);

        while(!xml.atEnd()){
            /* Read next element.*/
            xml.readNextStartElement();

            if(xml.hasError()){
                qDebug() << xml.errorString();
                break;
            }

            if(xml.isStartDocument()){
                continue;
            }

            if(xml.isStartElement()){

                if(xml.name()=="basicInput"){
                    qDebug() << "Reading basic Input...";
                    xml.readNextStartElement();

                    if(xml.name()=="numberOfTargetNuclei"){
                        ui->targetValue->setText(xml.readElementText());
                    }

                    xml.readNextStartElement();

                    if(xml.name()=="errorOfTargetNuclei"){
                        ui->targetError->setText(xml.readElementText());
                    }

                    xml.readNextStartElement();

                    if(xml.name()=="half-life"){
                        ui->halflifeValue->setText(xml.readElementText());
                    }

                    xml.readNextStartElement();

                    if(xml.name()=="errorOfHalf-life"){
                        ui->halflifeError->setText(xml.readElementText());
                    }
                }

                //Reading Counting Input

                for(int i=0; i<5; i++){
                    QString name;
                    name="RunWT"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            waitingTime.push_back(xml.text().toString());
                            ui->countingTable->item(i,0)->setText(waitingTime.at(i));
                            xml.readNext();
                        }
                    }
                }

                for(int i=0; i<5; i++){
                    QString name;
                    name="RunCT"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            countingTime.push_back(xml.text().toString());
                            ui->countingTable->item(i,1)->setText(countingTime.at(i));
                            xml.readNext();
                        }
                    }
                }

                for(int i=0; i<5; i++){
                    QString name;
                    name="RunRL"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            relativeLifeTime.push_back(xml.text().toString());
                            ui->countingTable->item(i,2)->setText(relativeLifeTime.at(i));
                            xml.readNext();
                        }
                    }
                }

                //Reading peak table ...

                for(int i=0; i<10; i++){
                    QString name;
                    name="energy"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            energy.push_back(xml.text().toString());                            
                            ui->peakTable->item(i,0)->setText(energy.at(i));
                            xml.readNext();
                        }
                    }
                }



                for(int i=0; i<10; i++){
                    QString name;
                    name="intensity"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            intensity.push_back(xml.text().toString());
                            ui->peakTable->item(i,1)->setText(intensity.at(i));
                            xml.readNext();
                        }
                    }
                }



                for(int i=0; i<10; i++){
                    QString name;
                    name="intensityError"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            intensityError.push_back(xml.text().toString());
                            ui->peakTable->item(i,2)->setText(intensityError.at(i));
                            xml.readNext();
                        }
                    }
                }


                for(int i=0; i<10; i++){
                    QString name;
                    name="efficiency"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            efficiency.push_back(xml.text().toString());
                            ui->peakTable->item(i,3)->setText(efficiency.at(i));
                            xml.readNext();
                        }
                    }
                }

                for(int i=0; i<10; i++){
                    QString name;
                    name="efficiencyError"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            efficiencyError.push_back(xml.text().toString());
                            ui->peakTable->item(i,4)->setText(efficiencyError.at(i));
                            xml.readNext();
                        }
                    }
                }

                for(int i=0; i<10; i++){
                    QString name;
                    name="counts"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            peakCounts.push_back(xml.text().toString());
                            ui->peakTable->item(i,5)->setText(peakCounts.at(i));
                            xml.readNext();
                        }
                    }
                }

                for(int i=0; i<10; i++){
                    QString name;
                    name="countsError"+QString::number(i+1);
                    if(xml.name()==name){
                        xml.readNext();
                        if(xml.tokenType()==QXmlStreamReader::Characters){
                            peakCountsError.push_back(xml.text().toString());
                            ui->peakTable->item(i,6)->setText(peakCountsError.at(i));
                            xml.readNext();
                        }
                    }                    
                }

                if(xml.name()=="currentFileName"){
                    xml.readNext();
                    if(xml.tokenType()==QXmlStreamReader::Characters){
                        currentFileName=xml.text().toString();
                        ui->pathLine->setText(currentFileName);
                    }
                }

            }
        }
    }

    qDebug()<< "File closed!";
    file.close();
}

void creatorWindow::saveInput(){
    if(saveFileName.right(6)!=".myBAM") saveFileName.append(".myBAM");

    QFile input(saveFileName);

    if(input.open(QIODevice::WriteOnly)){

        QDate date;
        date=QDate::currentDate();

        QTime time;
        time=QTime::currentTime();

        QString value;

        QXmlStreamWriter xmlwriter(&input);

        xmlwriter.setAutoFormatting(1);
        xmlwriter.writeStartDocument();
        xmlwriter.writeStartElement("myBAM-Input"); //Open myBamInput
        xmlwriter.writeAttribute("date", date.toString());
        xmlwriter.writeAttribute("time", time.toString());

        //Begin with number of Targetnuclei and Halflife
        xmlwriter.writeStartElement("basicInput");

        xmlwriter.writeTextElement("numberOfTargetNuclei", ui->targetValue->text());
        xmlwriter.writeTextElement("errorOfTargetNuclei", ui->targetError->text());
        xmlwriter.writeTextElement("half-life", ui->halflifeValue->text());
        xmlwriter.writeTextElement("errorOfHalf-life", ui->halflifeError->text());

        xmlwriter.writeEndElement();

        //Begin with counting periods
        qDebug() << "Writing countingTable input...";
        xmlwriter.writeStartElement("Counting");        
        xmlwriter.writeStartElement("waitingTime");
        qDebug() << "Writing waitingTimes ...";
        for(int i=0; i< ui->countingTable->rowCount(); i++){
            xmlwriter.writeTextElement("RunWT"+QString::number(i+1), ui->countingTable->item(i,0)->text());
        }

        xmlwriter.writeEndElement();

        xmlwriter.writeStartElement("countingTime");
        qDebug() << "Writing countingTimes ...";
        for(int i=0; i<ui->countingTable->rowCount(); i++){
            xmlwriter.writeTextElement("RunCT"+QString::number(i+1), ui->countingTable->item(i,1)->text());
        }
        xmlwriter.writeEndElement();

        xmlwriter.writeStartElement("relativeLifetime");
        for(int i=0; i< ui->countingTable->rowCount(); i++){
            xmlwriter.writeTextElement("RunRL"+QString::number(i+1), ui->countingTable->item(i,2)->text());
        }

        xmlwriter.writeEndElement();
        xmlwriter.writeEndElement();


        //Begin with Peakcounts
        qDebug() << "Writing peakTable input ...";
        xmlwriter.writeStartElement("Peaks");        
        for(int i=0; i<ui->peakTable->rowCount(); i++){
            xmlwriter.writeStartElement("Peak"+QString::number(i+1));
            xmlwriter.writeTextElement("energy"+QString::number(i+1), ui->peakTable->item(i,0)->text());
            xmlwriter.writeTextElement("intensity"+QString::number(i+1), ui->peakTable->item(i,1)->text());
            xmlwriter.writeTextElement("intensityError"+QString::number(i+1), ui->peakTable->item(i,2)->text());
            xmlwriter.writeTextElement("efficiency"+QString::number(i+1), ui->peakTable->item(i,3)->text());
            xmlwriter.writeTextElement("efficiencyError"+QString::number(i+1), ui->peakTable->item(i,4)->text());
            xmlwriter.writeTextElement("counts"+QString::number(i+1), ui->peakTable->item(i,5)->text());
            xmlwriter.writeTextElement("countsError"+QString::number(i+1), ui->peakTable->item(i,6)->text());
            xmlwriter.writeEndElement();
        }

        //CurrentFileName
        xmlwriter.writeTextElement("currentFileName", ui->pathLine->text());

        xmlwriter.writeEndElement();//close myBAM Input
        xmlwriter.writeEndDocument();

        input.close();
    }

}
