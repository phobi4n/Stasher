#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sendfile.h"
#include <QCoreApplication>
#include <QStringList>

MainWindow::MainWindow(const QStringList &files, const qint8 &number,  QWidget *parent) :
    QMainWindow(parent),
    m_files(files),
    m_number(number),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&upload, SIGNAL(yell(qint8)), this, SLOT(showYell(qint8)));
    connect(&upload, SIGNAL(workDone(QString)), this, SLOT(showResult(QString)));

    QSettings settings("Phobian", "Stasher");
    ui->userEdit->setText(settings.value("user").toString());
    ui->passEdit->setText(settings.value("pass").toString());

    if(m_number == 0) {
        ui->statusLabel->setText("Nothing to upload.");
        ui->pushButton_2->setDisabled(true);
    }
    else if (m_number == 1)
        ui->statusLabel->setText(m_files.at(0));
    else
        ui->statusLabel->setText("Several files to upload");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    QString userString = (ui->userEdit) ? ui->userEdit->text() : "";
    QString passString = (ui->passEdit) ? ui->passEdit->text() : "";

    QSettings settings("Phobian", "Stasher");
    settings.setValue("user", userString);
    settings.setValue("pass", passString);

    ui->statusLabel->setText("Starting...");

    QEventLoop pause;
    connect(&upload, SIGNAL(workDone(QString)), &pause, SLOT(quit()));

    for (qint8 i=0; i<m_number; i++) {
        if (ui->statusLabel->text().startsWith("Bad"))
            break;
        upload.start(m_files.at(i));
        ui->statusLabel->setText(m_files.at(i));
        pause.exec();
    }
}

void MainWindow::showYell(qint8 percent)
{
    ui->progressBar->setValue(percent);
}

void MainWindow::showResult(QString answer)
{
    ui->statusLabel->setText(answer);
}


