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
