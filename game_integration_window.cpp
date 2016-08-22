#include "game_integration_window.h"
#include "ui_game_integration_window.h"

game_integration_window::game_integration_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_integration_window)
{
    ui->setupUi(this);
    server = new QTcpServer(this); /* create our server */
    connect(this, SIGNAL(window_loaded()), this, SLOT(window_open()));
    connect(server, SIGNAL(newConnection()), this, SLOT(new_connection()));
    ui->map_picture_label->setTextFormat(Qt::RichText);
    ui->ct_label->setTextFormat(Qt::RichText);
    ui->t_label->setTextFormat(Qt::RichText);
    ui->ct_label->setText("<center><img src=:/icons/icons/CT.png></center>");
    ui->t_label->setText("<center><img src=:/icons/icons/T.png></center>");
    /* fill our weapon_labels with 8 labels */
    for (int x = 0; x < 8; x++)
    {
        game.weapon_labels << new QLabel(this);
        game.weapon_labels.at(x)->setTextFormat(Qt::RichText);
    }
}

game_integration_window::~game_integration_window()
{
    server->close();
    delete ui;
}

void game_integration_window::write_console(QString color, QString line)
{
    ui->console->append("<font color=" + color + ">" + line + "</font>");
}

void game_integration_window::handle_data(QString data)
{
    /*
     * here we will handle our JSON data
     * first, split it so we only have the JSON data, no post headers
     * then we setup our json parser
     * we need to create a qvariantmap for each section we are subscribed to:
     * - map
     * - round
     * - player_id
     * - player_state
     * - match_stats
     */
    data = "{" + data.section('{', 1);
    game.json_doc = QJsonDocument::fromJson(data.toUtf8());
    if (!game.json_doc.isEmpty())
    {
        game.json_object = game.json_doc.object();
        game.main_map = game.json_object.toVariantMap();
        game.map_map = game.main_map["map"].toMap();
        game.player_map = game.main_map["player"].toMap();
        game.round_map = game.player_map["round"].toMap();
        game.weapon_map = game.player_map["weapons"].toMap();
        game.stats_map = game.player_map["match_stats"].toMap();
        game.ct_score_map = game.map_map["team_ct"].toMap();
        game.t_score_map = game.map_map["team_t"].toMap();
        game.weapon_1_map = game.weapon_map["weapon_0"].toMap();
        game.weapon_2_map = game.weapon_map["weapon_1"].toMap();
        game.weapon_3_map = game.weapon_map["weapon_2"].toMap();
        game.weapon_4_map = game.weapon_map["weapon_3"].toMap();
        game.weapon_5_map = game.weapon_map["weapon_4"].toMap();
        game.weapon_6_map = game.weapon_map["weapon_5"].toMap();
        game.weapon_7_map = game.weapon_map["weapon_6"].toMap();
        game.weapon_8_map = game.weapon_map["weapon_7"].toMap();
        game.weapon_9_map = game.weapon_map["weapon_8"].toMap();
        game.weapon_10_map = game.weapon_map["weapon_9"].toMap();
        display_data();
    }
}

