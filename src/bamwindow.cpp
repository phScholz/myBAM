#include "bamwindow.h"
#include "ui_bamwindow.h"
#include <QFileDialog>
#include "bamcore.h"
#include <QDebug>
//#include "qcustomplot.h"
#include <QVector>
#include <QComboBox>
#include <QDate>

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
    connect(ui->eff_sourceTable, SIGNAL(itemSelectionChanged()), this, SLOT(tableSelectionChanged()));
    connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(exportFile()));
    //connect(ui->resultToolbox, SIGNAL(currentChanged(int)), this, SLOT(plot(int)));

    ui->resultToolbox->setCurrentIndex(0);
    ui->resultToolbox->setEnabled(0);
    ui->currentButton->setEnabled(0);
    ui->nprodButton->setEnabled(0);



    //Efficiency Tab
    //myEff =new bamEff(this);

    //setUpSourceTable();


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

        myBAM->calMode="normal";

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
    myBAM->myInput.errorTargetThickness = ui->thicknessError->value() *1.0e15;

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
    QString energy,cross, line, dcross, mittel, dmittel;
    double av, dav;
    av=0;
    dav=0;
    for(int i=0; i<myBAM->myInput.sigma.size(); i++){
        energy.setNum(myBAM->myInput.energy.at(i));
        cross.setNum(myBAM->myInput.sigma.at(i));
        dcross.setNum(myBAM->myInput.errorSigma.at(i));
        line=energy +" keV:\t" + cross + " +/- " + dcross;
        av+=myBAM->myInput.sigma.at(i)/myBAM->myInput.sigma.size();
        dav+=myBAM->myInput.errorSigma.at(i)/myBAM->myInput.sigma.size();
        ui->outputBox->appendPlainText(line);
    }
    ui->outputBox->appendPlainText("-------------");
    ui->outputBox->appendPlainText("");
    mittel.setNum(av);
    dmittel.setNum(dav);
    ui->outputBox->appendPlainText("Average:\t" + mittel + " +/- " + dmittel);
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

//    ui->currentPlot->clearGraphs();
//    ui->currentPlot->setRangeDrag(Qt::Vertical|Qt::Horizontal);
//    ui->currentPlot->setRangeZoom(Qt::Vertical|Qt::Horizontal);
//    ui->currentPlot->xAxis->setRange(myBAM->myInput.currentTime.at(0),myBAM->myInput.currentTime.at(myBAM->myInput.currentTime.size()-1));
//    ui->currentPlot->xAxis->setLabel("Time elapsed [s]");
//    ui->currentPlot->yAxis->setLabel("Number of Particles");
//    ui->currentPlot->addGraph();
//    ui->currentPlot->graph(0)->setName("Target Current");
//    ui->currentPlot->graph(0)->setData(myBAM->myInput.currentTime, myBAM->myInput.currentCountdiff);
//    ui->currentPlot->graph(0)->setPen(QPen(Qt::darkGreen));
//    ui->currentPlot->rescaleAxes();
//    ui->currentPlot->replot();
}

