#include "addonebookdialog.h"
#include "ui_addonebookdialog.h"

AddOneBookDialog::AddOneBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOneBookDialog)
{
    ui->setupUi(this);

    db2.setHostName("127.0.0.1");
    db2.setPort(3306);             //连接数据库端口号，与设置一致
    db2.setDatabaseName("test");   //连接数据库名，与设置一致
    db2.setUserName("root");       //数据库用户名，与设置一致
    db2.setPassword("159852");     //数据库密码，与设置一致
    db2.open();
    if(!db2.open())
    {
        qDebug()<<"失败";
        return ;
    }else {
        qDebug()<<"成功";
    }
}

AddOneBookDialog::~AddOneBookDialog()
{
    delete ui;
}


void AddOneBookDialog::on_btn_cancel_clicked()
{
    this->close();
}

void AddOneBookDialog::on_btn_ok_clicked()
{
    //定义一个book对象
    book abook;
    abook.bookIndex=this->ui->bookIndex->text().toInt();
    abook.bookName=this->ui->bookName->text();
    abook.athor=this->ui->athor->text();
    abook.press=this->ui->press->text();
    abook.publishDate=this->ui->publishDate->text().toInt();
    abook.price=this->ui->price->text().toInt();
    abook.inSKDate=this->ui->inSKDate->text().toInt();
    //创建执行sql语句的对象
    QSqlQuery query(db2);
    QString sql = QString("select * from booklib WHERE bookIndex='%1'").arg(abook.bookIndex);
    //执行sql语句
    query.exec(sql);
    //根据查询结果是否为空做出相应操作
    if(query.size())
    {
        qDebug()<<query.size();
        QMessageBox msgBox;
        msgBox.setText("此书已存在");
        msgBox.setInformativeText("您输入的书号可能有误");
        msgBox.setStandardButtons(QMessageBox::Ok );
        msgBox.exec();
    }else{
        qDebug()<<query.size();
        //定义存储数据的列表
        QVariantList bookIndex;
        QVariantList bookName;
        QVariantList athor;
        QVariantList press;
        QVariantList publishDate;
        QVariantList price;
        QVariantList inSKDate;

        bookIndex<<abook.bookIndex;
        bookName<< abook.bookName;
        athor<<abook.athor;
        press<<abook.press;
        publishDate<<abook.publishDate;
        price<<abook.price;
        inSKDate<<abook.inSKDate;

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
        this->close();
    }















}
