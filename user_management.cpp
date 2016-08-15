#include "user_management.h"
#include "ui_user_management.h"

user_management::user_management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_management)
{
    ui->setupUi(this);
    load_players();
}

user_management::~user_management()
{
    delete ui;
}

void user_management::load_players()
{
    ui->user_dropdown->clear();
    usernames.clear();
    userids.clear();
    parse.parse_users();
    usernames = parse.get_usernames();
    userids = parse.get_ids();
    for (int x = 0; x < usernames.length(); x++)
    {
        ui->user_dropdown->addItem(usernames.at(x));
    }
}

void user_management::on_refresh_users_button_clicked()
{
    load_players();
}

void user_management::on_delete_user_button_clicked()
{
    int opt = msgbox.confirm_box("You are about to delete a user", "Are you sure?", "Warning");
    switch (opt) {
       case QMessageBox::Yes: {
            QString to_remove = ui->user_dropdown->currentText() + "=" + userids.at(ui->user_dropdown->currentIndex());
            parse.delete_user(to_remove);
            load_players();
            break;
    }
       case QMessageBox::No:
           break;
       default:
           break;
     }
}

void user_management::on_add_user_button_clicked()
{
    if (ui->username_text->text() != "" && ui->user_id_text->text() != "")
    {
        QString user = ui->username_text->text() + "=" + ui->user_id_text->text();
        parse.add_user(user);
    }
}