void bamWindow::plotNprod(){

//    if(myBAM->myInput.NofT.size()>=1 && myBAM->myInput.NofT.size() <= myBAM->myInput.sigma.size()){
//        ui->nprodPlot->clearGraphs();
//        ui->nprodPlot->setRangeDrag(Qt::Vertical|Qt::Horizontal);
//        ui->nprodPlot->setRangeZoom(Qt::Vertical|Qt::Horizontal);
//        ui->nprodPlot->xAxis->setLabel("Time elapsed [s]");
//        ui->nprodPlot->yAxis->setLabel("Number of Nuclei");

//        for(int i=0; i<1 /*myBAM->myInput.NofT.size()*/; i++){
//	    qDebug()<< "Plotting Graph " << i+1;
//            QString name;
//            name.setNum(myBAM->myInput.energy.at(i));
//            name+=" keV";

//            switch(i){
//                case 0:
//                ui->nprodPlot->addGraph();
//                ui->nprodPlot->graph(i)->setName(name);
//                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(0));
//                ui->nprodPlot->graph(i)->setPen(QPen(Qt::red));
//                break;

//                case 1:
//                ui->nprodPlot->addGraph();
//                ui->nprodPlot->graph(i)->setName(name);
//                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
//                ui->nprodPlot->graph(i)->setPen(QPen(Qt::green));
//                break;

//                case 2:
//                ui->nprodPlot->addGraph();
//                ui->nprodPlot->graph(i)->setName(name);
//                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
//                ui->nprodPlot->graph(i)->setPen(QPen(Qt::darkYellow));
//                break;

//                case 3:
//                ui->nprodPlot->addGraph();
//                ui->nprodPlot->graph(i)->setName(name);
//                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
//                ui->nprodPlot->graph(i)->setPen(QPen(Qt::cyan));
//                break;

//                case 4:
//                ui->nprodPlot->addGraph();
//                ui->nprodPlot->graph(i)->setName(name);
//                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
//                ui->nprodPlot->graph(i)->setPen(QPen(Qt::blue));
//                break;

//                case 5:
//                ui->nprodPlot->addGraph();
//                ui->nprodPlot->graph(i)->setName(name);
//                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
//                ui->nprodPlot->graph(i)->setPen(QPen(Qt::black));
//                break;

//                case 6:
//                ui->nprodPlot->addGraph();
//                ui->nprodPlot->graph(i)->setName(name);
//                ui->nprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.NofT.at(i));
//                ui->nprodPlot->graph(i)->setPen(QPen(Qt::gray));
//                break;
//            }
//        }

//        ui->nprodPlot->rescaleAxes();
//        ui->nprodPlot->replot();
//    }
}

void bamWindow::plotDiffN(){

//    if(myBAM->myInput.NofT.size()>=1){
//        ui->diffNprodPlot->clearGraphs();
//        ui->diffNprodPlot->setRangeDrag(Qt::Vertical|Qt::Horizontal);
//        ui->diffNprodPlot->setRangeZoom(Qt::Vertical|Qt::Horizontal);
//        ui->diffNprodPlot->xAxis->setLabel("Time elapsed [s]");
//        ui->diffNprodPlot->yAxis->setLabel("Number of Nuclei");

//        for(int i=0; i<myBAM->myInput.NofT.size(); i++){
//            QString name;
//            name.setNum(myBAM->myInput.energy.at(i));
//            name+=" keV";

//            switch(i){
//                case 0:
//                ui->diffNprodPlot->addGraph();
//                ui->diffNprodPlot->graph(i)->setName(name);
//                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
//                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::red));
//                break;

//                case 1:
//                ui->diffNprodPlot->addGraph();
//                ui->diffNprodPlot->graph(i)->setName(name);
//                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
//                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::green));
//                break;

//                case 2:
//                ui->diffNprodPlot->addGraph();
//                ui->diffNprodPlot->graph(i)->setName(name);
//                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
//                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::darkYellow));
//                break;

//                case 3:
//                ui->diffNprodPlot->addGraph();
//                ui->diffNprodPlot->graph(i)->setName(name);
//                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
//                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::cyan));
//                break;

//                case 4:
//                ui->diffNprodPlot->addGraph();
//                ui->diffNprodPlot->graph(i)->setName(name);
//                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
//                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::blue));
//                break;

//                case 5:
//                ui->diffNprodPlot->addGraph();
//                ui->diffNprodPlot->graph(i)->setName(name);
//                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
//                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::black));
//                break;

//                case 6:
//                ui->diffNprodPlot->addGraph();
//                ui->diffNprodPlot->graph(i)->setName(name);
//                ui->diffNprodPlot->graph(i)->setData(myBAM->myInput.TfromN, myBAM->myInput.diffNofT.at(i));
//                ui->diffNprodPlot->graph(i)->setPen(QPen(Qt::gray));
//                break;
//            }
//        }

//        ui->diffNprodPlot->rescaleAxes();
//        ui->diffNprodPlot->replot();
//    }
}

