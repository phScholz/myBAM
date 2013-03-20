#include "bamwindow.h"
#include "ui_bamwindow.h"
#include <QFileDialog>
#include "bamcore.h"
#include <QDebug>
#include "qcustomplot.h"
#include <QVector>
#include <QComboBox>

bamWindow::bamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bamWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    myBAM = new bamCore(this);

    connect(myBAM, SIGNAL(setProgressBar(int)), this, SLOT(setProgressBar(int)));
    connect(myBAM, SIGNAL(finished()), this, SLOT(calFinished()));
    connect(this, SIGNAL(beginCal()), myBAM, SLOT(beginCal()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));
    //connect(ui->resultToolbox, SIGNAL(currentChanged(int)), this, SLOT(plot(int)));

    ui->resultToolbox->setCurrentIndex(0);
    ui->resultToolbox->setEnabled(0);
    ui->currentButton->setEnabled(0);
    ui->nprodButton->setEnabled(0);


    //Efficiency Tab
    myEff =new bamEff(this);

    for (int i=0; i<5; i++) {
        QComboBox *combo = new QComboBox(this);
        combo->addItem("");
        for(int j=0; j<myEff->mySources.size(); j++){
            combo->addItem(myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")");
        }
        ui->eff_sourceTable->setCellWidget(i,0,combo);

       //connect(combo, SIGNAL(currentIndexChanged(int)),this, SLOT(changed(int)));
    }


}

bamWindow::~bamWindow()
{
    delete ui;
}


void bamWindow::on_calButton_clicked()
{
    if(ui->inputBox->toPlainText().toUtf8()!= "" && ui->currentPath->text()!=""){
        ui->outputBox->setPlainText("");
        resetInput();
        getInput();
        readCountingInput();
        ui->targetGroup->setEnabled(0);
        ui->currentGroup->setEnabled(0);
        ui->resultsGroup->setEnabled(0);
        ui->inputGroup->setEnabled(0);
        ui->calButton->setEnabled(0);        

        emit beginCal();
    }
}

void bamWindow::on_browseButton_clicked()
{
    QString dirname = QFileDialog::getOpenFileName(this, tr("Select File"), "./");
    //xs->setDirname(dirname);
    ui->currentPath->setText(dirname);
}

void bamWindow::getInput(){
    myBAM->myInput.targetThickness = ui->thickness->value() *1.0e15 ;
    myBAM->myInput.errorTargetThickness = ui->thicknessError->value();

    myBAM->myInput.relativeDeadTime = ui->reltd->value();
    myBAM->myInput.errorRelativeDeadTime = ui->reltdError->value();

    myBAM->myInput.countingTime = ui->tm->value();
    myBAM->myInput.errorCountingTime = ui->tmError->value();

    myBAM->myInput.waitingTime = ui->tw->value();
    myBAM->myInput.errorWaitingTime = ui->twError->value();

    myBAM->myInput.halfLife = ui->halflife->value();
    myBAM->myInput.errorHalfLife = ui->halflifeError->value();

    myBAM->myInput.currentFile = ui->currentPath->text();
}

void bamWindow::readCountingInput(){
    qDebug() << "\nRead Input:";
    QString text=ui->inputBox->toPlainText().toUtf8();
    QStringList lines;
    QVector<QStringList> values;
    if(text.contains("\n")){
        lines = text.split("\n");
    }
    else lines.push_back(text);

    for(int i=0; i<lines.size(); i++){
        if(lines.at(i).size()>0){
        values.push_back(lines.at(i).split(QRegExp( "[ \\t]+"), QString::SkipEmptyParts));
        }
    }

    for(int i=0; i<values.size(); i++){
        if(values.at(i).size()==7){
            myBAM->myInput.energy.push_back(values.at(i).at(0).toDouble());
            myBAM->myInput.gammaIntensity.push_back(values.at(i).at(1).toDouble());
            myBAM->myInput.errorGammaIntensity.push_back(values.at(i).at(2).toDouble());
            myBAM->myInput.absoluteEfficiency.push_back(values.at(i).at(3).toDouble());
            myBAM->myInput.errorAbsoluteEfficiency.push_back(values.at(i).at(4).toDouble());
            myBAM->myInput.peakCounts.push_back(values.at(i).at(5).toDouble());
            myBAM->myInput.errorPeakCounts.push_back(values.at(i).at(6).toDouble());

        qDebug() << values.at(i).at(0) << values.at(i).at(1) << values.at(i).at(2) << values.at(i).at(3) << values.at(i).at(4) << values.at(i).at(5) << values.at(i).at(6);
        }
        else{
            qDebug() << "Invalid number of arguments in line " << i;
        }
    }
}

