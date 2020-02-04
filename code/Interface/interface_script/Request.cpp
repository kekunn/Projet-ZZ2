#include "Request.h"

Request::Request()
{}

Request::Request(QStringList arguments) : _args(arguments)
{}

void Request::run (Ui::MainWindow* ui)
{
    std::cout << "On lance le script Python" << std::endl;
    script.start("python.exe", _args);

    if(!script.waitForStarted())
    {
        std::cout << "Impossible de lancer le script" << std::endl;
    }
    else
    {
        QObject::connect(&script, &QProcess::readyReadStandardError, this, [this, ui]() {
            QByteArray output = script.readAllStandardError();
            std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

            ui->output_display->append(output);
        });

        QObject::connect(&script, &QProcess::readyReadStandardOutput, this, [this, ui]() {
            QByteArray output = script.readAllStandardOutput();
            std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

            ui->output_display->append(output);
        });

        QObject::connect(&script, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, []() {
            std::cout << "Processus terminé !" << std::endl;
        });
    }
}

