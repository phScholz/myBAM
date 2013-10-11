/******************************************************************************

    resultdialog.cpp

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
