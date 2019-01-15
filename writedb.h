#ifndef WRITEDB_H
#define WRITEDB_H
//用于将qlist数据写入数据库
#include<QList>
#include<book.h>
class WriteDB
{
public:
    WriteDB();
    static void writeInSK(QList<book> books);
};

#endif // WRITEDB_H
