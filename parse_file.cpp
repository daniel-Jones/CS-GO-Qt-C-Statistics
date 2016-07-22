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
