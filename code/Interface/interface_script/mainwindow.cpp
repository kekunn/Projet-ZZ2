#include "ui_mainwindow.h"
#include "Argument.h"



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
        std::vector<QStringList> args_list;
        QStringList arguments{"peps_download.py", "--latmin", QString::fromUtf8(lat_min.c_str()),
                                                  "--latmax", QString::fromUtf8(lat_max.c_str()),
                                                  "--lonmin", QString::fromUtf8(long_min.c_str()),
                                                  "--lonmax", QString::fromUtf8(long_max.c_str()),
                                                  "--windows"};
        args_list.push_back(arguments);
        r.run(ui, args_list, 0);
    }
    else if (choice == 3)
    {
        QFile file(file_path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cout << "Impossible de lire le fichier !" << std::endl;
        }
        else
        {
            QTextStream in(&file);
            std::vector<std::pair<std::string, std::string>> coord_list;
            std::vector<QStringList> args_list;
            QString line = in.readLine();
            std::vector<QString> name_list;
            std::vector<Argument> args;

            while (!in.atEnd())
            {
                QDir root;
                QString line = in.readLine();

                QRegExp rx("[;]");// match a comma
                QStringList list = line.split(rx);
                std::cout << "Testss : " << list[8].toStdString() << std::endl;
                args.push_back(Argument(list[0],
                                        list[1],
                                        list[2],
                                        list[5],
                                        list[6],
                                        list[7],
                                        list[8]));

                coord_list.push_back(std::make_pair(list[0].toStdString(), list[1].toStdString()));
                name_list.push_back(list[2]);
                root.mkdir(root.absolutePath() + "/DL/" + list[2]);
            }

            for (int i = 0; i < coord_list.size(); i++)
            {
                QString latmin, latmax, longmin, longmax;

                double lattitude = std::stod(args[i].lat_.toStdString());
                double longitude = std::stod(args[i].lon_.toStdString());

                if (args[i].ecart_ != "")
                {
                    double ecart = std::stod(args[i].ecart_.toStdString());
                    latmin = QString::number(lattitude - ecart);
                    latmax = QString::number(lattitude + ecart);
                    longmin = QString::number(longitude - ecart);
                    longmax = QString::number(longitude + ecart);
                }
                else
                {
                    latmin = QString::number(lattitude - 0.2);
                    latmax = QString::number(lattitude + 0.2);
                    longmin = QString::number(longitude - 0.2);
                    longmax = QString::number(longitude + 0.2);
                }


                QStringList arguments{"peps_download.py", "--latmin", latmin,
                                                          "--latmax", latmax,
                                                          "--lonmin", longmin,
                                                          "--lonmax", longmax,
                                                          "--windows",
                                                          "-w", "./DL/" + name_list[i] };
                if (args[i].deb_ != "")
                {
                    arguments.push_back("--star_date");
                    arguments.push_back(args[i].deb_);
                }
                if (args[i].fin_ != "")
                {
                    arguments.push_back("--end_date");
                    arguments.push_back(args[i].fin_);
                }
                if (args[i].couv_ != "")
                {
                    arguments.push_back("--cc");
                    arguments.push_back(args[i].couv_);
                }

                std::cout << "On ajoute l'argument" << std::endl;
                args_list.push_back(arguments);
            }
            int size = args_list.size();
            for (int i = 0; i < size; i++)
            {
                args_list.push_back(args_list[i]);
            }
            r.run(ui, args_list, 0);
        }
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

void MainWindow::on_pushButton_2_clicked()
{
    QString path_file = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),
                                                     "D:/Download_D",
                                                     "All files (*.*);; CSV (*.csv)");
    QMessageBox::information(this, tr("File"), "Vous avez sélectionné : " + path_file);
    ui->textEdit_6->setText(path_file);
    file_path = path_file;
}






