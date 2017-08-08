#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>

class sendFile : public QObject
{
    Q_OBJECT

public:
    explicit sendFile(QObject *parent = nullptr);
    void start(QString fileLocation);

private:
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
    QNetworkReply *reply;
    QFile *data;
signals:
    qint8 yell(qint8);
    QString workDone(QString);
public slots:

private slots:
    void uploadProgress2(qint64 done, qint64 total);
    void uploadDone(QNetworkReply *);
};

#endif // SENDFILE_H
