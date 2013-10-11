#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class resultDialog;
}

class resultDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit resultDialog(QWidget *parent = 0);
    ~resultDialog();

public slots:
    void showResults(QString text);
    void exportResults();

signals:
    void isOpened();
    
private:
    Ui::resultDialog *ui;
};

#endif // RESULTDIALOG_H
