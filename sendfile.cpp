#include "sendfile.h"
#include "mainwindow.h"

sendFile::sendFile(QObject *parent) : QObject(parent)
{
}

void sendFile::start(QString fileLocation)
{
    QString remotename = "ftp://ftp.sta.sh/" + QFileInfo(fileLocation).fileName();
    QUrl url2(remotename);

    QSettings settings("Phobian", "Stasher");
    url2.setUserName(settings.value("user").toString());
    url2.setPassword(settings.value("pass").toString());

    QFile data(fileLocation, this);
    if (data.open(QIODevice::ReadOnly)) {
        reply = qnam->put (QNetworkRequest(url2), data.readAll());
        //qDebug() << reply->error();

        connect(reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(uploadProgress2(qint64, qint64)));
        connect(qnam, SIGNAL(finished(QNetworkReply *)), this, SLOT(uploadDone(QNetworkReply *)));

        if (reply->isRunning())
            emit workDone("Running");
        else
            emit workDone("Connection error");
    }
    else {
        emit workDone("Bad filename given.");
    }
}

void sendFile::uploadProgress2(qint64 done, qint64 total) {
    double percent = 0.0;

    if (done > 0 && total > 0)
        percent = ( done*100 )/total;

    emit yell(int(percent));
}

void sendFile::uploadDone(QNetworkReply *) {
    QString networkResult("Unknown error.");

    switch (reply->error()) {
    case QNetworkReply::NoError:
        networkResult = "Done";
        break;
    case QNetworkReply::AuthenticationRequiredError:
        networkResult = "Bad login or FTP not enabled\nin account settings.";
        break;
    default:
        break;
    }

    emit workDone(networkResult);
    reply->deleteLater();
}
