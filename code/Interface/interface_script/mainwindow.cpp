#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::black);
    ui->setupUi(this);
    ui->output_display->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButton_clicked()
{
    choice = 1;

    ui->textEdit->setEnabled(true);

    ui->pushButton_2->setEnabled(false);
    ui->textEdit_6->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->textEdit_3->setEnabled(false);
    ui->textEdit_4->setEnabled(false);
    ui->textEdit_5->setEnabled(false);
}

void MainWindow::on_radioButton_2_clicked()
{
    choice = 2;

    ui->textEdit->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->textEdit_6->setEnabled(false);

    ui->textEdit_2->setEnabled(true);
    ui->textEdit_3->setEnabled(true);
    ui->textEdit_4->setEnabled(true);
    ui->textEdit_5->setEnabled(true);
}

void MainWindow::on_radioButton_3_clicked()
{
    choice = 3;

    ui->pushButton_2->setEnabled(true);
    ui->textEdit_6->setEnabled(true);

    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->textEdit_3->setEnabled(false);
    ui->textEdit_4->setEnabled(false);
    ui->textEdit_5->setEnabled(false);
}


void MainWindow::on_pushButton_clicked()
{
    if (choice == 1)
    {

        QStringList arguments{"peps_download.py", "-l",  "Paris"};


        script.start("python.exe", arguments);
        if(!script.waitForStarted())
        {
            std::cout << "Impossible de lancer le script" << std::endl;
        }
        else
        {

            QObject::connect(&script, &QProcess::readyReadStandardError, this, [this]() {
                QByteArray output = script.readAllStandardError();
                std::cout << output.toStdString() << std::endl;

                ui->output_display->append(output);
            });
        }
    }
    else if (choice == 2)
    {
        QStringList arguments{"peps_download.py", "--latmin", QString::fromUtf8(lat_min.c_str()),
                                                  "--latmax", QString::fromUtf8(lat_max.c_str()),
                                                  "--lonmin", QString::fromUtf8(long_min.c_str()),
                                                  "--lonmax", QString::fromUtf8(long_max.c_str()),
                                                  "--windows"};
        std::cout << "On lance le script Python" << std::endl;
        script.start("python.exe", arguments);

        if(!script.waitForStarted())
        {
            std::cout << "Impossible de lancer le script" << std::endl;
        }
        else
        {

            QObject::connect(&script, &QProcess::readyReadStandardError, this, [this]() {
                QByteArray output = script.readAllStandardError();
                std::cout << "Sortie : " << output.length() << output.toStdString() << std::endl;

                ui->output_display->append(output);
            });
        }
    }
    else
    {

    }
}

void MainWindow::on_textEdit_textChanged()
{
    city_name = ui->textEdit->toPlainText().toUtf8().constData();
}

void MainWindow::on_textEdit_2_textChanged()
{
    lat_min = ui->textEdit_2->toPlainText().toUtf8().constData();
}

void MainWindow::on_textEdit_3_textChanged()
{
    lat_max = ui->textEdit_3->toPlainText().toUtf8().constData();
}

void MainWindow::on_textEdit_4_textChanged()
{
    long_min = ui->textEdit_4->toPlainText().toUtf8().constData();
}

void MainWindow::on_textEdit_5_textChanged()
{
    long_max = ui->textEdit_5->toPlainText().toUtf8().constData();
}




