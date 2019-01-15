#include "show.h"
Show::Show()
{

}

void Show::showSK(QTableWidget *tableWidget, QList<book> books)
{
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置列数
    tableWidget->setColumnCount(7);
    //设置行数
    tableWidget->setRowCount(books.length());
    //设置表头
    tableWidget->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "作者"<< "出版社"<<"出版日期"<<"价格"<<"入库日期");
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   // 单个选中
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    //设置item内容
    for(int i=0;i<books.length();i++)
    {
        //要将int强制转换为QString
        tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(books.at(i).bookIndex)));
        tableWidget->setItem(i,1,new QTableWidgetItem(books.at(i).bookName));
        tableWidget->setItem(i,2,new QTableWidgetItem(books.at(i).athor));
        tableWidget->setItem(i,3,new QTableWidgetItem(books.at(i).press));
        tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(books.at(i).publishDate)));
        tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(books.at(i).price)));
        tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(books.at(i).inSKDate)));
    }
}

void Show::showSCJ(QTableWidget *tableWidget, QList<book> books)
{
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置列数
    tableWidget->setColumnCount(7);
    //设置行数
    tableWidget->setRowCount(books.length());
    //设置表头
    tableWidget->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "作者"<< "出版社"<<"出版日期"<<"价格"<<"加入收藏夹日期");
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   // 单个选中
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    //设置item内容
    for(int i=0;i<books.length();i++)
    {
        //要将int强制转换为QString
        tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(books.at(i).bookIndex)));
        tableWidget->setItem(i,1,new QTableWidgetItem(books.at(i).bookName));
        tableWidget->setItem(i,2,new QTableWidgetItem(books.at(i).athor));
        tableWidget->setItem(i,3,new QTableWidgetItem(books.at(i).press));
        tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(books.at(i).publishDate)));
        tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(books.at(i).price)));
        tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(books.at(i).inSCJDate)));
    }
}

void Show::showGWC(QTableWidget *tableWidget, QList<book> books)
{
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置列数
    tableWidget->setColumnCount(8);
    //设置行数
    tableWidget->setRowCount(books.length());
    //设置表头
    tableWidget->setHorizontalHeaderLabels(QStringList() << "书号" << "书名" << "作者"<< "出版社"<<"出版日期"<<"价格"<<"入购物车日期"<<"数量");
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   // 单个选中
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    //设置item内容
    for(int i=0;i<books.length();i++)
    {
        //要将int强制转换为QString
        tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(books.at(i).bookIndex)));
        tableWidget->setItem(i,1,new QTableWidgetItem(books.at(i).bookName));
        tableWidget->setItem(i,2,new QTableWidgetItem(books.at(i).athor));
        tableWidget->setItem(i,3,new QTableWidgetItem(books.at(i).press));
        tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(books.at(i).publishDate)));
        tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(books.at(i).price)));
        tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(books.at(i).inGWCDate)));
        tableWidget->setItem(i,7,new QTableWidgetItem(QString::number(books.at(i).num)));
    }
}