void bamWindow::saveFile(){

    filename=QFileDialog::getSaveFileName(this,tr("Save file"), tr("./"), tr("*.myBAM"));
    QString tt,ett,rdt,erdt,ct,ect,wt,ewt,hl,ehl,current, input, text;
    input="failure";

    if(!filename.contains(".myBAM")){
        filename.append(".myBAM");
    }

    tt.setNum(ui->thickness->value(),'g',10);
    ett.setNum(ui->thicknessError->value(),'g',10);

    rdt.setNum(ui->reltd->value(),'g',10);
    erdt.setNum(ui->reltdError->value(),'g',10);

    ct.setNum(ui->tm->value(),'g',10);
    ect.setNum(ui->tmError->value(),'g',10);

    wt.setNum(ui->tw->value(),'g',10);
    ewt.setNum(ui->twError->value(),'g',10);

    hl.setNum(ui->halflife->value(),'g',10);
    ehl.setNum(ui->halflifeError->value(),'g',10);

    current = ui->currentPath->text();

    input=ui->inputBox->toPlainText();

    text="#This is a myBAM settings-file\n";
    text+="#\n";
    text+="#N(Target)\tdN\trelLiveTime\tdrelLiveTime\tcountingTime\tdcountingTime\twaitingTime\tdwaitingTime\thalfLife\tdhalfLife\tcurrentpath\n";
    text+=tt + "\t" + ett + "\t" + rdt + "\t" + erdt + "\t" + ct + "\t" + ect + "\t" + wt + "\t" + ewt + "\t"+hl + "\t" + ehl + "\t" + current + "\n";
    text+="#\n#\n";
    text+="#-------------------------------INPUT-------------------------------\n";
    text+="#\n";
    text+="#E\tdE\tI\tdI\tEff\tdEff\tCounts\tdCounts\n#\n";
    text+=input;

    qDebug() << "Data which is going to be written into the savFile:";
    qDebug() << text;

    QFile file(filename);

    file.open(QIODevice::WriteOnly);
    file.write(text.toUtf8());
    file.close();
}

void bamWindow::loadFile(){

    filename=QFileDialog::getOpenFileName(this, tr("Select a myBAM file"), tr("./"), tr("*.myBAM"));
    setWindowTitle("myBAM (..."+filename.right(30)+")");
    QFile file(filename);
    qDebug() << "bamWindow: Opening File ...";
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString text, line, input;
    QStringList lines;
    QVector <QStringList> values;

    qDebug() << "bamWindow: Reading file content...";
    while(!in.atEnd()){

        line=in.readLine().append("\n");
        if(!(line.contains("#"))){
            text.append(line);
        }
    }
    qDebug() << text;
    file.close();
    qDebug() << "bamWindow: Closing file.";
    qDebug() << "bamWindow: Separating into lines ...";

    lines=text.split("\n");

    qDebug() << "bamWindow: Separating into values ...";

    for(int i=0; i<lines.size(); i++){
        values.push_back(lines.at(i).split(QRegExp( "[ \\t]+"), QString::SkipEmptyParts));
    }

    qDebug() << "bamWindow: Writing values to UI ...";

    if(lines.size()>=2 && values.at(0).size()==11){

        ui->thickness->setValue(values.at(0).at(0).toDouble());
        ui->thicknessError->setValue(values.at(0).at(1).toDouble());

        ui->reltd->setValue(values.at(0).at(2).toDouble());
        ui->reltdError->setValue(values.at(0).at(3).toDouble());

        ui->tm->setValue(values.at(0).at(4).toDouble());
        ui->tmError->setValue(values.at(0).at(5).toDouble());

        ui->tw->setValue(values.at(0).at(6).toDouble());
        ui->twError->setValue(values.at(0).at(7).toDouble());

        ui->halflife->setValue(values.at(0).at(8).toDouble());
        ui->halflifeError->setValue(values.at(0).at(9).toDouble());

        ui->currentPath->setText(values.at(0).at(10));

        for(int i=1; i<=lines.size()-1; i++){
            input="";
            for(int j=0; j<values.at(i).size(); j++){
                input+=values.at(i).at(j) + "   ";
            }
            ui->inputBox->append(input);
        }
    }
    else{
        qDebug() << "bamCore::ERROR: Malformed File to read ...!!";
    }

}

