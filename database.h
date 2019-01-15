#ifndef DATABASE_H
#define DATABASE_H
#include<QSqlQuery>
#include<QSqlDatabase>
#include<book.h>
#include<qlist.h>
#include<QDebug>
#include<QString>
#include<QVariantList>
class DataBase
{
public:
    DataBase();
    //查询书库操作，并返回QList<book>容器
    static QList<book> SKQuerey(QSqlDatabase db,QString sql);
    //覆盖写入书库操作
    static void writeInSK(QSqlDatabase db,QList<book> books);
    //插入书库数据库操作
    static void InsertSK(QSqlDatabase db,QList<book> books);
    //查询收藏夹操作，并返回QList<book>容器
    static QList<book> SCJQuerey(QSqlDatabase db,QString sql);
    //覆盖写入收藏夹操作
    static void writeInSCJ(QSqlDatabase db,QList<book> books);
    //插入购物车数据库操作
    static void InsertSCJ(QSqlDatabase db,QList<book> books);
    //查询购物车操作，并返回QList<book>容器
    static QList<book> GWCQuerey(QSqlDatabase db,QString sql);
    //插入购物车数据库操作
    static void InsertGWC(QSqlDatabase db,QList<book> books);
};

#endif // DATABASE_H
