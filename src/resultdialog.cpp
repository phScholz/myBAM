#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QDebug>

resultDialog::resultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultDialog)
{
    ui->setupUi(this);
    setWindowTitle("myBAM - Results");
    emit isOpened();
    ui->resultBox->setPlainText("\nEnergy\tValue[cm^2]\tError\n\n");
}

resultDialog::~resultDialog()
{
    delete ui;
}

void resultDialog::showResults(QString text){
    ui->resultBox->appendPlainText(text);
    qDebug() << "funzt";
}