void bamWindow::exportFile(){
    filename=QFileDialog::getSaveFileName(this, tr("Save File ..."), tr("./"), tr("*.mBX"));
    if(filename.right(4)!=".mBX"){
        filename.append(".mBX");
    }

    QString energy,cross, line, dcross, text;
    for(int i=0; i<myBAM->myInput.sigma.size(); i++){
        energy.setNum(myBAM->myInput.energy.at(i));
        cross.setNum(myBAM->myInput.sigma.at(i));
        dcross.setNum(myBAM->myInput.errorSigma.at(i));
        line=energy +"\t" + cross + "\t" + dcross+"\n";
        text.append(line);
    }

    QFile file(filename);

    file.open(QIODevice::WriteOnly);
    file.write(text.toUtf8());
    file.close();


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

void bamWindow::setUpSourceTable(){

    //Setup all items
    for (int j=0; j<5; j++){
        for(int i=0; i<6; i++){
            ui->eff_sourceTable->setItem(j,i, new QTableWidgetItem(""));
        }
    }

    //---------------------COMBO BOXEN START--------------------------
    combo0= new QComboBox(this);
    combo0->addItem("");
    for(int j=0; j<myEff->mySources.size(); j++){
        combo0->addItem(myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")");
    }
    connect(combo0, SIGNAL(currentIndexChanged(QString)), this, SLOT(sourceSelectedC0(QString)));
    ui->eff_sourceTable->setCellWidget(0,0,combo0);

    combo1= new QComboBox(this);
    combo1->addItem("");
    for(int j=0; j<myEff->mySources.size(); j++){
        combo1->addItem(myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")");
    }
    connect(combo1, SIGNAL(currentIndexChanged(QString)), this, SLOT(sourceSelectedC1(QString)));
    ui->eff_sourceTable->setCellWidget(1,0,combo1);

    combo2= new QComboBox(this);
    combo2->addItem("");
    for(int j=0; j<myEff->mySources.size(); j++){
        combo2->addItem(myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")");
    }
    connect(combo2, SIGNAL(currentIndexChanged(QString)), this, SLOT(sourceSelectedC2(QString)));
    ui->eff_sourceTable->setCellWidget(2,0,combo2);

    combo3= new QComboBox(this);
    combo3->addItem("");
    for(int j=0; j<myEff->mySources.size(); j++){
        combo3->addItem(myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")");
    }
    connect(combo3, SIGNAL(currentIndexChanged(QString)), this, SLOT(sourceSelectedC3(QString)));
    ui->eff_sourceTable->setCellWidget(3,0,combo3);

    combo4= new QComboBox(this);
    combo4->addItem("");
    for(int j=0; j<myEff->mySources.size(); j++){
        combo4->addItem(myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")");
    }
    connect(combo4, SIGNAL(currentIndexChanged(QString)), this, SLOT(sourceSelectedC4(QString)));
    ui->eff_sourceTable->setCellWidget(4,0,combo4);

    //---------------------COMBO BOXEN ENDE--------------------------

    //---------------------DATE EDIT START---------------------------

    date0 = new QDateEdit(this);
    date0->setDate(QDate::currentDate());
    connect(date0, SIGNAL(dateChanged(QDate)), this, SLOT(dateChanged0(QDate)));
    ui->eff_sourceTable->setCellWidget(0,3,date0);

    date1 = new QDateEdit(this);
    date1->setDate(QDate::currentDate());
    connect(date1, SIGNAL(dateChanged(QDate)), this, SLOT(dateChanged1(QDate)));
    ui->eff_sourceTable->setCellWidget(1,3,date1);

    date2 = new QDateEdit(this);
    date2->setDate(QDate::currentDate());
    connect(date2, SIGNAL(dateChanged(QDate)), this, SLOT(dateChanged2(QDate)));
    ui->eff_sourceTable->setCellWidget(2,3,date2);

    date3 = new QDateEdit(this);
    date3->setDate(QDate::currentDate());
    connect(date3, SIGNAL(dateChanged(QDate)), this, SLOT(dateChanged3(QDate)));
    ui->eff_sourceTable->setCellWidget(3,3,date3);

    date4 = new QDateEdit(this);
    date4->setDate(QDate::currentDate());
    connect(date4, SIGNAL(dateChanged(QDate)), this, SLOT(dateChanged4(QDate)));
    ui->eff_sourceTable->setCellWidget(4,3,date4);

    //---------------------DATE EDIT ENDE---------------------------



}

void bamWindow::sourceSelectedC0(QString source){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(source == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac,dac;
            ac.setNum(myEff->mySources.at(j).startActivity*1000);
            dac.setNum(myEff->mySources.at(j).startActivity_error);

            qDebug() << "bamWindow: Writing text to Table ...";
            qDebug() << ac << dac << myEff->mySources.at(j).startDate.toString();
            ui->eff_sourceTable->item(0,1)->setText(ac);
            ui->eff_sourceTable->item(0,2)->setText(dac);
            date0->setDate(myEff->mySources.at(j).startDate);
        }
        else{
            //qDebug() << "bamWindow: Source not found ...";
        }
    }
}

