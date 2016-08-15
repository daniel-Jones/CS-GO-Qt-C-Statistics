#ifndef FILE_DOWNLOAD_H
#define FILE_DOWNLOAD_H
#include <QString>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include "message_box.h"

class file_download
{
public:
    file_download();
    int download_file(QString url, QString save_location);
private:
    QNetworkAccessManager http;
    QEventLoop loop;
    message_box msgbox;
};

#endif // FILE_DOWNLOAD_H
