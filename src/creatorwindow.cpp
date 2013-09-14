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
        myBAM->myInput.N_Prod.clear();
        myBAM->myInput.errorN_Prod.clear();
        myBAM->myInput.NofT.clear();
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
        if(ui->countingTable->item(i,2)->text().toInt())
            myBAM->myInput.relLifeT.push_back(ui->countingTable->item(i,2)->text().toDouble());
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
    QString energy,cross, line, dcross, mittel, dmittel, text;
    double av, dav, sumSigmas, varIntern, varExtern;

    av=0;
    dav=0;
    text="";
    sumSigmas=0;
    varIntern=0;
    varExtern=0;


    for(int i=0; i<myBAM->myInput.sigma.size(); i++){
        energy.setNum(myBAM->myInput.energy.at(i));

        cross.setNum(myBAM->myInput.sigma.at(i));

        dcross.setNum(myBAM->myInput.errorSigma.at(i));

        line=energy +" keV:\t" + cross + "   +/-   " + dcross;

        av+=myBAM->myInput.sigma.at(i)/myBAM->myInput.errorSigma.at(i);
        sumSigmas+=1/myBAM->myInput.errorSigma.at(i);

        dav+=myBAM->myInput.errorSigma.at(i)/myBAM->myInput.sigma.size();
        text+=line+"\n";
    }
    text+="--------------------------\n";
    mittel.setNum(av/sumSigmas);
    dmittel.setNum(dav);
    text+="Average:\t" + mittel + "  +/-  " + dmittel;

    //system("clear");
    qDebug() << "Energy\t\tValue\t\tError";
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
    loadFileName = QFileDialog::getOpenFileName(this, tr("Getting a myBAM-input file"), tr("./"), tr("*.myBAM"));
    loadInput();
}

void creatorWindow::loadInput(){

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