void bamWindow::sourceSelectedC1(QString source){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(source == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac,dac;
            ac.setNum(myEff->mySources.at(j).startActivity*1000);
            dac.setNum(myEff->mySources.at(j).startActivity_error);

            qDebug() << "bamWindow: Writing text to Table ...";
            qDebug() << ac << dac << myEff->mySources.at(j).startDate.toString();
            ui->eff_sourceTable->item(1,1)->setText(ac);
            ui->eff_sourceTable->item(1,2)->setText(dac);
            date1->setDate(myEff->mySources.at(j).startDate);
        }
        else{
            //qDebug() << "bamWindow: Source not found ...";
        }
    }
}

void bamWindow::sourceSelectedC2(QString source){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(source == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac,dac;
            ac.setNum(myEff->mySources.at(j).startActivity*1000);
            dac.setNum(myEff->mySources.at(j).startActivity_error);

            qDebug() << "bamWindow: Writing text to Table ...";
            qDebug() << ac << dac << myEff->mySources.at(j).startDate.toString();
            ui->eff_sourceTable->item(2,1)->setText(ac);
            ui->eff_sourceTable->item(2,2)->setText(dac);
            date2->setDate(myEff->mySources.at(j).startDate);
        }
        else{
            //qDebug() << "bamWindow: Source not found ...";
        }
    }
}

void bamWindow::sourceSelectedC3(QString source){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(source == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac,dac;
            ac.setNum(myEff->mySources.at(j).startActivity*1000);
            dac.setNum(myEff->mySources.at(j).startActivity_error);

            qDebug() << "bamWindow: Writing text to Table ...";
            qDebug() << ac << dac << myEff->mySources.at(j).startDate.toString();
            ui->eff_sourceTable->item(3,1)->setText(ac);
            ui->eff_sourceTable->item(3,2)->setText(dac);
            date3->setDate(myEff->mySources.at(j).startDate);
        }
        else{
            //qDebug() << "bamWindow: Source not found ...";
        }
    }
}

