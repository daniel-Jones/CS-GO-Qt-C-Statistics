#ifndef STATS_DISPLAY_WINDOW_H
#define STATS_DISPLAY_WINDOW_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include "file_download.h"
#include "parse_file.h"
#include "user_management.h"

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
        QString maps[20][6] = {
            /* map name | image location | rounds total | rounds win | rounds lost | win percent*/
            {"cs_assault", ":/maps/maps/cs_assault.png", "", "", ""},
            {"cs_italy", ":/maps/maps/cs_italy.png", "", "", "", ""},
            {"cs_office", ":/maps/maps/cs_office.png", "", "", "", ""},
            {"de_aztec", ":/maps/maps/de_aztec.png", "", "", "", ""},
            {"de_cbble", ":/maps/maps/de_cbble.png", "", "", "", ""},
            {"de_dust2", ":/maps/maps/de_dust2.png", "", "", "", ""},
            {"de_dust", ":/maps/maps/de_dust.png", "", "", "", ""},
            {"de_inferno", ":/maps/maps/de_inferno.png", "" "", "", ""},
            {"de_nuke", ":/maps/maps/de_nuke.png", "", "", "", ""},
            {"de_train", ":/maps/maps/de_train.png", "", "", "", ""},
            {"de_lake", ":/maps/maps/de_lake.png", "", "", "", ""},
            {"de_stmarc", ":/maps/maps/de_stmarc.png", "", "", "", ""},
            {"de_safehouse", ":/maps/maps/de_safehouse.png", "" "", "" , ""},
            {"ar_baggage", ":/maps/maps/ar_baggage.png", "", "", "", ""},
            {"ar_shoots", ":/maps/maps/ar_shoots.png", "", "", "", ""},
            {"de_bank", ":/maps/maps/de_bank.png", "", "", "", ""},
            {"ar_monas", ":/maps/maps/ar_monastery.png", "" "", "", ""},
            {"de_vertigo", ":/maps/maps/de_vertigo.png", "", "", "", ""},
            {"de_sugarcane", ":/maps/maps/de_sugarcane.png", "", "", "", ""},
            {"cs_militia", ":/maps/maps/cs_militia.png", "", "", "", ""},
        };
        QList<QLabel *> map_labels;
        QList<QLabel *> map_stat_labels;
        QString weapons[33][6] = {
        /*weapon name | image location | kills | shots | hits | ratio of hits to shots */
            {"ak47", ":/weapons/weapons/ak47.png", "0", "0", "0", "0"},
            {"awp", ":/weapons/weapons/awp.png", "0", "0", "0", "0"},
            {"p90", ":/weapons/weapons/p90.png", "0", "0", "0", "0"},
            {"deagle", ":/weapons/weapons/deagle.png", "0", "0", "0", "0"},
            {"m4", ":/weapons/weapons/m4a1.png", "0", "0", "0", "0"},
            {"knife", ":/weapons/weapons/knife.png", "0", "0", "0", "0"},
            {"fiveseven", ":/weapons/weapons/fiveseven.png", "0", "0", "0", "0"},
            {"hkp2000", ":/weapons/weapons/hkp2000.png", "0", "0", "0", "0"},
            {"glock", ":/weapons/weapons/glock.png", "0", "0", "0", "0"},
            {"p250", ":/weapons/weapons/p250.png", "0", "0", "0", "0"},
            {"mp7", ":/weapons/weapons/mp7.png", "0", "0", "0", "0"},
            {"galil", ":/weapons/weapons/galil.png", "0", "0", "0", "0"},
            {"ump45", ":/weapons/weapons/ump45.png", "0", "0", "0", "0"},
            {"tec9", ":/weapons/weapons/tec9.png", "0", "0", "0", "0"},
            {"negev", ":/weapons/weapons/negev.png", "0", "0", "0", "0"},
            {"m249", ":/weapons/weapons/m249.png", "0", "0", "0", "0"},
            {"g3sg1", ":/weapons/weapons/g3sg1.png", "0", "0", "0", "0"},
            {"scar20", ":/weapons/weapons/scar20.png", "0", "0", "0", "0"},
            {"aug", ":/weapons/weapons/aug.png", "0", "0", "0", "0"},
            {"sg556", ":/weapons/weapons/sg556.png", "0", "0", "0", "0"},
            {"nova", ":/weapons/weapons/nova.png", "0", "0", "0", "0"},
            {"sawedoff", ":/weapons/weapons/sawedoff.png", "0", "0", "0", "0"},
            {"xm1014", ":/weapons/weapons/xm1014.png", "0", "0", "0", "0"},
            {"mag7", ":/weapons/weapons/mag7.png", "0", "0", "0", "0"},
            {"mp9", ":/weapons/weapons/mpn.png", "0", "0", "0", "0"},
            {"ssg08", ":/weapons/weapons/ssg08.png", "0", "0", "0", "0"},
            {"bizon", ":/weapons/weapons/bizon.png", "0", "0", "0", "0"},
            {"mac10", ":/weapons/weapons/mac10.png", "0", "0", "0", "0"},
            {"famas", ":/weapons/weapons/famas.png", "0", "0", "0", "0"},
            {"hegrenade", ":/weapons/weapons/hegrenade.png", "0", "0", "0", "0"},
            {"elite", ":/weapons/weapons/elite.png", "0", "0", "0", "0"},
            {"taser", ":/weapons/weapons/taser.png", "0", "0", "0", "0"},
            {"molotov", ":/weapons/weapons/molotov.png", "0", "0", "0", "0"},
        };
        QList<QLabel *> weapon_labels;
        QList<QLabel *> stat_labels;
    } user;
    file_download download;
    parse_file parse;
    QStringList usernames;
    QStringList userids;
    user_management manage;
signals:
      void window_loaded();

private slots:
    void window_open();
    void on_refresh_button_clicked();
    void on_new_id_button_clicked();
    void on_users_dropdown_currentIndexChanged(int index);
    void on_manage_users_button_clicked();
};

#endif // STATS_DISPLAY_WINDOW_H
