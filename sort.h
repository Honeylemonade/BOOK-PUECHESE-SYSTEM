#ifndef SORT_H
#define SORT_H

#include<QList>
#include<book.h>
#include <QDebug>
class Sort
{
public:
    Sort();
    //按1书号，2价格，3入库日期进行排序
    static QList<book> sortSK(QList<book> books,int flag);
    //按1书号，2价格，3入库日期进行排序
    static QList<book> sortSCJ(QList<book> books,int flag);
};

#endif // SORT_H
