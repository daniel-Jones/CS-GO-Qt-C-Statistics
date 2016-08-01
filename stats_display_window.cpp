#include "stats_display_window.h"
#include "ui_stats_display_window.h"

stats_display_window::stats_display_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stats_display_window)
{
    ui->setupUi(this);
    connect(this, SIGNAL(window_loaded()), this, SLOT(window_open()), Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));
}

stats_display_window::~stats_display_window()
{
    delete ui;
}

void stats_display_window::setup_user()
{
    /*
     * this function sets up our user struct
     * TODO: CLEAN IT UP
     */
    user.username = parse.parse_user_data("\"personaname\":", ": ");
    user.realname = parse.parse_user_data("\"realname\":", ": ");
    user.avatar_url = parse.parse_user_data("\"avatarfull\":", ": ");
    user.status = parse.parse_user_data("\"personastate\":", ": ");
    user.user_64id = parse.parse_user_data("\"steamid\":", ": ");
    download.download_file(user.avatar_url, "avatar.jpg");
    /* now we have to deal with our user account details */
    ui->username_label->setText(user.username.left(15));
    if (user.realname == "null")
        ui->realname_label->setText("Real name not set");
    else
        ui->realname_label->setText(user.realname);
    if (user.username == "null")
    {
        QPixmap avatar(":/icons/icons/avatar.jpg");
        ui->avatar_label->setPixmap(avatar);
    }
    else
    {
        QPixmap avatar("avatar.jpg");
        ui->avatar_label->setPixmap(avatar);
    }
    /* user online status */
    switch(user.status.toInt())
    {
        case 0:
            ui->status_label->setText("<font color=red>Offline</font>");
        break;
        case 1:
            ui->status_label->setText("<font color=green>Online</font>");
        break;
        case 2:
            ui->status_label->setText("<font color=yellow>Busy</font>");
        break;
        case 3:
            ui->status_label->setText("<font color=orange>Away</font>");
        break;
        case 4:
            ui->status_label->setText("<font color=black>Snooze</font>");
        break;
        default:
            ui->status_label->setText("Unknown status");
        break;
    }
}

void stats_display_window::setup_csgo_data()
{
    /* this function populates our data templates and fills in the UI */
    /* tables */
    ui->weapon_table->setColumnCount(2);
    ui->weapon_table->setRowCount(33);
    ui->map_table->setColumnCount(2);
    ui->map_table->setRowCount(20);
    /*
     * set data in user.weapons
     * create a qlabel for each weapon * 2 and set the info
     */
    for (int x = 0; x < 33; x++)
    {
        /* parse stats */
        user.weapons[x][2] = parse.parse_csgo_data("total_kills_" + user.weapons[x][0]);
        user.weapons[x][3] = parse.parse_csgo_data("total_shots_" + user.weapons[x][0]);
        user.weapons[x][4] = parse.parse_csgo_data("total_hits_" + user.weapons[x][0]);
        user.weapons[x][5] = QString::number(user.weapons[x][4].toFloat() / user.weapons[x][3].toFloat(), 'f', 2);
        /* set weapon label */
        user.weapon_labels << new QLabel(this);
        user.weapon_labels.at(x)->setTextFormat(Qt::RichText);
        user.weapon_labels.at(x)->setText("<center><img src=" + user.weapons[x][1] + "> <br /> " + user.weapons[x][0] + " </center>");
        ui->weapon_table->setCellWidget(x, 0, user.weapon_labels.at(x));
        /* set weapon stat labels */
        user.stat_labels << new QLabel(this);
        user.stat_labels.at(x)->setTextFormat(Qt::RichText);
        user.stat_labels.at(x)->setText(user.weapons[x][2] + " kills <br />" + user.weapons[x][3] + " shots <br />" + user.weapons[x][4] + " hits <br />" + user.weapons[x][5] + " hit ratio");
        ui->weapon_table->setCellWidget(x, 1, user.stat_labels.at(x));
    }

    /*
     * set data in user.maps
     * create a qlabel for each map * 2 and set the info
     */
    for (int x = 0; x < 20; x++)
    {
        /* parse stats */
        user.maps[x][2] = parse.parse_csgo_data("total_rounds_map_" + user.maps[x][0] + '"');
        user.maps[x][3] = parse.parse_csgo_data("total_wins_map_" + user.maps[x][0] + '"');
        user.maps[x][4] = QString::number(user.maps[x][2].toInt() - user.maps[x][3].toInt());
        user.maps[x][5] = QString::number(user.maps[x][3].toFloat() / user.maps[x][2].toFloat(), 'f', 2);
        /* set map label */
        user.map_labels << new QLabel(this);
        user.map_labels.at(x)->setTextFormat(Qt::RichText);
        user.map_labels.at(x)->setText("<center><img src=" + user.maps[x][1] + "> <br /> " + user.maps[x][0] + " </center>");
        ui->map_table->setCellWidget(x, 0, user.map_labels.at(x));
        /* set map stat labels */
        user.map_stat_labels << new QLabel(this);
        user.map_stat_labels.at(x)->setTextFormat(Qt::RichText);
        user.map_stat_labels.at(x)->setText(user.maps[x][2] + " rounds <br />" + user.maps[x][3] + " won <br />" + user.maps[x][4] + " lost <br />" + user.maps[x][5] + " W/L ratio");
        ui->map_table->setCellWidget(x, 1, user.map_stat_labels.at(x));
    }

    /* time played */
    user.time_ingame = parse.parse_csgo_data("total_time_played");
    QString time_in_game = "Hours in CS:GO: " + QString::number(user.time_ingame.toInt() / 3600);
    ui->time_in_label->setText(time_in_game);
    /* mvp */
    user.mvp_count = parse.parse_csgo_data("total_mvps");
    ui->mvp_number_label->setTextFormat(Qt::RichText);
    ui->mvp_number_label->setText("<img width=20 height=20 src=:/icons/icons/mvp.png> " + user.mvp_count + " MVPs");
    /* total kills */
    ui->total_kills_label->setTextFormat(Qt::RichText);
    user.total_kills = parse.parse_csgo_data("total_kill");
    ui->total_kills_label->setText("<img width=20 height=20 src=:/icons/icons/domination.png> Total kills: " + QString::number(user.total_kills.toInt()));
    /* total deaths */
    user.total_deaths = parse.parse_csgo_data("total_deaths");
    ui->total_deaths_label->setText("<img width=20 height=20 src=:/icons/icons/suicide.png> Total deaths: " + QString::number(user.total_deaths.toInt()));
    /* k/d ratio */
    user.kd_ratio = QString::number(user.total_kills.toFloat() / user.total_deaths.toFloat()).toFloat();
    ui->kd_ratio_label->setText("K/D Ratio: " + QString::number(user.kd_ratio, 'f', 2));
}

