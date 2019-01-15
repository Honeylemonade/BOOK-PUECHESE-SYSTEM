#ifndef BOOK_H
#define BOOK_H
#include<QString>
//书的实体类
class book
{
public:
    book()
    {

    }
    //定义了一系列书的属性
    int bookIndex;
    QString bookName;
    QString athor;
    QString press;
    int publishDate;
    int price;
    int inSKDate;
    int inSCJDate;
    int inGWCDate;
    int num=1;

};

#endif // BOOK_H
