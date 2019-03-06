/********************************************************************************
** Form generated from reading UI file 'newpassword.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPASSWORD_H
#define UI_NEWPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewPassword
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *NewPassword)
    {
        if (NewPassword->objectName().isEmpty())
            NewPassword->setObjectName(QStringLiteral("NewPassword"));
        NewPassword->resize(400, 150);
        NewPassword->setMinimumSize(QSize(400, 150));
        NewPassword->setMaximumSize(QSize(400, 150));
        verticalLayout = new QVBoxLayout(NewPassword);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        widget = new QWidget(NewPassword);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, pushButton_2);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(2, QFormLayout::FieldRole, pushButton);


        verticalLayout->addWidget(widget);


        retranslateUi(NewPassword);

        QMetaObject::connectSlotsByName(NewPassword);
    } // setupUi

    void retranslateUi(QDialog *NewPassword)
    {
        NewPassword->setWindowTitle(QApplication::translate("NewPassword", "Dialog", 0));
        label->setText(QApplication::translate("NewPassword", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0));
        label_2->setText(QApplication::translate("NewPassword", "\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201", 0));
        pushButton_2->setText(QApplication::translate("NewPassword", "\345\217\226\346\266\210", 0));
        pushButton->setText(QApplication::translate("NewPassword", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class NewPassword: public Ui_NewPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPASSWORD_H
