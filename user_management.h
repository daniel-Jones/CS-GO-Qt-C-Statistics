#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <QWidget>
#include <QDebug>
#include "parse_file.h"

namespace Ui {
class user_management;
}

class user_management : public QWidget
{
    Q_OBJECT

public:
    explicit user_management(QWidget *parent = 0);
    ~user_management();

private slots:
    void on_refresh_users_button_clicked();

    void on_delete_user_button_clicked();

    void on_add_user_button_clicked();

private:
    Ui::user_management *ui;
    parse_file parse;
    QStringList usernames;
    QStringList userids;
    void load_players();
};

#endif // USER_MANAGEMENT_H
