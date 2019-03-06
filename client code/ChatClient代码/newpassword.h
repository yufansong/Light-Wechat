#ifndef NEWPASSWORD_H
#define NEWPASSWORD_H

#include <QDialog>
#include <QPushButton>
#include <QBitmap>
#include <QPainter>
#include "mylabel.h"

namespace Ui {
class NewPassword;
}

class NewPassword : public QDialog
{
    Q_OBJECT

public:
    explicit NewPassword(QWidget *parent = 0);
    ~NewPassword();

    QPushButton endPassword;
    QPushButton *pushButtonCancel;

    //新密码和上次的密码
    QString password;
    QString passwordPre;

    //设置上次的密码
    void setPasswordPre(QString lastPassword);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NewPassword *ui;
};

#endif // NEWPASSWORD_H
