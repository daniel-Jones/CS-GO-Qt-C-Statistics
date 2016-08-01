#include "parse_file.h"

parse_file::parse_file()
{

}

QString parse_file::parse_user_data(QString option, QString split)
{
    /*
     * this function parses the userdata.dat file for info on the users steam account
     */
    QFile file("userdata.dat");
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if (line.contains(option))
              return line.split(split)[1].replace("\"", "").replace(",", "");
       }
       file.close();
    }
    return "null";
}

QString parse_file::parse_csgo_data(QString option)
{
    /*
     * this function parses csgodata.dat for stats
     */
    QFile file("csgodata.dat");
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if (line.contains(option))
          {
              line = in.readLine();
              return line.split(": ")[1];
          }
       }
       file.close();
    }
    return "null";
}

void parse_file::parse_users()
{
    /*
     * This function populates our dropdown menu with users
     *
     * example users.dat file:
     *
     * daniel_j=76561198055087665
     * ScruffyRules=76561198046533376
     *
     */
    usernames.clear();
    userids.clear();

        QFile inputFile("users.dat");
        if (inputFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if (line.contains("="))
                {
                    usernames.append(line.split("=")[0]);
                    userids.append(line.split("=")[1]);
                }
            }
            inputFile.close();
        } else
        {
            qDebug() << "No users loaded.";
        }
}

QStringList parse_file::get_usernames()
{
    return usernames;
}

QStringList parse_file::get_ids()
{
    return userids;
}

void parse_file::delete_user(QString user)
{
    /* copy pasta, make pretty */
    qDebug() << "deleting user" << user;
    QFile f("users.dat");
    if(f.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&f);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            if(line != user)
                s.append(line + "\n");
        }
        f.resize(0);
        t << s;
        f.close();
    }
}

void parse_file::add_user(QString user)
{
    qDebug() << "adding user" << user;
    QFile file("users.dat");
    if(!file.open(QIODevice::Append)) {
        qDebug() << "Cannot open file to save";

    } else
    {
        QTextStream stream(&file);
        stream << user;
        file.close();
    }
}
