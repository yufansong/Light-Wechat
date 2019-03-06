/********************************************************************************
** Form generated from reading UI file 'mylogin.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYLOGIN_H
#define UI_MYLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyLogin
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QWidget *widget_2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *MyLogin)
    {
        if (MyLogin->objectName().isEmpty())
            MyLogin->setObjectName(QStringLiteral("MyLogin"));
        MyLogin->resize(500, 350);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MyLogin->sizePolicy().hasHeightForWidth());
        MyLogin->setSizePolicy(sizePolicy);
        MyLogin->setMinimumSize(QSize(500, 350));
        MyLogin->setMaximumSize(QSize(500, 350));
        verticalLayout = new QVBoxLayout(MyLogin);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(MyLogin);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(4);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(4, 4, 4, 4);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        lineEdit->raise();
        label->raise();
        label_2->raise();
        lineEdit_2->raise();

        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(MyLogin);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setEnabled(true);
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        formLayout = new QFormLayout(widget_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        lineEdit_3 = new QLineEdit(widget_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEnabled(true);
        lineEdit_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_3);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        lineEdit_4 = new QLineEdit(widget_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setEnabled(true);
        lineEdit_4->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_4->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_4);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(20, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setEnabled(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, pushButton_2);


        verticalLayout->addWidget(widget_2);


        retranslateUi(MyLogin);

        QMetaObject::connectSlotsByName(MyLogin);
    } // setupUi

    void retranslateUi(QDialog *MyLogin)
    {
        MyLogin->setWindowTitle(QApplication::translate("MyLogin", "Dialog", 0));
        label->setText(QApplication::translate("MyLogin", "ip\345\234\260\345\235\200", 0));
        lineEdit->setText(QApplication::translate("MyLogin", "10.60.102.252", 0));
        label_2->setText(QApplication::translate("MyLogin", "\347\253\257\345\217\243\345\217\267", 0));
        lineEdit_2->setText(QApplication::translate("MyLogin", "21100", 0));
        label_3->setText(QApplication::translate("MyLogin", "\347\224\250\346\210\267\345\220\215", 0));
        lineEdit_3->setText(QApplication::translate("MyLogin", "ZhangSan", 0));
        label_4->setText(QApplication::translate("MyLogin", "\345\257\206\347\240\201", 0));
        lineEdit_4->setText(QApplication::translate("MyLogin", "12345", 0));
        pushButton->setText(QApplication::translate("MyLogin", "\351\200\200\345\207\272", 0));
        pushButton_2->setText(QApplication::translate("MyLogin", "\347\231\273\351\231\206", 0));
    } // retranslateUi

};

namespace Ui {
    class MyLogin: public Ui_MyLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYLOGIN_H
