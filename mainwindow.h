#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>
#include "sendfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QStringList &files, const qint8 &number = 0,  QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void showYell(qint8);
    void showResult(QString);

private:
    QStringList m_files;
    qint8 m_number;
    sendFile upload;
    qint8 upload_counter;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
