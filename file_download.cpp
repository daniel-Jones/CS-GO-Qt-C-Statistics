#include "file_download.h"

file_download::file_download()
{

}

int file_download::file_download::download_file(QString url, QString save_location)
{
    /*
     * this function will download a given url/file to a location
     * no file location will be interpreted as . (current directory)
     */
    qDebug() << "downloading to " + save_location + " from " + url;
    if (QFile::exists(save_location))
        QFile::remove(save_location);
    QNetworkReply *reply = http.get(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();
    QFile file(save_location);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    delete reply;
    if (QFile::exists(save_location) && file.size() > 0)
        return 1; /* file downloaded - could just be a blank file at this point */
    else
        return 0; /* file did not download */
}