void bamWindow::setProgressBar(int num){
    ui->progressBar->setValue(num);
}

void bamWindow::calFinished(){
    ui->resultToolbox->setEnabled(1);
    displayResults();
    ui->targetGroup->setEnabled(1);
    ui->currentGroup->setEnabled(1);
    ui->resultsGroup->setEnabled(1);
    ui->inputGroup->setEnabled(1);
    ui->calButton->setEnabled(1);
    ui->currentButton->setEnabled(1);
    ui->nprodButton->setEnabled(1);
}

void bamWindow::displayResults(){
    QString energy,cross, line, dcross;
    for(int i=0; i<myBAM->myInput.sigma.size(); i++){
        energy.setNum(myBAM->myInput.energy.at(i));
        cross.setNum(myBAM->myInput.sigma.at(i));
        dcross.setNum(myBAM->myInput.errorSigma.at(i));
        line=energy +" keV:\t" + cross + " +/- " + dcross;
        ui->outputBox->appendPlainText(line);
    }
}

void bamWindow::resetInput(){
    myBAM->myInput.energy.clear();
    myBAM->myInput.absoluteEfficiency.clear();
    myBAM->myInput.currentCount.clear();
    myBAM->myInput.currentTime.clear();
    myBAM->myInput.gammaIntensity.clear();
    myBAM->myInput.errorGammaIntensity.clear();
    myBAM->myInput.errorAbsoluteEfficiency.clear();
    myBAM->myInput.errorN_Prod.clear();
    myBAM->myInput.errorPhi.clear();
    myBAM->myInput.phi.clear();
    myBAM->myInput.peakCounts.clear();
    myBAM->myInput.errorPeakCounts.clear();
    myBAM->myInput.N_Prod.clear();
    myBAM->myInput.sigma.clear();
    myBAM->myInput.errorSigma.clear();
    myBAM->myInput.currentCountdiff.clear();
    myBAM->myInput.NofT.clear();
    myBAM->myInput.TfromN.clear();
    myBAM->myInput.diffNofT.clear();

}

void bamWindow::plotCurrent(){

    ui->currentPlot->clearGraphs();
    ui->currentPlot->setRangeDrag(Qt::Vertical|Qt::Horizontal);
    ui->currentPlot->setRangeZoom(Qt::Vertical|Qt::Horizontal);
    ui->currentPlot->xAxis->setRange(myBAM->myInput.currentTime.at(0),myBAM->myInput.currentTime.at(myBAM->myInput.currentTime.size()-1));
    ui->currentPlot->xAxis->setLabel("Time elapsed [s]");
    ui->currentPlot->yAxis->setLabel("Number of Particles");
    ui->currentPlot->addGraph();
    ui->currentPlot->graph(0)->setName("Target Current");
    ui->currentPlot->graph(0)->setData(myBAM->myInput.currentTime, myBAM->myInput.currentCountdiff);
    ui->currentPlot->graph(0)->setPen(QPen(Qt::darkGreen));
    ui->currentPlot->rescaleAxes();
    ui->currentPlot->replot();
}

