#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_clicked();

    void on_textEdit_textChanged();

    void on_textEdit_2_textChanged();

    void on_textEdit_3_textChanged();

    void on_textEdit_4_textChanged();

    void on_textEdit_5_textChanged();

private:
    Ui::MainWindow *ui;

    bool city;
    std::string city_name;
    std::string lat_min;
    std::string lat_max;
    std::string long_min;
    std::string long_max;
};
#endif // MAINWINDOW_H
