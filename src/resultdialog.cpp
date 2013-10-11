#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QString>


resultDialog::resultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultDialog)
{
    ui->setupUi(this);
    setWindowTitle("myBAM - Results");
    emit isOpened();
    ui->resultBox->setPlainText("\nEnergy\tValue[cm^2]\tError\n\n");
    connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(exportResults()));
}

resultDialog::~resultDialog()
{
    delete ui;
}

void resultDialog::showResults(QString text){
    ui->resultBox->appendPlainText(text);
    qDebug() << "funzt";
}

void resultDialog::exportResults(){
    QString filename;
    filename = QFileDialog::getSaveFileName(this,tr("Save file"), tr("./"), tr("*.*"));

    QString content;
    content=ui->resultBox->toPlainText();

    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(content.toLatin1());
    file.close();
}
