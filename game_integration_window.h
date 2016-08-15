#ifndef GAME_INTEGRATION_WINDOW_H
#define GAME_INTEGRATION_WINDOW_H

#include <QWidget>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class game_integration_window;
}

class game_integration_window : public QWidget
{
    Q_OBJECT

public:
    explicit game_integration_window(QWidget *parent = 0);
    ~game_integration_window();

private:
    Ui::game_integration_window *ui;
    void write_console(QString color, QString line);
    void handle_data(QString data);
    void display_data();
    QTcpServer *server; /* our server instance */
    struct game_data {
        QJsonDocument json_doc;
        QJsonObject json_object;
        QVariantMap main_map;
         QVariantMap map_map;
        QVariantMap player_map;
        QVariantMap round_map;
        QVariantMap weapon_map;
        QVariantMap stats_map;
        QVariantMap ct_score_map;
        QVariantMap t_score_map;
        QString current_user_id;
        QString current_map;
        QString current_team;
    } game;

protected:
      void showEvent(QShowEvent *ev);

signals:
      void window_loaded();

private slots:
      void window_open();
      void new_connection();
      void on_start_server_button_clicked();
      void on_stop_server_button_clicked();
      void on_close_window_button_clicked();
};

#endif // GAME_INTEGRATION_WINDOW_H
