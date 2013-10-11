/******************************************************************************

    bamwindow.h

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
#ifndef BAMWINDOW_H
#define BAMWINDOW_H

#include <QMainWindow>
#include "baminput.h"
#include "bamcore.h"
#include "bameff.h"
#include <QComboBox>
#include <QDateEdit>
namespace Ui {
class bamWindow;
}

class bamWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit bamWindow(QWidget *parent = 0);
    ~bamWindow();

    //bamInput input;
    bamCore *myBAM;
    bamEff *myEff;

    QComboBox *combo0;
    QComboBox *combo1;
    QComboBox *combo2;
    QComboBox *combo3;
    QComboBox *combo4;

    QDateEdit *date0;
    QDateEdit *date1;
    QDateEdit *date2;
    QDateEdit *date3;
    QDateEdit *date4;    


signals:
    void pushButtonPressed();
    void beginCal();
    
public slots:
    void setProgressBar(int );
    void calFinished();
    void plot(int index);




private slots:
    void on_calButton_clicked();

    void on_browseButton_clicked();

    void resetInput();

    void getInput();

    void readCountingInput();

    void displayResults();

    void plotCurrent();

    void plotNprod();

    void plotDiffN();

    void loadFile();

    void saveFile();

    void exportFile();

    void setUpSourceTable();

    void tableSelectionChanged();

    void sourceSelectedC0(QString);
    void sourceSelectedC1(QString);
    void sourceSelectedC2(QString);
    void sourceSelectedC3(QString);
    void sourceSelectedC4(QString);

    void dateChanged0(QDate);
    void dateChanged1(QDate);
    void dateChanged2(QDate);
    void dateChanged3(QDate);
    void dateChanged4(QDate);

    void on_closeButton_clicked();

    void on_currentButton_clicked();

    void on_nprodButton_clicked();

private:
    Ui::bamWindow *ui;

    QString filename;    
};

#endif // BAMWINDOW_H
