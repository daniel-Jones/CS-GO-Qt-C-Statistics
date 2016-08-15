#include "message_box.h"

message_box::message_box()
{

}

void message_box::info_box(QString message, QString title)
{
    QMessageBox msgbox;
    msgbox.setWindowTitle(title);
    msgbox.setText(message);
    msgbox.exec();
}

int message_box::confirm_box(QString warning, QString message, QString title)
{
    /* returns 1 for yes, 0 for no */
    QMessageBox msgbox;
    msgbox.setWindowTitle(title);
    msgbox.setText(warning);
    msgbox.setInformativeText(message);
    msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgbox.setDefaultButton(QMessageBox::No);
    return msgbox.exec();
}
