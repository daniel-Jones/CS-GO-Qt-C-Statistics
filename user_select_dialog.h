#ifndef USER_SELECT_DIALOG_H
#define USER_SELECT_DIALOG_H

#include <QMainWindow>
#include <QDebug>
#include "file_download.h"
#include "stats_display_window.h"

namespace Ui {
class user_select_dialog;
}

class user_select_dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit user_select_dialog(QWidget *parent = 0);
    ~user_select_dialog();

private slots:
    void on_select_account_button_clicked();

private:
    Ui::user_select_dialog *ui;
    file_download download;
    stats_display_window n_window;
    void download_info();
    void load_players();
};

#endif // USER_SELECT_DIALOG_H
