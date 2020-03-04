#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "mainwindow.h"


class Argument
{

    public :
    QString lat_;
    QString lon_;
    QString ville_;
    QString ecart_;
    QString deb_;
    QString fin_;
    QString couv_;

    Argument(QString lat, QString lon, QString ville, QString ecart, QString deb, QString fin, QString couv);
};


#endif // ARGUMENT_H
