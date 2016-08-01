#ifndef PARSE_FILE_H
#define PARSE_FILE_H
#include <QFile>
#include <QDebug>
#include <QTextStream>

class parse_file
{
public:
    parse_file();
    QString parse_user_data(QString option, QString split);
    QString parse_csgo_data(QString option);
    void parse_users(); /* parse file */
    QStringList get_usernames(); /* returns pre parsed data */
    QStringList get_ids(); /* returns pre parsed data */
    QStringList usernames;
    QStringList userids;
    void delete_user(QString user);
    void add_user(QString user);
};

#endif // PARSE_FILE_H