void stats_display_window::reload_profile()
{
    /* a hacky function that refreshes stats displayed */
    qDebug() << "Attempting to download user data";
    QString file_loc = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=FEBFDE46520663091143F867FEE39BFF&steamids=" + user.user_64id;
    int success = download.download_file(file_loc, "userdata.dat");
    if (success == 1)
    {
        qDebug() << "Attempting to download cs:go data";
        file_loc = "http://api.steampowered.com/ISteamUserStats/GetUserStatsForGame/v0002/?appid=730&key=FEBFDE46520663091143F867FEE39BFF&steamid=" + user.user_64id;
        success = download.download_file(file_loc, "csgodata.dat");
    }
    if (success == 1)
    {
        window_open();
        qDebug() << "User data and CS:GO stats refreshed"; /* file could be ANYTHING or empty! */
    }
    else
    {
        qDebug() << "Failed";
    }
}

void stats_display_window::load_players()
{
    /* fill our lists and dropdown box with user data */
    ui->users_dropdown->clear();
    usernames.clear();
    userids.clear();
    parse.parse_users();
    usernames = parse.get_usernames();
    userids = parse.get_ids();
    for (int x = 0; x < usernames.length(); x++)
    {
        ui->users_dropdown->addItem(usernames.at(x));
    }
}

void stats_display_window::showEvent(QShowEvent *ev)
{
    emit window_loaded();
}

void stats_display_window::window_open()
{
    /*
     * this slot is called when our stats window is opened
     * we will call our user setup function
     * we will then call our csgo data setup function
     * we then need to load our players into the drop down box and lists
     */
    setup_user();
    setup_csgo_data();
    load_players();
}

void stats_display_window::on_refresh_button_clicked()
{
   reload_profile();
   load_players();
}

void stats_display_window::on_new_id_button_clicked()
{
    if (ui->new_steam_id->text() != "")
    {
        user.user_64id = ui->new_steam_id->text();
        reload_profile();
        load_players();
    }
}

void stats_display_window::on_users_dropdown_currentIndexChanged(int index)
{
    if (!usernames.isEmpty() && index != -1)
        ui->new_steam_id->setText(userids.at(index));
}

void stats_display_window::on_manage_users_button_clicked()
{
    manage.show();
}
