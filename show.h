#ifndef SHOW_H
#define SHOW_H


#include<QList>
#include<book.h>
#include<qtablewidget.h>
#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include<QHeaderView>
class Show
{
public:
    Show();
    //显示书库书籍的函数，需要当前ui的table 和 QList<book>容器 作为参数
    static void showSK(QTableWidget *tableWidget,QList<book> books);
    //显示收藏夹书籍的函数，需要当前ui的table 和 QList<book>容器 作为参数
    static void showSCJ(QTableWidget *tableWidget,QList<book> books);
    //显示购物车书籍的函数，需要当前ui的table 和 QList<book>容器 作为参数
    static void showGWC(QTableWidget *tableWidget,QList<book> books);

};

#endif // SHOW_H
