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
