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

void stats_display_window::showEvent(QShowEvent *ev)
{
    emit window_loaded();
}

void stats_display_window::window_open()
{
    /*
     * this slot is called when our stats window is opened
     * we will parse our steam account file and edit the UI accordingly
     */
    user.username = parse.parse_user_data("\"personaname\":", ": ");
    user.realname = parse.parse_user_data("\"realname\":", ": ");
    user.avatar_url = parse.parse_user_data("\"avatarfull\":", ": ");
    user.status = parse.parse_user_data("\"personastate\":", ": ");
    download.download_file(user.avatar_url, "avatar.jpg");
    /* now we have to deal with our user account details */
    ui->username_label->setText(user.username);
    if (user.realname == NULL)
        ui->realname_label->setText("Realname not set");
    else
        ui->realname_label->setText(user.realname);
    QPixmap image("avatar.jpg");
    ui->avatar_label->setPixmap(image);

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
    user.time_ingame = parse.parse_csgo_data("total_time_played");
    QString time_in_game = "Hours in CS:GO: " + QString::number(user.time_ingame.toInt() / 3600);
    ui->time_in_label->setText(time_in_game);
    qDebug() << user.time_ingame.toInt();
}
