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
};

#endif // PARSE_FILE_H
