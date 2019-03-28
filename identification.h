#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H
#include <QString>
#include <QVector>

class Champs
{
public:
    QString Login;
    QString MotDePasse;
};

class Identification
{
public:
    QVector<Champs> vChamps;
    Identification(){}
};

#endif // IDENTIFICATION_H
