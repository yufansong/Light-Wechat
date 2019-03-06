#include "newpassword.h"
#include "ui_newpassword.h"

NewPassword::NewPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPassword)
{
    ui->setupUi(this);

    password = "";
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    pushButtonCancel = ui->pushButton_2;

    //设置圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);

    ui->pushButton->  setStyleSheet(
                //正常状态样式
                "QPushButton{"
                "background-color:rgba(216,216,216,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:4px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(190,190,190,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(255,255,255,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                );

    ui->pushButton_2->  setStyleSheet(
                //正常状态样式
                "QPushButton{"
                "background-color:rgba(216,216,216,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:4px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标悬浮样式
                "QPushButton:hover{"
                "background-color:rgba(190,190,190,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(255,255,255,100);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:6px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,200);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色
                "padding:6px;"                          //填衬
                "font: 75 12pt 微软雅黑;"
                "}"
                );
}

NewPassword::~NewPassword()
{
    delete ui;
}

void NewPassword::on_pushButton_clicked()
{
    QString text1 = ui->lineEdit->text();
    QString text2 = ui->lineEdit_2->text();

    if(text1.isEmpty())
    {
        //提示密码非空
        MyLabel *mylabel = new MyLabel(this,"密码不能为空");
        mylabel->toastr();
        return;
    }

    if(text1 != text2)
    {
        //提示两次输入密码不一致
        MyLabel *mylabel = new MyLabel(this,"两次输入的密码不一致");
        mylabel->toastr();
        return;
    }

    if(text1 == passwordPre)
    {
        //提示不与之前密码相同
        MyLabel *mylabel = new MyLabel(this,"与原密码相同");
        mylabel->toastr();
        return;
    }

    password = text1;

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    endPassword.clicked();
}

void NewPassword::on_pushButton_2_clicked()
{
    password = "";

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    endPassword.clicked();
}

void NewPassword::setPasswordPre(QString lastPassword)
{
    passwordPre = lastPassword;
    password = "";
}
