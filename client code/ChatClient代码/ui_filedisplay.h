/********************************************************************************
** Form generated from reading UI file 'filedisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEDISPLAY_H
#define UI_FILEDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileDisplay
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QLabel *label_3;
    QListView *listView;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QListView *listView_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *FileDisplay)
    {
        if (FileDisplay->objectName().isEmpty())
            FileDisplay->setObjectName(QStringLiteral("FileDisplay"));
        FileDisplay->resize(1000, 800);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FileDisplay->sizePolicy().hasHeightForWidth());
        FileDisplay->setSizePolicy(sizePolicy);
        FileDisplay->setMinimumSize(QSize(1000, 800));
        QIcon icon;
        icon.addFile(QStringLiteral(":/myImage/images/open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FileDisplay->setWindowIcon(icon);
        horizontalLayout_2 = new QHBoxLayout(FileDisplay);
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(4, 4, 4, 4);
        widget = new QWidget(FileDisplay);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(61, 61, 61);"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/myImage/images/ui.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(60, 60));
        pushButton_2->setFlat(true);

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/myImage/images/password.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon2);
        pushButton_3->setIconSize(QSize(60, 60));
        pushButton_3->setFlat(true);

        verticalLayout->addWidget(pushButton_3);

        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/myImage/images/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon3);
        pushButton_6->setIconSize(QSize(60, 60));
        pushButton_6->setFlat(true);

        verticalLayout->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/myImage/images/close.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon4);
        pushButton_5->setIconSize(QSize(60, 60));
        pushButton_5->setFlat(true);

        verticalLayout->addWidget(pushButton_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(widget);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_4 = new QWidget(FileDisplay);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayout_5 = new QVBoxLayout(widget_4);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_2->setFrameShape(QFrame::NoFrame);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_2);

        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_3);


        verticalLayout_4->addWidget(widget_4);

        listView = new QListView(FileDisplay);
        listView->setObjectName(QStringLiteral("listView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy1);
        listView->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        listView->setFrameShape(QFrame::NoFrame);
        listView->setFrameShadow(QFrame::Plain);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setSelectionBehavior(QAbstractItemView::SelectItems);
        listView->setProperty("isWrapping", QVariant(false));
        listView->setResizeMode(QListView::Fixed);
        listView->setGridSize(QSize(0, 0));
        listView->setViewMode(QListView::ListMode);
        listView->setModelColumn(0);
        listView->setBatchSize(100);

        verticalLayout_4->addWidget(listView);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(FileDisplay);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 248);\n"
"font: 75 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        listView_2 = new QListView(FileDisplay);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        sizePolicy1.setHeightForWidth(listView_2->sizePolicy().hasHeightForWidth());
        listView_2->setSizePolicy(sizePolicy1);
        listView_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        listView_2->setFrameShape(QFrame::NoFrame);
        listView_2->setFrameShadow(QFrame::Plain);
        listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView_2->setSelectionBehavior(QAbstractItemView::SelectItems);
        listView_2->setProperty("isWrapping", QVariant(false));
        listView_2->setResizeMode(QListView::Fixed);
        listView_2->setGridSize(QSize(0, 0));
        listView_2->setViewMode(QListView::ListMode);
        listView_2->setModelColumn(0);
        listView_2->setBatchSize(100);

        verticalLayout_3->addWidget(listView_2);

        widget_2 = new QWidget(FileDisplay);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 3);
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(4, 4, 4, 4);
        pushButton_4 = new QPushButton(widget_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy2);
        pushButton_4->setStyleSheet(QStringLiteral(""));
        pushButton_4->setIcon(icon);
        pushButton_4->setFlat(true);

        horizontalLayout_3->addWidget(pushButton_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(widget_3);

        textEdit = new QTextEdit(widget_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        textEdit->setFrameShape(QFrame::NoFrame);

        verticalLayout_2->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 5);
        verticalLayout_2->setStretch(2, 1);

        verticalLayout_3->addWidget(widget_2);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 10);
        verticalLayout_3->setStretch(2, 4);

        horizontalLayout_2->addLayout(verticalLayout_3);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 6);

        retranslateUi(FileDisplay);

        QMetaObject::connectSlotsByName(FileDisplay);
    } // setupUi

    void retranslateUi(QDialog *FileDisplay)
    {
        FileDisplay->setWindowTitle(QApplication::translate("FileDisplay", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_6->setText(QString());
        pushButton_5->setText(QString());
        label_2->setText(QApplication::translate("FileDisplay", "TextLabel", 0));
        label_3->setText(QApplication::translate("FileDisplay", "TextLabel", 0));
        label->setText(QString());
        pushButton_4->setText(QString());
        pushButton->setText(QApplication::translate("FileDisplay", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class FileDisplay: public Ui_FileDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEDISPLAY_H
