#ifndef BAMSOURCE_H
#define BAMSOURCE_H


#include <QDate>
#include <QString>

class bamSource
{

public:
    bamSource();

    QString isotope;
    QString number;
    double startActivity;
    double startActivity_error;
    double halfLife;
    double halfLife_error;
    QDate startDate;

    int startYear;
    int startDay;
    int startMonth;

    
signals:
    
public slots:


};

#endif // BAMSOURCE_H
