#include "user_select_dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    user_select_dialog w;
    w.show();

    return a.exec();
}
