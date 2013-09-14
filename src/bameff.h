#ifndef BAMEFF_H
#define BAMEFF_H

#include <QObject>
#include <QVector>
#include "bamsource.h"



class bamEff : public QObject
{
    Q_OBJECT
public:
    explicit bamEff(QObject *parent = 0);

    QVector<bamSource> mySources;
    
signals:
    
public slots:
    
};

#endif // BAMEFF_H
