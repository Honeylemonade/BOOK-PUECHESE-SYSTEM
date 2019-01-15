#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSqlQuery>
#include<book.h>
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariantList>
#include<book.h>
#include<database.h>
#include<show.h>
#include<sort.h>
#include<addonebookdialog.h>
#include<QString>
#include<QMessageBox>
#include<QDateTime>
#include<QLineEdit>
#include<QInputDialog>
#include<form.h>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    Ui::Widget *ui;
    //设置数据库连接节点db
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    //定义书库里的书
    QList<book> SKbooks;
    //定义收藏夹里的书
    QList<book> SCJbooks;
    //定义购物车里的书
    QList<book> GWCbooks;

private slots:
    //点击进行书库排序
    void on_SKsort_clicked();
    //向书库中添加一本书
    void on_SKAddOneBook_clicked();
    //批量向书库中导入书籍信息
    void on_SKAddBooks_clicked();
    //按书号删除书库中书籍
    void on_SKdeleteIndex_clicked();
    //按入库日期批量删除书库中书籍
    void on_SKdeleteIndex_2_clicked();
    //根据书号查找书库中书籍，并显示其信息
    void on_SKSearch_clicked();
    //添加至收藏夹
    void on_SKAddToSCJ_clicked();
    //从书库添加至购物车
    void on_SKAddToGWC_clicked();
    //为收藏夹的书籍进行排序
    void on_SCJsort_clicked();
    //根据书号查找收藏夹中的书籍，并输出信息
    void on_SCJSearch_clicked();
    //选中后，从收藏夹中移出该书籍
    void on_DFromSCJ_clicked();
    //选中后，从收藏夹添加到购物车
    void on_SCJAddToGWC_clicked();
    //根据书号搜索购物车中书籍，并输出信息
    void on_GWCSearch_clicked();
    //选中后，从购物车中移出
    void on_DFromGWC_clicked();
    //从购物车移至收藏夹
    void on_GWCROMtoSCJ_clicked();
    //判断库中是否已存在改书，若存在则num++
    static bool isExist(QList<book> ku,int bookIndex);
    //计算购物车中所有物品的价格
    int getPrice();
    //增加购书数量
    void on_GWCInNum_btn_clicked();
    //减少购书数量
    void on_GWCDeNum_btn_clicked();
    void on_pushButton_clicked();
};

#endif // WIDGET_H
