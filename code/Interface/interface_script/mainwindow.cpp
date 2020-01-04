#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , city(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButton_clicked()
{
    city = true;
    ui->textEdit->setEnabled(true);
    ui->textEdit_2->setEnabled(false);
    ui->textEdit_3->setEnabled(false);
    ui->textEdit_4->setEnabled(false);
    ui->textEdit_5->setEnabled(false);
}

void MainWindow::on_radioButton_2_clicked()
{
    city = false;
    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(true);
    ui->textEdit_3->setEnabled(true);
    ui->textEdit_4->setEnabled(true);
    ui->textEdit_5->setEnabled(true);
}


void MainWindow::on_pushButton_clicked()
{
    if (city)
    {
        QProcess p;
        QStringList arguments { "peps_download.py", "-l", "Paris" };
        p.start("python", arguments);
        p.waitForFinished();
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
