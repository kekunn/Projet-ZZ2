#include "Request.h"
#include <iostream>


Request::Request()
{}

Request::Request(QStringList arguments) : _args(arguments)
{}

void Request::run (Ui::MainWindow* ui, std::vector<QStringList> arguments, int id)
{
    script = new QProcess();
    /* Reset de l'affichage */
    ui->output_display->clear();

    QObject::connect(script, &QProcess::readyReadStandardError, this, [this, ui]() {
        QByteArray output = script->readAllStandardError();
        std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

        ui->output_display->append(output);
    });

    QObject::connect(script, &QProcess::readyReadStandardOutput, this, [this, ui]() {
        QByteArray output = script->readAllStandardOutput();
        std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

        ui->output_display->append(output);
    });


    QObject::connect(script, &QProcess::readyRead, this, [this, ui]() {
        QByteArray output = script->readAll();
        std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

        ui->output_display->append(output);
    });

    QObject::connect(script, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this, ui, id, arguments]() {
        std::cout << "Processus terminé !" << std::endl;

        script->kill();
        delete(script);

        if (id + 1 < arguments.size())
        {
            this->run(ui, arguments, id + 1);
        }
        else
        {
            std::cout << "Toutes les requetes sont traitees ! " << std::endl;
            ui->output_display->append("Toutes les requetes ont ete traitees !");
        }
    });














    std::cout << "On lance le script Python id : " << id << std::endl;
    ui->progressBar->setValue((float)(id + 1) / arguments.size() * 100);
    script->start("python.exe", arguments[id]);
/*
    if(!script->waitForStarted())
    {
        std::cout << "Impossible de lancer le script" << std::endl;
    }
    else
    {
        QObject::connect(script, &QProcess::readyReadStandardError, this, [this, ui]() {
            QByteArray output = script->readAllStandardError();
            std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

            ui->output_display->append(output);
        });

        QObject::connect(script, &QProcess::readyReadStandardOutput, this, [this, ui]() {
            QByteArray output = script->readAllStandardOutput();
            std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

            ui->output_display->append(output);
        });


        QObject::connect(script, &QProcess::readyRead, this, [this, ui]() {
            QByteArray output = script->readAll();
            std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

            ui->output_display->append(output);
        });

        QObject::connect(script, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this, ui, id, arguments]() {
            std::cout << "Processus terminé !" << std::endl;
            delete(script);

            if (id + 1 < arguments.size())
            {
                this->run(ui, arguments, id + 1);
            }
            else
            {
                std::cout << "Toutes les requetes sont traitees ! " << std::endl;
                ui->output_display->append("Toutes les requetes ont ete traitees !");
            }
        });
    }*/
}

