#include "sort.h"
Sort::Sort()
{

}

QList<book> Sort::sortSK(QList<book> books, int flag)
{
    if(flag==1)
    {   qDebug()<<"2";
        //书号冒泡排序
        for(int i=0;i<books.length();i++)
            for(int j=0;j<books.length()-1;j++)
            {
                if(books.at(j).bookIndex>books.at(j+1).bookIndex)
                {
                    books.swap(j,j+1);
                }
            }
    }else
        if(flag==2)
        {
            //价格冒泡排序
            for(int i=0;i<books.length();i++)
                for(int j=0;j<books.length()-1;j++)
                {
                    if(books.at(j).price>books.at(j+1).price)
                    {
                        books.swap(j,j+1);
                    }
                }
        }else
            if(flag==3)
            {
                //入库日期冒泡排序
                for(int i=0;i<books.length();i++)
                    for(int j=0;j<books.length()-1;j++)
                    {
                        if(books.at(j).inSKDate>books.at(j+1).inSKDate)
                        {
                            books.swap(j,j+1);
                        }
                    }

            }
    return books;
}

QList<book> Sort::sortSCJ(QList<book> books, int flag)
{
    if(flag==1)
    {   qDebug()<<"2";
        //书号冒泡排序
        for(int i=0;i<books.length();i++)
            for(int j=0;j<books.length()-1;j++)
            {
                if(books.at(j).bookIndex>books.at(j+1).bookIndex)
                {
                    books.swap(j,j+1);
                }
            }
    }else
        if(flag==2)
        {
            //价格冒泡排序
            for(int i=0;i<books.length();i++)
                for(int j=0;j<books.length()-1;j++)
                {
                    if(books.at(j).price>books.at(j+1).price)
                    {
                        books.swap(j,j+1);
                    }
                }
        }else
            if(flag==3)
            {
                //入库日期冒泡排序
                for(int i=0;i<books.length();i++)
                    for(int j=0;j<books.length()-1;j++)
                    {
                        if(books.at(j).inSCJDate>books.at(j+1).inSCJDate)
                        {
                            books.swap(j,j+1);
                        }
                    }

            }
    return books;
}
