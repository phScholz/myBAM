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
