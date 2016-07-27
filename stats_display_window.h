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
    void setup_user();
    void setup_csgo_data();
    void reload_profile();
    void load_players();
    struct user_info {
        /* contains our user data for both steam and csgo */
        QString username;
        QString realname;
        QString avatar_url;
        QString user_64id;
        QString status;
        QString time_ingame;
        QString mvp_count;
        QString total_kills;
        QString total_deaths;
        float kd_ratio;
        /* weapon stats */
        QString ak47_kills;
        QString deagle_kills;
        QString m4_kills;
        QString awp_kills;
        QString aug_kills;
        QString bizon_kills;
        QString elite_kills;
        QString famas_kills;
        QString fiveseven_kills;
        QString g3sg1_kills;
        QString galilar_kills;
        QString glock_kills;
        QString hegrenade_kills;
        QString hkp2000_kills;
        QString knife_kills;
        QString m249_kills;
        QString mac10_kills;
        QString mag7_kills;
        QString mp7_kills;
        QString negev_kills;
        QString nova_kills;
        QString p250_kills;
        QString p90_kills;
        QString sawedoff_kills;
        QString scar20_kills;
        QString sg556_kills;
        QString ssg08_kills;
        QString tec9_kills;
        QString ump45_kills;
        QString xm1014_kills;
    } user;
    file_download download;
    parse_file parse;
    QStringList usernames;
    QStringList userids;
signals:
      void window_loaded();

private slots:
    void window_open();
    void on_refresh_button_clicked();
    void on_new_id_button_clicked();
    void on_users_dropdown_currentIndexChanged(int index);
};

#endif // STATS_DISPLAY_WINDOW_H
