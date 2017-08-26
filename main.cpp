#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList fileNames = QCoreApplication::arguments();
    fileNames.removeFirst();

    qint8 fileCount = fileNames.count();

    // Quick file check before proceeding
    for (qint8 i = 0; i < fileCount; ++i) {
        bool doesit = QFile::exists(fileNames.at(i));
        if (!doesit) {
            qWarning() << "File(s) not found.";
            return 1;
        }
    }

    MainWindow w(fileNames, fileCount);
    w.show();

    return a.exec();
}
