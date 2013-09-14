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
    
private slots:




private:
    Ui::creatorWindow *ui;
};

#endif // CREATORWINDOW_H