void bamWindow::plotNprod(){

    if(myBAM->myInput.NofT.size()>=1 && myBAM->myInput.NofT.size() <= myBAM->myInput.sigma.size()){
        ui->nprodPlot->clearGraphs();
        ui->nprodPlot->setRangeDrag(Qt::Vertical|Qt::Horizontal);
        ui->nprodPlot->setRangeZoom(Qt::Vertical|Qt::Horizontal);
        ui->nprodPlot->xAxis->setLabel("Time elapsed [s]");
        ui->nprodPlot->yAxis->setLabel("Number of Nuclei");

        for(int i=0; i<1 /*myBAM->myInput.NofT.size()*/; i++){
	    qDebug()<< "Plotting Graph " << i+1;
            QString name;
            name.setNum(myBAM->myInput.energy.at(i));
            name+=" keV";

            switch(i){
                case 0:
                ui->nprodPlot->addGraph();
                ui->nprodPlot->graph(i)->setName(name);
                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(0));
                ui->nprodPlot->graph(i)->setPen(QPen(Qt::red));
                break;

                case 1:
                ui->nprodPlot->addGraph();
                ui->nprodPlot->graph(i)->setName(name);
                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
                ui->nprodPlot->graph(i)->setPen(QPen(Qt::green));
                break;

                case 2:
                ui->nprodPlot->addGraph();
                ui->nprodPlot->graph(i)->setName(name);
                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
                ui->nprodPlot->graph(i)->setPen(QPen(Qt::darkYellow));
                break;

                case 3:
                ui->nprodPlot->addGraph();
                ui->nprodPlot->graph(i)->setName(name);
                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
                ui->nprodPlot->graph(i)->setPen(QPen(Qt::cyan));
                break;

                case 4:
                ui->nprodPlot->addGraph();
                ui->nprodPlot->graph(i)->setName(name);
                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
                ui->nprodPlot->graph(i)->setPen(QPen(Qt::blue));
                break;

                case 5:
                ui->nprodPlot->addGraph();
                ui->nprodPlot->graph(i)->setName(name);
                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
                ui->nprodPlot->graph(i)->setPen(QPen(Qt::black));
                break;

                case 6:
                ui->nprodPlot->addGraph();
                ui->nprodPlot->graph(i)->setName(name);
                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
                ui->nprodPlot->graph(i)->setPen(QPen(Qt::gray));
                break;
            }
        }

        ui->nprodPlot->rescaleAxes();
        ui->nprodPlot->replot();
    }
}

void bamWindow::plotDiffN(){

    if(myBAM->myInput.NofT.size()>=1){
        ui->diffNprodPlot->clearGraphs();
        ui->diffNprodPlot->setRangeDrag(Qt::Vertical|Qt::Horizontal);
        ui->diffNprodPlot->setRangeZoom(Qt::Vertical|Qt::Horizontal);
        ui->diffNprodPlot->xAxis->setLabel("Time elapsed [s]");
        ui->diffNprodPlot->yAxis->setLabel("Number of Nuclei");

        for(int i=0; i<myBAM->myInput.NofT.size(); i++){
            QString name;
            name.setNum(myBAM->myInput.energy.at(i));
            name+=" keV";

            switch(i){
                case 0:
                ui->diffNprodPlot->addGraph();
                ui->diffNprodPlot->graph(i)->setName(name);
                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::red));
                break;

                case 1:
                ui->diffNprodPlot->addGraph();
                ui->diffNprodPlot->graph(i)->setName(name);
                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::green));
                break;

                case 2:
                ui->diffNprodPlot->addGraph();
                ui->diffNprodPlot->graph(i)->setName(name);
                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::darkYellow));
                break;

                case 3:
                ui->diffNprodPlot->addGraph();
                ui->diffNprodPlot->graph(i)->setName(name);
                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::cyan));
                break;

                case 4:
                ui->diffNprodPlot->addGraph();
                ui->diffNprodPlot->graph(i)->setName(name);
                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::blue));
                break;

                case 5:
                ui->diffNprodPlot->addGraph();
                ui->diffNprodPlot->graph(i)->setName(name);
                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::black));
                break;

                case 6:
                ui->diffNprodPlot->addGraph();
                ui->diffNprodPlot->graph(i)->setName(name);
                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::gray));
                break;
            }
        }

        ui->diffNprodPlot->rescaleAxes();
        ui->diffNprodPlot->replot();
    }
}

