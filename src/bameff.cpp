/******************************************************************************

    bameff.cpp

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

#include "bameff.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

bamEff::bamEff(QObject *parent) :
    QObject(parent)
{
    QFile f("./stuff/quellen.dat");
    QStringList lines;
    QString text,line;

    qDebug() << "bamEff: Start to read quellen.dat!";

    if(f.open(QIODevice::ReadOnly)){
        QTextStream in(&f);
        while(!in.atEnd()){
            line= in.readLine().append("\n");
            if(!line.contains("#"))
                    text.append(line);
        }
        f.close();

        lines=text.split("\n");

        QVector<QStringList> values; //Array of QStringlists of size of the number of lines

        for(int i=0; i<lines.size()-1; i++){
            if(lines.at(i).size()>0){
            values.push_back(lines.at(i).split(QRegExp( "[ \\t]+"), QString::SkipEmptyParts));

            bamSource dummy;
            QDate date(2013,1,1);
                if(values.at(i).size()>=6){
                    dummy.isotope=values.at(i).at(0);
                    dummy.number=values.at(i).at(1);
                    dummy.startActivity=values.at(i).at(4).toDouble()*1000;
                    dummy.halfLife=values.at(i).at(5).toDouble()*365.25*24*3600;
                    dummy.startDate=date;

                    mySources.push_back(dummy);
                }
                else{
                    qDebug()<<"bamEff: Line too short: " << i;
                }

            }

        }

    }
    else qDebug() << "bamEff: Can not open quellen.dat!";
}
