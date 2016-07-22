#ifndef STATS_DISPLAY_WINDOW_H
#define STATS_DISPLAY_WINDOW_H

#include <QWidget>
#include <QDebug>
#include "file_download.h"
#include "parse_file.h"

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

    struct user_info { /* contains our user data for both steam and csgo */
        QString username;
        QString realname;
        QString avatar_url;
        QString status;
        QString time_ingame;
    } user;

    file_download download;
    parse_file parse;
signals:
      void window_loaded();

private slots:
    void window_open();
};

#endif // STATS_DISPLAY_WINDOW_H
