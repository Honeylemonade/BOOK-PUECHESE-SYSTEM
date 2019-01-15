#include "database.h"
#include<QDebug>
#include<QString>
#include<QVariantList>
DataBase::DataBase()
{

}

QList<book> DataBase::SKQuerey(QSqlDatabase db, QString sql)
{
    //创建SQL语句执行对象，并指定对哪个数据库进行sql操作
    QSqlQuery query(db);
    //定义接收书籍内容的容器
    QList<book> books;
    query.exec(sql);
    while(query.next())
    {
        book bk;

        bk.bookIndex=query.value(0).toInt();
        bk.bookName=query.value(1).toString();
        bk.athor=query.value(2).toString();
        bk.press=query.value(3).toString();
        bk.publishDate=query.value(4).toInt();
        bk.price=query.value(5).toInt();
        bk.inSKDate=query.value(6).toInt();
        books.append(bk);
    }
    return books ;
}

void DataBase::writeInSK(QSqlDatabase db,QList<book> books)
{
    //创建执行sql语句的对象
    QSqlQuery query(db);
    //清空书库信息的数据库
    query.exec("truncate table booklib");
    //定义存储数据的列表
    QVariantList bookIndex;
    QVariantList bookName;
    QVariantList athor;
    QVariantList press;
    QVariantList publishDate;
    QVariantList price;
    QVariantList inSKDate;
    for(int i=0;i<books.length();i++)
    {
        bookIndex<<books.at(i).bookIndex;
        bookName<< books.at(i).bookName;
        athor<<books.at(i).athor;
        press<<books.at(i).press;
        publishDate<<books.at(i).publishDate;
        price<<books.at(i).price;
        inSKDate<<books.at(i).inSKDate;
    }
    //进行预处理
    query.prepare("INSERT	INTO booklib VALUES(?,?,?,?,?,?,?)");
    query.addBindValue(bookIndex);
    query.addBindValue(bookName);
    query.addBindValue(athor);
    query.addBindValue(press);
    query.addBindValue(publishDate);
    query.addBindValue(price);
    query.addBindValue(inSKDate);
    //执行预处理命令
    query.execBatch();
}

void DataBase::InsertSK(QSqlDatabase db, QList<book> books)
{
    //创建执行sql语句的对象
    QSqlQuery query(db);
    //定义存储数据的列表
    QVariantList bookIndex;
    QVariantList bookName;
    QVariantList athor;
    QVariantList press;
    QVariantList publishDate;
    QVariantList price;
    QVariantList inSKDate;
    for(int i=0;i<books.length();i++)
    {
        bookIndex<<books.at(i).bookIndex;
        bookName<< books.at(i).bookName;
        athor<<books.at(i).athor;
        press<<books.at(i).press;
        publishDate<<books.at(i).publishDate;
        price<<books.at(i).price;
        inSKDate<<books.at(i).inSKDate;
    }
    //进行预处理
    query.prepare("INSERT	INTO booklib VALUES(?,?,?,?,?,?,?)");
    query.addBindValue(bookIndex);
    query.addBindValue(bookName);
    query.addBindValue(athor);
    query.addBindValue(press);
    query.addBindValue(publishDate);
    query.addBindValue(price);
    query.addBindValue(inSKDate);
    //执行预处理命令
    query.execBatch();
}

QList<book> DataBase::SCJQuerey(QSqlDatabase db, QString sql)
{
    //创建SQL语句执行对象，并指定对哪个数据库进行sql操作
    QSqlQuery query(db);
    //定义接收书籍内容的容器
    QList<book> books;
    query.exec(sql);
    while(query.next())
    {
        book bk;

        bk.bookIndex=query.value(0).toInt();
        bk.bookName=query.value(1).toString();
        bk.athor=query.value(2).toString();
        bk.press=query.value(3).toString();
        bk.publishDate=query.value(4).toInt();
        bk.price=query.value(5).toInt();
        bk.inSCJDate=query.value(6).toInt();
        books.append(bk);
    }
    return books ;
}