void bamWindow::sourceSelectedC4(QString source){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(source == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac,dac;
            ac.setNum(myEff->mySources.at(j).startActivity*1000);
            dac.setNum(myEff->mySources.at(j).startActivity_error);

            qDebug() << "bamWindow: Writing text to Table ...";
            qDebug() << ac << dac << myEff->mySources.at(j).startDate.toString();
            ui->eff_sourceTable->item(4,1)->setText(ac);
            ui->eff_sourceTable->item(4,2)->setText(dac);
            date4->setDate(myEff->mySources.at(j).startDate);
        }
        else{
            //qDebug() << "bamWindow: Source not found ...";
        }
    }
}

void bamWindow::dateChanged0(QDate expDate){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(combo0->currentText() == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac;
            int diff=-expDate.daysTo(myEff->mySources.at(j).startDate);
            qDebug() << "bamWindow: Time difference: " << diff  << " days";
            double value=myBAM->activity(diff, myEff->mySources.at(j).startActivity*1000, myEff->mySources.at(j).halfLife);
            ac.setNum(value);
            qDebug() << "bamWindow: New activity: " + ac + " Bq";
            ui->eff_sourceTable->item(0,1)->setText(ac);
        }
   }
}


void bamWindow::dateChanged1(QDate expDate){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(combo1->currentText() == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac;
            int diff=-expDate.daysTo(myEff->mySources.at(j).startDate);
            qDebug() << "bamWindow: Time difference: " << diff  << " days";
            double value=myBAM->activity(diff, myEff->mySources.at(j).startActivity*1000, myEff->mySources.at(j).halfLife);
            ac.setNum(value);
            qDebug() << "bamWindow: New activity: " + ac + " Bq";
            ui->eff_sourceTable->item(1,1)->setText(ac);
        }
   }
}


void bamWindow::dateChanged2(QDate expDate){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(combo2->currentText() == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac;
            int diff=-expDate.daysTo(myEff->mySources.at(j).startDate);
            qDebug() << "bamWindow: Time difference: " << diff  << " days";
            double value=myBAM->activity(diff, myEff->mySources.at(j).startActivity*1000, myEff->mySources.at(j).halfLife);
            ac.setNum(value);
            qDebug() << "bamWindow: New activity: " + ac + " Bq";
            ui->eff_sourceTable->item(2,1)->setText(ac);
        }
   }
}


void bamWindow::dateChanged3(QDate expDate){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(combo3->currentText() == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac;
            int diff=-expDate.daysTo(myEff->mySources.at(j).startDate);
            qDebug() << "bamWindow: Time difference: " << diff  << " days";
            double value=myBAM->activity(diff, myEff->mySources.at(j).startActivity*1000, myEff->mySources.at(j).halfLife);
            ac.setNum(value);
            qDebug() << "bamWindow: New activity: " + ac + " Bq";
            ui->eff_sourceTable->item(3,1)->setText(ac);
        }
   }
}


void bamWindow::dateChanged4(QDate expDate){
    for(int j=0; j<myEff->mySources.size()-1; j++){
        if(combo4->currentText() == myEff->mySources.at(j).number + " (" + myEff->mySources.at(j).isotope + ")"){
            QString ac;
            int diff=-expDate.daysTo(myEff->mySources.at(j).startDate);
            qDebug() << "bamWindow: Time difference: " << diff  << " days";
            double value=myBAM->activity(diff, myEff->mySources.at(j).startActivity*1000, myEff->mySources.at(j).halfLife);
            ac.setNum(value);
            qDebug() << "bamWindow: New activity: " + ac + " Bq";
            ui->eff_sourceTable->item(4,1)->setText(ac);
        }
   }
}

void bamWindow::tableSelectionChanged(){
    for(int i=0; i<5; i++){
        for(int j=0; j<6; j++){
            if(ui->eff_sourceTable->item(i,j)->isSelected()){
                qDebug() << "Item(" << i << "," << j << ") is selected";
            }
        }
    }


}

