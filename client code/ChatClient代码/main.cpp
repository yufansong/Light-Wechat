#include<QApplication>
#include"chatdialog.h"
#include"filedisplay.h"
#include"mylogin.h"

#include<QFileDialog>

int main(int argc,char*argv[])
{
    QApplication a(argc,argv);


    // 翻转页面
    ChatDialog *dialog = new ChatDialog();
    dialog->show();

/*
    char strSend[976],strReceive[976];
    for(int i = 0;i<976;i++)
        strSend[i] = 0;
    QString name1 = "nothing";
    QString name2 = "nothing";

    Message message;
    int length;

    message.setFileMsg(name1,name2,976,strSend);
    message.getFileMsg(name1,name2,length,strReceive);

    qDebug()<<"length="<<length;

    for(int i = 0;i<976;i++)
    {
        if(strSend[i] != strReceive[i])
            qDebug()<<i<<"不相同"<<strSend[i]<<strReceive[i];
    }
    qDebug()<<"玩成";
    */

/*
    QFileDialog dialog;
    dialog.setWindowTitle("请选择发送的文件");
    dialog.exec();

    QStringList strList;
    strList = dialog.selectedFiles();

    if(strList.size())
    {
        //将打开文件的内容读入TextEdit中
        QFile file(strList[0]);
        file.open(QIODevice::ReadOnly|QIODevice::Text);

        //这里没有通过QTextStream方式读文件，因为这种方式导致中文乱码，因此这里直接用了file的readAll函数
        QByteArray array = file.readAll();
        QString str1(array);
        qDebug()<<"[content]";
        qDebug()<<str1;
        file.close();

        QString fileName = strList[0].section('/',-1,-1);
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QString fileMessage = str1;
        char *str = new char[fileMessage.size() + 1];
        QstringToChar(fileMessage,str);
        file.write(str,fileMessage.size());
        file.close();
    }

    qDebug()<<"完毕";
*/
    return a.exec();
}
