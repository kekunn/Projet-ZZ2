#ifndef REQUEST_H
#define REQUEST_H

#include <QProcess>
#include <vector>
#include "ui_mainwindow.h"

class Request : public QObject
{
    Q_OBJECT
    public :
        Request();
        Request(QStringList arguments);

        void run (Ui::MainWindow* ui, std::vector<QStringList> arguments, int id);

    private :
        QStringList _args;
        QProcess* script;
};


#endif // REQUEST_H

