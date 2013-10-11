/******************************************************************************

    creatorwindow.h

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
#ifndef CREATORWINDOW_H
#define CREATORWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include "bamcore.h"

namespace Ui {
class creatorWindow;
}

class creatorWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit creatorWindow(QWidget *parent = 0);
    ~creatorWindow();

    bamCore *myBAM;
    int file;

    QString saveFileName;
    QString currentFileName;
    QString loadFileName;

    QStringList waitingTime;
    QStringList countingTime;
    QStringList relativeLifeTime;

    QStringList energy;
    QStringList intensity;
    QStringList intensityError;
    QStringList efficiency;
    QStringList efficiencyError;
    QStringList peakCounts;
    QStringList peakCountsError;

signals:
        void beginCal();
        void results(QString);

public slots:
        void displayResults();
        void sendResults();
        void closeWindow();
        void saveForm();
        void browseCurrent();
        void loadFile();
        void loadInput();
        void saveInput();
        void calculate();
        void getInput();
        void resetInput();
        void resetForm();
    
private slots:




private:
    Ui::creatorWindow *ui;
};

#endif // CREATORWINDOW_H
