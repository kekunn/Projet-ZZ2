#ifndef REQUEST_H
#define REQUEST_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

class Request : public QObject
{
    Q_OBJECT
    public :
        Request();
        Request(QStringList arguments);

        void run (Ui::MainWindow* ui);

    private :
        QStringList _args;
        QProcess script;
};


#endif // REQUEST_H

