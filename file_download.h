#ifndef FILE_DOWNLOAD_H
#define FILE_DOWNLOAD_H
#include <QString>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class file_download
{
public:
    file_download();
    int download_file(QString url, QString save_location);
private:
    QNetworkAccessManager http;
    QEventLoop loop;
};

#endif // FILE_DOWNLOAD_H
