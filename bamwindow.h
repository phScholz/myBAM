#ifndef BAMWINDOW_H
#define BAMWINDOW_H

#include <QMainWindow>
#include "baminput.h"
#include "bamcore.h"
#include "bameff.h"
#include <QComboBox>

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




    void on_closeButton_clicked();

    void on_currentButton_clicked();

    void on_nprodButton_clicked();

private:
    Ui::bamWindow *ui;

    QString filename;    
};

#endif // BAMWINDOW_H
