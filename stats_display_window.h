#ifndef STATS_DISPLAY_WINDOW_H
#define STATS_DISPLAY_WINDOW_H

#include <QWidget>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include "file_download.h"

namespace Ui {
class stats_display_window;
}

class stats_display_window : public QWidget
{
    Q_OBJECT


protected:
      void showEvent(QShowEvent *ev);

public:
    explicit stats_display_window(QWidget *parent = 0);
    ~stats_display_window();

private:
    Ui::stats_display_window *ui;

    struct user_info {
        QString username;
        QString realname;
        QString avatar_url;
    } user;

    file_download download;
signals:
      void window_loaded();

private slots:
    void test();
};

#endif // STATS_DISPLAY_WINDOW_H
