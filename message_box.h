#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H
#include <QMessageBox>

class message_box
{
public:
    message_box();
    void info_box(QString message, QString title);
    int confirm_box(QString warning, QString message, QString title);
};

#endif // MESSAGE_BOX_H