void bamWindow::saveFile(){

    filename=QFileDialog::getSaveFileName(this,tr("Save file"), tr("./"), tr("*.myBAM"));
    QString tt,ett,rdt,erdt,ct,ect,wt,ewt,hl,ehl,current, input, text;
    input="failure";

    if(!filename.contains(".myBAM")){
        filename.append(".myBAM");
    }

    tt.setNum(ui->thickness->value());
    ett.setNum(ui->thicknessError->value());

    rdt.setNum(ui->reltd->value());
    erdt.setNum(ui->reltdError->value());

    ct.setNum(ui->tm->value());
    ect.setNum(ui->tmError->value());

    wt.setNum(ui->tw->value());
    ewt.setNum(ui->twError->value());

    hl.setNum(ui->halflife->value());
    ehl.setNum(ui->halflifeError->value());

    current = ui->currentPath->text();

    input=ui->inputBox->toPlainText();

    text="#This is a myBAM settings-file\n";
    text+=tt + "\n" + ett + "\n" + rdt + "\n" + erdt + "\n" + ct + "\n" + ect + "\n" + wt + "\n" + ewt + "\n"+hl + "\n" + ehl + "\n" + current + "\n";

    qDebug() << text;

    QFile file(filename);

    file.open(QIODevice::WriteOnly);
    file.write(text.toUtf8());
    file.close();

    filename.append(".input");

    QFile file2(filename);
    file2.open(QIODevice::WriteOnly);
    file2.write(input.toUtf8());
    file2.close();

}

void bamWindow::loadFile(){

    filename=QFileDialog::getOpenFileName(this, tr("Select a myBAM file"), tr("./"), tr("*.myBAM"));

    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString text, line;
    QStringList lines;

    while(!in.atEnd()){

        line=in.readLine().append("\n");
        //if(!line.contains("#This is a myBAM settings-file")){
            text.append(line);
        //}
    }
    qDebug() << text;
    file.close();
    lines=text.split("\n");

    if(lines.size()>=11 && filename.contains(".myBAM") ){

        ui->thickness->setValue(lines.at(1).toDouble());
        ui->thicknessError->setValue(lines.at(2).toDouble());

        ui->reltd->setValue(lines.at(3).toDouble());
        ui->reltdError->setValue(lines.at(4).toDouble());

        ui->tm->setValue(lines.at(5).toDouble());
        ui->tmError->setValue(lines.at(6).toDouble());

        ui->tw->setValue(lines.at(7).toDouble());
        ui->twError->setValue(lines.at(8).toDouble());

        ui->halflife->setValue(lines.at(9).toDouble());
        ui->halflifeError->setValue(lines.at(10).toDouble());

        ui->currentPath->setText(lines.at(11));
    }

    filename.append(".input");
    qDebug()<< filename;
    QFile file2(filename);
    file2.open(QIODevice::ReadOnly);
    QTextStream in2(&file2);
    text="";
    while(!in2.atEnd()){
        text+=in2.readLine().append("\n");
    }
    qDebug() << text;
    ui->inputBox->setPlainText(text);
    file2.close();

}

void bamWindow::plot(int index){
    switch(index){
    case 1:
        plotCurrent();
        break;
    case 2:
        plotNprod();
        plotDiffN();
        break;
    default:
        break;
    }
}

void bamWindow::on_closeButton_clicked()
{
    close();
}

void bamWindow::on_currentButton_clicked()
{
    plotCurrent();
}

void bamWindow::on_nprodButton_clicked()
{
    plotNprod();
    //plotDiffN();
}
