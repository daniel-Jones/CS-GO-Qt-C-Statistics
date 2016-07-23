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
    ui->username_label->setText(user.username);
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
    /* most of the things in this function are images */
    int w = 100;
    int h = 50;
    ui->weapon_table->setColumnCount(2);
    ui->weapon_table->setRowCount(29);
    /* mvp */
    user.mvp_count = parse.parse_csgo_data("total_mvps");
    QPixmap mvp(":/icons/icons/mvp.png");
    ui->mvp_label->setPixmap(mvp.scaled(30, 30));
    QString mvp_count = user.mvp_count + " MVPs";
    ui->mvp_number_label->setText(mvp_count);
    /* time played */
    user.time_ingame = parse.parse_csgo_data("total_time_played");
    QString time_in_game = "Hours in CS:GO: " + QString::number(user.time_ingame.toInt() / 3600);
    ui->time_in_label->setText(time_in_game);
    /* awp */
    QLabel *awp_label = new QLabel(this);
    QLabel *awp_kills_label = new QLabel(this);
    QPixmap awp(":/weapons/weapons/awp.png");
    awp_label->setPixmap(awp.scaled(w, h));
    user.awp_kills = parse.parse_csgo_data("total_kills_awp");
    QString awp_kills_text = user.awp_kills + " kills";
    awp_kills_label->setText(awp_kills_text);
    ui->weapon_table->setCellWidget(0, 0, awp_label);
    ui->weapon_table->setCellWidget(0, 1, awp_kills_label);
    /* ak47 */
    QLabel *ak47_label = new QLabel(this);
    QLabel *ak47_kills_label = new QLabel(this);
    QPixmap ak47(":/weapons/weapons/ak47.png");
    ak47_label->setPixmap(ak47.scaled(w, h));
    user.ak47_kills = parse.parse_csgo_data("total_kills_ak47");
    QString ak47_kills_text = user.ak47_kills + " kills";
    ak47_kills_label->setText(ak47_kills_text);
    ui->weapon_table->setCellWidget(1, 0, ak47_label);
    ui->weapon_table->setCellWidget(1, 1, ak47_kills_label);
    /* deagle */
    QLabel *deagle_label = new QLabel(this);
    QLabel *deagle_kills_label = new QLabel(this);
    QPixmap deagle(":/weapons/weapons/deagle.png");
    deagle_label->setPixmap(deagle.scaled(w / 2, h));
    user.deagle_kills = parse.parse_csgo_data("total_kills_deagle");
    QString deagle_kills_text = user.deagle_kills + " kills";
    deagle_kills_label->setText(deagle_kills_text);
    ui->weapon_table->setCellWidget(2, 0, deagle_label);
    ui->weapon_table->setCellWidget(2, 1, deagle_kills_label);
    /* m4 */
    QLabel *m4_label = new QLabel(this);
    QLabel *m4_kills_label = new QLabel(this);
    QPixmap m4(":/weapons/weapons/m4.png");
    m4_label->setPixmap(m4.scaled(w, h));
    user.m4_kills = parse.parse_csgo_data("total_kills_m4");
    QString m4_kills_text = user.m4_kills + " kills";
    m4_kills_label->setText(m4_kills_text);
    ui->weapon_table->setCellWidget(3, 0, m4_label);
    ui->weapon_table->setCellWidget(3, 1, m4_kills_label);
    /* aug */
    QLabel *aug_label = new QLabel(this);
    QLabel *aug_kills_label = new QLabel(this);
    QPixmap aug(":/weapons/weapons/aug.png");
    aug_label->setPixmap(aug.scaled(w, h));
    user.aug_kills = parse.parse_csgo_data("total_kills_aug");
    QString aug_kills_text = user.aug_kills + " kills";
    aug_kills_label->setText(aug_kills_text);
    ui->weapon_table->setCellWidget(4, 0, aug_label);
    ui->weapon_table->setCellWidget(4, 1, aug_kills_label);
    /* bizon */
    QLabel *bizon_label = new QLabel(this);
    QLabel *bizon_kills_label = new QLabel(this);
    QPixmap bizon(":/weapons/weapons/bizon.png");
    bizon_label->setPixmap(bizon.scaled(w, h));
    user.bizon_kills = parse.parse_csgo_data("total_kills_bizon");
    QString bizon_kills_text = user.bizon_kills + " kills";
    bizon_kills_label->setText(bizon_kills_text);
    ui->weapon_table->setCellWidget(5, 0, bizon_label);
    ui->weapon_table->setCellWidget(5, 1, bizon_kills_label);
    /* elite */
    QLabel *elite_label = new QLabel(this);
    QLabel *elite_kills_label = new QLabel(this);
    QPixmap elite(":/weapons/weapons/elite.png");
    elite_label->setPixmap(elite.scaled(w, h));
    user.elite_kills = parse.parse_csgo_data("total_kills_elite");
    QString elite_kills_text = user.elite_kills + " kills";
    elite_kills_label->setText(elite_kills_text);
    ui->weapon_table->setCellWidget(6, 0, elite_label);
    ui->weapon_table->setCellWidget(6, 1, elite_kills_label);
    /* famas */
    QLabel *famas_label = new QLabel(this);
    QLabel *famas_kills_label = new QLabel(this);
    QPixmap famas(":/weapons/weapons/famas.png");
    famas_label->setPixmap(famas.scaled(w, h));
    user.famas_kills = parse.parse_csgo_data("total_kills_famas");
    QString famas_kills_text = user.famas_kills + " kills";
    famas_kills_label->setText(famas_kills_text);
    ui->weapon_table->setCellWidget(7, 0, famas_label);
    ui->weapon_table->setCellWidget(7, 1, famas_kills_label);
    /* fiveseven */
    QLabel *fiveseven_label = new QLabel(this);
    QLabel *fiveseven_kills_label = new QLabel(this);
    QPixmap fiveseven(":/weapons/weapons/fiveseven.png");
    fiveseven_label->setPixmap(fiveseven.scaled(w / 2, h));
    user.fiveseven_kills = parse.parse_csgo_data("total_kills_fiveseven");
    QString fiveseven_kills_text = user.fiveseven_kills + " kills";
    fiveseven_kills_label->setText(fiveseven_kills_text);
    ui->weapon_table->setCellWidget(8, 0, fiveseven_label);
    ui->weapon_table->setCellWidget(8, 1, fiveseven_kills_label);
    /* g3sg1 */
    QLabel *g3sg1_label = new QLabel(this);
    QLabel *g3sg1_kills_label = new QLabel(this);
    QPixmap g3sg1(":/weapons/weapons/g3sg1.png");
    g3sg1_label->setPixmap(g3sg1.scaled(w, h));
    user.g3sg1_kills = parse.parse_csgo_data("total_kills_g3sg1");
    QString g3sg1_kills_text = user.g3sg1_kills + " kills";
    g3sg1_kills_label->setText(g3sg1_kills_text);
    ui->weapon_table->setCellWidget(9, 0, g3sg1_label);
    ui->weapon_table->setCellWidget(9, 1, g3sg1_kills_label);
    /* galilar */
    QLabel *galilar_label = new QLabel(this);
    QLabel *galilar_kills_label = new QLabel(this);
    QPixmap galilar(":/weapons/weapons/galilar.png");
    galilar_label->setPixmap(galilar.scaled(w, h));
    user.galilar_kills = parse.parse_csgo_data("total_kills_galilar");
    QString galilar_kills_text = user.galilar_kills + " kills";
    galilar_kills_label->setText(galilar_kills_text);
    ui->weapon_table->setCellWidget(10, 0, galilar_label);
    ui->weapon_table->setCellWidget(10, 1, galilar_kills_label);
    /* glock */
    QLabel *glock_label = new QLabel(this);
    QLabel *glock_kills_label = new QLabel(this);
    QPixmap glock(":/weapons/weapons/glock.png");
    glock_label->setPixmap(glock.scaled(w / 2, h));
    user.glock_kills = parse.parse_csgo_data("total_kills_glock");
    QString glock_kills_text = user.glock_kills + " kills";
    glock_kills_label->setText(glock_kills_text);
    ui->weapon_table->setCellWidget(11, 0, glock_label);
    ui->weapon_table->setCellWidget(11, 1, glock_kills_label);
    /* hegrenade */
    QLabel *hegrenade_label = new QLabel(this);
    QLabel *hegrenade_kills_label = new QLabel(this);
    QPixmap hegrenade(":/weapons/weapons/hegrenade.png");
    hegrenade_label->setPixmap(hegrenade.scaled(w / 2, h));
    user.hegrenade_kills = parse.parse_csgo_data("total_kills_hegrenade");
    QString hegrenade_kills_text = user.hegrenade_kills + " kills";
    hegrenade_kills_label->setText(hegrenade_kills_text);
    ui->weapon_table->setCellWidget(12, 0, hegrenade_label);
    ui->weapon_table->setCellWidget(12, 1, hegrenade_kills_label);
    /* hkp2000 */
    QLabel *hkp2000_label = new QLabel(this);
    QLabel *hkp2000_kills_label = new QLabel(this);
    QPixmap hkp2000(":/weapons/weapons/hkp2000.png");
    hkp2000_label->setPixmap(hkp2000.scaled(w / 2, h));
    user.hkp2000_kills = parse.parse_csgo_data("total_kills_hkp2000");
    QString hkp2000_kills_text = user.hkp2000_kills + " kills";
    hkp2000_kills_label->setText(hkp2000_kills_text);
    ui->weapon_table->setCellWidget(13, 0, hkp2000_label);
    ui->weapon_table->setCellWidget(13, 1, hkp2000_kills_label);
    /* knife */
    QLabel *knife_label = new QLabel(this);
    QLabel *knife_kills_label = new QLabel(this);
    QPixmap knife(":/weapons/weapons/knife.png");
    knife_label->setPixmap(knife.scaled(w / 2, h));
    user.knife_kills = parse.parse_csgo_data("total_kills_knife");
    QString knife_kills_text = user.knife_kills + " kills";
    knife_kills_label->setText(knife_kills_text);
    ui->weapon_table->setCellWidget(14, 0, knife_label);
    ui->weapon_table->setCellWidget(14, 1, knife_kills_label);
    /* mac10 */
    QLabel *mac10_label = new QLabel(this);
    QLabel *mac10_kills_label = new QLabel(this);
    QPixmap mac10(":/weapons/weapons/mac10.png");
    mac10_label->setPixmap(mac10.scaled(w / 2, h));
    user.mac10_kills = parse.parse_csgo_data("total_kills_mac10");
    QString mac10_kills_text = user.mac10_kills + " kills";
    mac10_kills_label->setText(mac10_kills_text);
    ui->weapon_table->setCellWidget(15, 0, mac10_label);
    ui->weapon_table->setCellWidget(15, 1, mac10_kills_label);
    /* mag7 */
    QLabel *mag7_label = new QLabel(this);
    QLabel *mag7_kills_label = new QLabel(this);
    QPixmap mag7(":/weapons/weapons/mag7.png");
    mag7_label->setPixmap(mag7.scaled(w, h));
    user.mag7_kills = parse.parse_csgo_data("total_kills_mag7");
    QString mag7_kills_text = user.mag7_kills + " kills";
    mag7_kills_label->setText(mag7_kills_text);
    ui->weapon_table->setCellWidget(16, 0, mag7_label);
    ui->weapon_table->setCellWidget(16, 1, mag7_kills_label);
    /* mp7 */
    QLabel *mp7_label = new QLabel(this);
    QLabel *mp7_kills_label = new QLabel(this);
    QPixmap mp7(":/weapons/weapons/mp7.png");
    mp7_label->setPixmap(mp7.scaled(w / 2, h));
    user.mp7_kills = parse.parse_csgo_data("total_kills_mp7");
    QString mp7_kills_text = user.mp7_kills + " kills";
    mp7_kills_label->setText(mp7_kills_text);
    ui->weapon_table->setCellWidget(17, 0, mp7_label);
    ui->weapon_table->setCellWidget(17, 1, mp7_kills_label);
    /* negev */
    QLabel *negev_label = new QLabel(this);
    QLabel *negev_kills_label = new QLabel(this);
    QPixmap negev(":/weapons/weapons/negev.png");
    negev_label->setPixmap(negev.scaled(w, h));
    user.negev_kills = parse.parse_csgo_data("total_kills_negev");
    QString negev_kills_text = user.negev_kills + " kills";
    negev_kills_label->setText(negev_kills_text);
    ui->weapon_table->setCellWidget(18, 0, negev_label);
    ui->weapon_table->setCellWidget(18, 1, negev_kills_label);
    /* nova */
    QLabel *nova_label = new QLabel(this);
    QLabel *nova_kills_label = new QLabel(this);
    QPixmap nova(":/weapons/weapons/nova.png");
    nova_label->setPixmap(nova.scaled(w, h));
    user.nova_kills = parse.parse_csgo_data("total_kills_nova");
    QString nova_kills_text = user.nova_kills + " kills";
    nova_kills_label->setText(nova_kills_text);
    ui->weapon_table->setCellWidget(19, 0, nova_label);
    ui->weapon_table->setCellWidget(19, 1, nova_kills_label);
    /* p250 */
    QLabel *p250_label = new QLabel(this);
    QLabel *p250_kills_label = new QLabel(this);
    QPixmap p250(":/weapons/weapons/p250.png");
    p250_label->setPixmap(p250.scaled(w / 2, h));
    user.p250_kills = parse.parse_csgo_data("total_kills_p250");
    QString p250_kills_text = user.p250_kills + " kills";
    p250_kills_label->setText(p250_kills_text);
    ui->weapon_table->setCellWidget(20, 0, p250_label);
    ui->weapon_table->setCellWidget(20, 1, p250_kills_label);
    /* p90 */
    QLabel *p90_label = new QLabel(this);
    QLabel *p90_kills_label = new QLabel(this);
    QPixmap p90(":/weapons/weapons/p90.png");
    p90_label->setPixmap(p90.scaled(w, h));
    user.p90_kills = parse.parse_csgo_data("total_kills_p90");
    QString p90_kills_text = user.p90_kills + " kills";
    p90_kills_label->setText(p90_kills_text);
    ui->weapon_table->setCellWidget(21, 0, p90_label);
    ui->weapon_table->setCellWidget(21, 1, p90_kills_label);
    /* sawedoff */
    QLabel *sawedoff_label = new QLabel(this);
    QLabel *sawedoff_kills_label = new QLabel(this);
    QPixmap sawedoff(":/weapons/weapons/sawedoff.png");
    sawedoff_label->setPixmap(sawedoff.scaled(w, h));
    user.sawedoff_kills = parse.parse_csgo_data("total_kills_sawedoff");
    QString sawedoff_kills_text = user.sawedoff_kills + " kills";
    sawedoff_kills_label->setText(sawedoff_kills_text);
    ui->weapon_table->setCellWidget(22, 0, sawedoff_label);
    ui->weapon_table->setCellWidget(22, 1, sawedoff_kills_label);
    /* scar20 */
    QLabel *scar20_label = new QLabel(this);
    QLabel *scar20_kills_label = new QLabel(this);
    QPixmap scar20(":/weapons/weapons/scar20.png");
    scar20_label->setPixmap(scar20.scaled(w, h));
    user.scar20_kills = parse.parse_csgo_data("total_kills_scar20");
    QString scar20_kills_text = user.scar20_kills + " kills";
    scar20_kills_label->setText(scar20_kills_text);
    ui->weapon_table->setCellWidget(23, 0, scar20_label);
    ui->weapon_table->setCellWidget(23, 1, scar20_kills_label);
    /* sg556 */
    QLabel *sg556_label = new QLabel(this);
    QLabel *sg556_kills_label = new QLabel(this);
    QPixmap sg556(":/weapons/weapons/sg556.png");
    sg556_label->setPixmap(sg556.scaled(w, h));
    user.sg556_kills = parse.parse_csgo_data("total_kills_sg556");
    QString sg556_kills_text = user.sg556_kills + " kills";
    sg556_kills_label->setText(sg556_kills_text);
    ui->weapon_table->setCellWidget(24, 0, sg556_label);
    ui->weapon_table->setCellWidget(24, 1, sg556_kills_label);
    /* ssg08 */
    QLabel *ssg08_label = new QLabel(this);
    QLabel *ssg08_kills_label = new QLabel(this);
    QPixmap ssg08(":/weapons/weapons/ssg08.png");
    ssg08_label->setPixmap(ssg08.scaled(w, h));
    user.ssg08_kills = parse.parse_csgo_data("total_kills_ssg08");
    QString ssg08_kills_text = user.ssg08_kills + " kills";
    ssg08_kills_label->setText(ssg08_kills_text);
    ui->weapon_table->setCellWidget(25, 0, ssg08_label);
    ui->weapon_table->setCellWidget(25, 1, ssg08_kills_label);
    /* tec9 */
    QLabel *tec9_label = new QLabel(this);
    QLabel *tec9_kills_label = new QLabel(this);
    QPixmap tec9(":/weapons/weapons/tec9.png");
    tec9_label->setPixmap(tec9.scaled(w / 2, h));
    user.tec9_kills = parse.parse_csgo_data("total_kills_tec9");
    QString tec9_kills_text = user.tec9_kills + " kills";
    tec9_kills_label->setText(tec9_kills_text);
    ui->weapon_table->setCellWidget(26, 0, tec9_label);
    ui->weapon_table->setCellWidget(26, 1, tec9_kills_label);
    /* ump45 */
    QLabel *ump45_label = new QLabel(this);
    QLabel *ump45_kills_label = new QLabel(this);
    QPixmap ump45(":/weapons/weapons/ump45.png");
    ump45_label->setPixmap(ump45.scaled(w, h));
    user.ump45_kills = parse.parse_csgo_data("total_kills_ump45");
    QString ump45_kills_text = user.ump45_kills + " kills";
    ump45_kills_label->setText(ump45_kills_text);
    ui->weapon_table->setCellWidget(27, 0, ump45_label);
    ui->weapon_table->setCellWidget(27, 1, ump45_kills_label);
    /* xm1014 */
    QLabel *xm1014_label = new QLabel(this);
    QLabel *xm1014_kills_label = new QLabel(this);
    QPixmap xm1014(":/weapons/weapons/xm1014.png");
    xm1014_label->setPixmap(xm1014.scaled(w, h));
    user.xm1014_kills = parse.parse_csgo_data("total_kills_xm1014");
    QString xm1014_kills_text = user.xm1014_kills + " kills";
    xm1014_kills_label->setText(xm1014_kills_text);
    ui->weapon_table->setCellWidget(28, 0, xm1014_label);
    ui->weapon_table->setCellWidget(28, 1, xm1014_kills_label);
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
     */
    setup_user();
    setup_csgo_data();
}

void stats_display_window::on_refresh_button_clicked()
{
   reload_profile();
}

void stats_display_window::on_new_id_button_clicked()
{
    user.user_64id = ui->new_steam_id->text();
    reload_profile();
}
