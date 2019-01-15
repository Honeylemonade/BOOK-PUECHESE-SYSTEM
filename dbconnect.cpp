#include "dbconnect.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariantList>
DBConnect::DBConnect()
{

}

void DBConnect::connect()
{
    //创建数据库对象 db 并连接
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("test");      //连接数据库名，与设置一致
    db.setUserName("root");      //数据库用户名，与设置一致
    db.setPassword("159852");    //数据库密码，与设置一致
    db.open();
    if(!db.open())
     {
         qDebug()<<"失败";
         return ;
     }else {
        qDebug()<<"成功";
}
     //创建SQL语句执行对象，并指定对哪个数据库进行sql操作
     QSqlQuery query(db);

}
