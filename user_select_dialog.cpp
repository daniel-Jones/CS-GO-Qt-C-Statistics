#include "user_select_dialog.h"
#include "ui_user_select_dialog.h"

user_select_dialog::user_select_dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user_select_dialog)
{
    ui->setupUi(this);
}

user_select_dialog::~user_select_dialog()
{
    delete ui;
}

void user_select_dialog::on_select_account_button_clicked()
{
    /*
     * we need to check if the user gave a steam id
     * if they did, proceed
     */
    if (ui->steam_url_text->text() == NULL)
    {
        qDebug() << "No profile provided.";
    } else {
        qDebug() << "Profile selected:" << ui->steam_url_text->text();
        ui->close_button->setEnabled(false);
        ui->select_account_button->setEnabled(false);
        ui->steam_url_text->setEnabled(false);
        ui->info_label->setText("Downloading data..");
        /* user data was a last second thought when designing this fucntion, clean it up one day, error checking etc */
        qDebug() << "Attempting to download user data";
        QString file_loc = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=FEBFDE46520663091143F867FEE39BFF&steamids=" + ui->steam_url_text->text();
        int success = download.download_file(file_loc, "userdata.dat");
        if (success == 1)
        {
            qDebug() << "Attempting to download cs:go data";
            file_loc = "http://api.steampowered.com/ISteamUserStats/GetUserStatsForGame/v0002/?appid=730&key=FEBFDE46520663091143F867FEE39BFF&steamid=" + ui->steam_url_text->text();
            success = download.download_file(file_loc, "csgodata.dat");
        }
        if (success == 1)
        {
            qDebug() << "Downloaded everything"; /* file could be ANYTHING or empty! */
            n_window.show();
            this->hide();
        }
        else
        {
            qDebug() << "Failed";
            ui->close_button->setEnabled(true);
            ui->select_account_button->setEnabled(true);
            ui->steam_url_text->setEnabled(true);
            ui->info_label->setText("Failed to download, try again.");
        }

    }
}