void game_integration_window::display_data()
{
    /* in this function we dynamically display the user data on the GUI */
    if (game.current_user_id != game.player_map["steam_id"].toString()) /* if our name has not changed, don't update it */
    {
        write_console("red", "changing user ID");
        game.current_user_id = game.player_map["steam_id"].toString();
    }
    if (game.current_map != game.map_map["name"].toString()) /* if our map has not changed, don't update it */
    {
        game.current_map = game.map_map["name"].toString();
        ui->map_picture_label->setText("<img src=:/maps/maps/images/" + game.current_map + ".png /> <br />" + game.current_map);
    }
    if (game.current_team != game.player_map["team"].toString()) /* if our team has not changed, don't update */
    {
        game.current_team = game.player_map["team"].toString();
        if (game.current_team == "T")
            ui->player_team_label->setText("Terrorist");
        if (game.current_team == "CT")
            ui->player_team_label->setText("Counter Terrorist");
    }
    if (game.player_map["name"].toString().length() > 9) /* username too long */
    {
        ui->player_name_label->setText("<font size = 15>" + game.player_map["name"].toString().left(9) + "[...]</font>");
    } else
        ui->player_name_label->setText("<font size = 15>" + game.player_map["name"].toString() + "</font>");
    ui->player_score_label->setText("Score: " + game.stats_map["score"].toString());
    ui->ct_score_label->setText("<center>" + game.ct_score_map["score"].toString() + "</center>");
    ui->t_score_label->setText("<center>" + game.t_score_map["score"].toString() + "</center>");
    ui->round_number_label->setText("<center><font size = 10> Round <br />" + game.map_map["round"].toString() + "</font></center>");
    ui->kills_label->setText("Kills: " + game.stats_map["kills"].toString());
    ui->deaths_label->setText("Deaths: " + game.stats_map["deaths"].toString());
    /* weapons */
    /* TODO: find a better way? */
    if (game.weapon_1_map["name"].toString() != "")
        ui->weapon_1_label->setText("<img src=:/weapons/weapons/" + game.weapon_1_map["name"].toString() + ".png>");
    else
        ui->weapon_1_label->setText("");
    if (game.weapon_2_map["name"].toString() != "")
        ui->weapon_2_label->setText("<img src=:/weapons/weapons/" + game.weapon_2_map["name"].toString() + ".png><br />" + game.weapon_2_map["ammo_clip"].toString() + " " + game.weapon_2_map["ammo_reserve"].toString());
    else
        ui->weapon_2_label->setText("");
    if (game.weapon_3_map["name"].toString() != "")
        ui->weapon_3_label->setText("<img src=:/weapons/weapons/" + game.weapon_3_map["name"].toString() + ".png><br />" + game.weapon_3_map["ammo_clip"].toString() + " " + game.weapon_3_map["ammo_reserve"].toString());
    else
        ui->weapon_3_label->setText("");
    if (game.weapon_4_map["name"].toString() != "")
        ui->weapon_4_label->setText("<img src=:/weapons/weapons/" + game.weapon_4_map["name"].toString() + ".png><br />" + game.weapon_4_map["ammo_clip"].toString() + " " + game.weapon_4_map["ammo_reserve"].toString());
    else
        ui->weapon_4_label->setText("");
    if (game.weapon_5_map["name"].toString() != "")
        ui->weapon_5_label->setText("<img src=:/weapons/weapons/" + game.weapon_5_map["name"].toString() + ".png><br />" + game.weapon_5_map["ammo_clip"].toString() + " " + game.weapon_5_map["ammo_reserve"].toString());
    else
        ui->weapon_5_label->setText("");
    if (game.weapon_6_map["name"].toString() != "")
        ui->weapon_6_label->setText("<img src=:/weapons/weapons/" + game.weapon_6_map["name"].toString() + ".png><br />" + game.weapon_6_map["ammo_clip"].toString() + " " + game.weapon_6_map["ammo_reserve"].toString());
    else
        ui->weapon_6_label->setText("");
    if (game.weapon_7_map["name"].toString() != "")
        ui->weapon_7_label->setText("<img src=:/weapons/weapons/" + game.weapon_7_map["name"].toString() + ".png><br />" + game.weapon_7_map["ammo_clip"].toString() + " " + game.weapon_7_map["ammo_reserve"].toString());
    else
        ui->weapon_7_label->setText("");
    if (game.weapon_8_map["name"].toString() != "")
        ui->weapon_8_label->setText("<img src=:/weapons/weapons/" + game.weapon_8_map["name"].toString() + ".png><br />" + game.weapon_8_map["ammo_clip"].toString() + " " + game.weapon_8_map["ammo_reserve"].toString());
    else
        ui->weapon_8_label->setText("");
    if (game.weapon_9_map["name"].toString() != "")
        ui->weapon_9_label->setText("<img src=:/weapons/weapons/" + game.weapon_9_map["name"].toString() + ".png><br />" + game.weapon_9_map["ammo_clip"].toString() + " " + game.weapon_9_map["ammo_reserve"].toString());
    else
        ui->weapon_9_label->setText("");
    if (game.weapon_10_map["name"].toString() != "")
        ui->weapon_10_label->setText("<img src=:/weapons/weapons/" + game.weapon_10_map["name"].toString() + ".png><br />" + game.weapon_10_map["ammo_clip"].toString() + " " + game.weapon_10_map["ammo_reserve"].toString());
    else
        ui->weapon_10_label->setText("");


}

void game_integration_window::showEvent(QShowEvent *ev)
{
    emit window_loaded();
}

void game_integration_window::window_open()
{
    write_console("green", "Game Integration window open");
    ui->start_server_button->setEnabled(true);
    ui->stop_server_button->setEnabled(false);
}

void game_integration_window::new_connection()
{
    /* this is ugly code - it just works, I believe this is a HORRIBLE way to do it */
    /*
     * new connection found, things to do:
     * - create socket
     * - wait for it to be ready to read
     * - read all data
     * - send it to be handled elsewhere
     * - close our socket
     */
    QTcpSocket *socket; /* our socket instance */
    socket = server->nextPendingConnection();
    socket->waitForReadyRead(1000); /* one second of tolerence */
    handle_data(QString(socket->readAll()));
    socket->close();
    delete socket;
}

void game_integration_window::on_start_server_button_clicked()
{
    /* here we start our server */
    if (server->listen(QHostAddress::LocalHost, 3000))
    {
        /* start the server */
        write_console("blue", "Server started, waiting for data");
        ui->start_server_button->setEnabled(false);
        ui->stop_server_button->setEnabled(true);
    } else
    {
        /* server msut be running or some other error */
        write_console("red", "Server cannot be started");
    }
}

void game_integration_window::on_stop_server_button_clicked()
{
    if (server->isListening())
    {
        /* close our server */
        server->close();
        ui->start_server_button->setEnabled(true);
        ui->stop_server_button->setEnabled(false);
        write_console("blue", "Server stopped");
    }
}

void game_integration_window::on_close_window_button_clicked()
{
    server->close();
    this->close();
}
