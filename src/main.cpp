/******************************************************************************

    main.cpp

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

//#include "bamwindow.h"
#include "bamcore.h"
#include "creatorwindow.h"
#include <QApplication>
#include <QObject>
#include <QProcess>
#include <QDebug>

#define QUELLENDAT "./stuff/quellen.dat"

bool creatorWin=false;
bool bamWin=false;
bool noWin=false;
int file=0;


int switchParameters(QString para){

    if(para=="-c" || para=="--creator"){
        return 1;
    }

//    if(para=="-n" || para=="--normal"){
//        return 2;
//    }

    if(para=="-f" || para=="--file"){
        return 3;
    }

    if(para=="-h" || para=="--help"){
        qDebug() << "\nUSAGE:\t\tmyBAM <parameters> <file>\n";
        qDebug() << "PARAMETERS:\t-c/--creator\tIf this flag is set the myBAM program will only start in creator mode\n\t\t\t\twhich is a GUI window to create myBAM-input files.\n";
        qDebug() << "\t\t-n/--normal\t This will start myBAM in normal mode.";
        qDebug() << "\t\t-f/--file\t This will just calculate the cross sections out of a given *.myBAM file.";
        qDebug() << "\t\t-h/--help\t Opens this information.";
        return 0;
    }

    return 4;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    bamWindow *w = new bamWindow;
    creatorWindow *x = new creatorWindow;

    if(argc>1){
        for(int i=1; i<argc; i++){
            QString para(argv[i]);
            switch(switchParameters(para)){
                case 0: if(!file){
                            exit(1);
                        }
                        break;

                case 1: creatorWin=true;
                        break;

                case 2: bamWin=true;
                        break;

                case 3: file=i;
                        break;

            case 4: switchParameters("-h");
                    break;
            }
        }
    }

//    if(bamWin){
//        w->show();
//        return a.exec();
//    }

    if(creatorWin  || argc==1){
        x->show();
        return a.exec();
    }

    if(file){

        QString fileName(argv[file+1]);
        x->file=1;

        x->loadFileName=fileName;
        x->loadInput();
        x->calculate();


//        w->close();
        x->close();
        a.quit();
    }



}
