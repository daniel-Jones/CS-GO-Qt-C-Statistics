#include "stats_display_window.h"
#include "ui_stats_display_window.h"

stats_display_window::stats_display_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stats_display_window)
{
    ui->setupUi(this);
    connect(this, SIGNAL(window_loaded()), this, SLOT(test()), Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));
}

stats_display_window::~stats_display_window()
{
    delete ui;
}

void stats_display_window::showEvent(QShowEvent *ev)
{
    emit window_loaded();
}

void stats_display_window::test()
{
    QFile file("userdata.dat");
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if (line.contains("\"personaname\":"))
              user.username = line.split(": ")[1].replace("\"", "").replace(",", "");
          if (line.contains("\"realname\":"))
              user.realname = line.split(": ")[1].replace("\"", "").replace(",", "");
          if (line.contains("\"avatarfull\":"))
              user.avatar_url = line.split(": ")[1].replace("\"", "").replace(",", "");
       }
       file.close();
    }
    download.download_file(user.avatar_url, "avatar.jpg");
    ui->username_label->setText(user.username);
    if (user.realname == NULL)
        ui->realname_label->setText("Realname not set");
    else
        ui->realname_label->setText(user.realname);
    QPixmap image("avatar.jpg");
    ui->avatar_label->setPixmap(image);

}