void DataBase::writeInSCJ(QSqlDatabase db, QList<book> books)
{
    //创建执行sql语句的对象
    QSqlQuery query(db);
    //清空书库信息的数据库
    query.exec("truncate table favor");
    //定义存储数据的列表
    QVariantList bookIndex;
    QVariantList bookName;
    QVariantList athor;
    QVariantList press;
    QVariantList publishDate;
    QVariantList price;
    QVariantList inSCJDate;
    for(int i=0;i<books.length();i++)
    {
        bookIndex<<books.at(i).bookIndex;
        bookName<< books.at(i).bookName;
        athor<<books.at(i).athor;
        press<<books.at(i).press;
        publishDate<<books.at(i).publishDate;
        price<<books.at(i).price;
        inSCJDate<<books.at(i).inSCJDate;
    }
    //进行预处理
    query.prepare("INSERT	INTO favor VALUES(?,?,?,?,?,?,?)");
    query.addBindValue(bookIndex);
    query.addBindValue(bookName);
    query.addBindValue(athor);
    query.addBindValue(press);
    query.addBindValue(publishDate);
    query.addBindValue(price);
    query.addBindValue(inSCJDate);
    //执行预处理命令
    query.execBatch();
}

void DataBase::InsertSCJ(QSqlDatabase db, QList<book> books)
{
    //创建执行sql语句的对象
    QSqlQuery query(db);
    //定义存储数据的列表
    QVariantList bookIndex;
    QVariantList bookName;
    QVariantList athor;
    QVariantList press;
    QVariantList publishDate;
    QVariantList price;
    QVariantList inSCJDate;
    for(int i=0;i<books.length();i++)
    {
        bookIndex<<books.at(i).bookIndex;
        bookName<< books.at(i).bookName;
        athor<<books.at(i).athor;
        press<<books.at(i).press;
        publishDate<<books.at(i).publishDate;
        price<<books.at(i).price;
        inSCJDate<<books.at(i).inSCJDate;
    }
    //进行预处理
    query.prepare("INSERT	INTO favor VALUES(?,?,?,?,?,?,?)");
    query.addBindValue(bookIndex);
    query.addBindValue(bookName);
    query.addBindValue(athor);
    query.addBindValue(press);
    query.addBindValue(publishDate);
    query.addBindValue(price);
    query.addBindValue(inSCJDate);
    //执行预处理命令
    query.execBatch();
}

QList<book> DataBase::GWCQuerey(QSqlDatabase db, QString sql)
{
    //创建SQL语句执行对象，并指定对哪个数据库进行sql操作
    QSqlQuery query(db);
    //定义接收书籍内容的容器
    QList<book> books;
    query.exec(sql);
    while(query.next())
    {
        book bk;

        bk.bookIndex=query.value(0).toInt();
        bk.bookName=query.value(1).toString();
        bk.athor=query.value(2).toString();
        bk.press=query.value(3).toString();
        bk.publishDate=query.value(4).toInt();
        bk.price=query.value(5).toInt();
        bk.inGWCDate=query.value(6).toInt();
        bk.num=query.value(7).toInt();
        books.append(bk);
    }
    return books ;
}

void DataBase::InsertGWC(QSqlDatabase db, QList<book> books)
{
    //创建执行sql语句的对象
    QSqlQuery query(db);
    //定义存储数据的列表
    QVariantList bookIndex;
    QVariantList bookName;
    QVariantList athor;
    QVariantList press;
    QVariantList publishDate;
    QVariantList price;
    QVariantList inGWCDate;
    QVariantList num;

    for(int i=0;i<books.length();i++)
    {
        bookIndex<<books.at(i).bookIndex;
        bookName<< books.at(i).bookName;
        athor<<books.at(i).athor;
        press<<books.at(i).press;
        publishDate<<books.at(i).publishDate;
        price<<books.at(i).price;
        inGWCDate<<books.at(i).inGWCDate;
        num<<books.at(i).num;
    }
    //进行预处理
    query.prepare("INSERT	INTO shoppingtrolley VALUES(?,?,?,?,?,?,?,?)");
    query.addBindValue(bookIndex);
    query.addBindValue(bookName);
    query.addBindValue(athor);
    query.addBindValue(press);
    query.addBindValue(publishDate);
    query.addBindValue(price);
    query.addBindValue(inGWCDate);
    query.addBindValue(num);
    //执行预处理命令
    query.execBatch();
}

