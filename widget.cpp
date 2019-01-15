#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建数据库对象 db 并连接
    db.setHostName("127.0.0.1");
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("test");      //连接数据库名，与设置一致
    db.setUserName("root");      //数据库用户名，与设置一致
    db.setPassword("159852");    //数据库密码，与设置一致
    db.open();
    if(!db.open())
    {
        qDebug()<<"失败";
        return ;
    }else {
        qDebug()<<"成功";
    }
    //获取书库书籍数据
    this->SKbooks=DataBase::SKQuerey(db,"select * from booklib");
    //显示书库书籍信息
    Show::showSK(this->ui->SKtableWidget,SKbooks);
    //获取收藏夹书籍数据
    this->SCJbooks=DataBase::SCJQuerey(db,"select * from favor");
    //显示收藏夹书籍信息
    Show::showSCJ(this->ui->SCJtableWidget,SCJbooks);
    //获取购物车书籍数据
    this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
    //显示购物车书籍信息
    Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
    this->ui->priceLB->setNum(getPrice());

}

Widget::~Widget()
{
    delete ui;
}


//
void Widget::on_SKsort_clicked()
{
    //获取当前数据库数据，更新虚拟库
    this->SKbooks=DataBase::SKQuerey(db,"select * from booklib");
    //排序
    this->SKbooks=Sort::sortSK(SKbooks,this->ui->SKcomboBox->currentIndex());
    qDebug()<<this->ui->SKcomboBox->currentIndex();
    //写入数据库
    DataBase::writeInSK(db,this->SKbooks);
    //显示
    Show::showSK(this->ui->SKtableWidget,SKbooks);
}

//书库界面点击添加书籍按钮
void Widget::on_SKAddOneBook_clicked()
{

    AddOneBookDialog a;
    a.exec();
    //获取当前数据库数据，更新虚拟库
    this->SKbooks=DataBase::SKQuerey(db,"select * from booklib");
    //显示
    Show::showSK(this->ui->SKtableWidget,SKbooks);
}

void Widget::on_SKAddBooks_clicked()
{
    //获取当前日期
    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString("yyyyMMdd");
    qDebug() << localTime;
    //booklines按行存储了信息
    QList<QString> bookLines;
    QFile file("books.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"失败";
    } else {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            //按行读取
            QString line=in.readLine();

            bookLines.append(line);
        }
        file.close();
    }
    //现已获取了行list数据,接下来将其分解,并加入Books中
    QList<book> Books;
    book singleBook;
    for(int i=0;i<bookLines.length();i++)
    {
        QString line=bookLines.at(i);
        //以空格为分割符
        QStringList infos=line.split(" ");
        singleBook.bookIndex=infos.at(0).toInt();
        singleBook.bookName=infos.at(1);
        singleBook.athor=infos.at(2);
        singleBook.press=infos.at(3);
        singleBook.publishDate=infos.at(4).toInt();
        singleBook.price=infos.at(5).toInt();
        singleBook.inSKDate=localTime.toInt();
        Books.append(singleBook);
    }
    //插入到数据库中
    DataBase::InsertSK(db,Books);
    //获取当前数据库数据，更新虚拟库
    this->SKbooks=DataBase::SKQuerey(db,"select * from booklib");
    //显示
    Show::showSK(this->ui->SKtableWidget,SKbooks);
}
//指定书号删除
void Widget::on_SKdeleteIndex_clicked()
{//获取文本框中的值
    int flag=this->ui->SKDI_ln->text().toInt();
    //创建执行sql语句的对象
    QSqlQuery query(db);
    QString deletesql = QString("DELETE FROM booklib WHERE bookIndex='%1'").arg(flag);
    //执行sql语句
    query.exec(deletesql);
    //同步到虚拟库
    this->SKbooks=DataBase::SKQuerey(db,"select * from booklib");
    //显示
    Show::showSK(this->ui->SKtableWidget,SKbooks);
}


//指定日期删除
void Widget::on_SKdeleteIndex_2_clicked()
{
    //获取文本框中的值
    int flag=this->ui->SKDD_ln->text().toInt();
    //创建执行sql语句的对象
    QSqlQuery query(db);
    QString deletesql = QString("DELETE FROM booklib WHERE inSKDate='%1'").arg(flag);
    //执行sql语句
    query.exec(deletesql);
    //同步到虚拟库
    this->SKbooks=DataBase::SKQuerey(db,"select * from booklib");
    //显示
    Show::showSK(this->ui->SKtableWidget,SKbooks);
}
//根据图书号查找图书，并显示图书信息
void Widget::on_SKSearch_clicked()
{ //获取书号
    int flag=this->ui->SKlineEdit->text().toInt();
    book tempbook;
    //初始默认设置index为0作为标记
    tempbook.bookIndex=0;
    //遍历书库
    for(int i=0;i<SKbooks.length();i++)
    {
        if(SKbooks.at(i).bookIndex==flag)
        {
            tempbook=SKbooks.at(i);
        }
    }
    //此时以遍历结束，
    if(tempbook.bookIndex==0)
    {
        QMessageBox msgBox;
        msgBox.setText("查无此书");
        msgBox.setInformativeText("您输入的书号可能有误");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QString info="书号:"+QString::number(tempbook.bookIndex)+'\n'
                +"书名:"+tempbook.bookName+'\n'
                +"作者:"+tempbook.athor+'\n'
                +"出版社:"+tempbook.press+'\n'
                +"出版日期:"+QString::number(tempbook.publishDate)+'\n'
                +"价格:"+QString::number(tempbook.price)+'\n'
                +"入库日期:"+QString::number(tempbook.inSKDate);
        QMessageBox msgBox;
        msgBox.setText("查询成功");
        msgBox.setInformativeText(info);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        //运行窗口
        msgBox.exec();

    }
}

//选中行后加入收藏夹
void Widget::on_SKAddToSCJ_clicked()
{
    //获取选中行
    int flag=this->ui->SKtableWidget->currentRow();
    qDebug()<<flag;
    //判断是否有被选中行
    if(flag!=-1)
    {
        //判断否库中已存在该书
        if(!isExist(SCJbooks,SKbooks.at(flag).bookIndex))
        {
            QList<book> books;
            //获取收藏夹图书对象，并加入到books中
            bool isOk;
            QString text = QInputDialog::getText(this,
                                                 "输入",
                                                 "请手动输入加入收藏夹的时间",
                                                 QLineEdit::Normal,
                                                 "请输入标准格式",
                                                 &isOk);
            if(isOk)
            {
                book temp;
                temp=SKbooks.at(flag);
                temp.inSCJDate=text.toInt();
                books.append(temp);
                //插入到收藏夹
                DataBase::InsertSCJ(db,books);
                //获取收藏夹书籍数据
                this->SCJbooks=DataBase::SCJQuerey(db,"select * from favor");
                //显示收藏夹书籍信息
                Show::showSCJ(this->ui->SCJtableWidget,SCJbooks);
            }
        }
    }
}

void Widget::on_SCJsort_clicked()
{
    //获取当前数据库数据，更新虚拟库
    this->SCJbooks=DataBase::SCJQuerey(db,"select * from favor");
    //排序
    this->SCJbooks=Sort::sortSCJ(SCJbooks,this->ui->SCJcomboBox->currentIndex());
    qDebug()<<this->ui->SCJcomboBox->currentIndex();
    //写入数据库
    DataBase::writeInSCJ(db,this->SCJbooks);
    //显示
    Show::showSCJ(this->ui->SCJtableWidget,SCJbooks);
}
//根据书号查收藏夹里的书
void Widget::on_SCJSearch_clicked()
{
    //获取书号
    int flag=this->ui->SCJlineEdit->text().toInt();
    //判断是否有被选中行
    if(flag!=-1)
    {
        book tempbook;
        //初始默认设置index为0作为标记
        tempbook.bookIndex=0;
        //遍历书库
        for(int i=0;i<SCJbooks.length();i++)
        {
            if(SCJbooks.at(i).bookIndex==flag)
            {
                tempbook=SCJbooks.at(i);
            }
        }
        //此时以遍历结束，
        if(tempbook.bookIndex==0)
        {
            QMessageBox msgBox;
            msgBox.setText("查无此书");
            msgBox.setInformativeText("您输入的书号可能有误");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        else
        {
            QString info="书号:"+QString::number(tempbook.bookIndex)+'\n'
                    +"书名:"+tempbook.bookName+'\n'
                    +"作者:"+tempbook.athor+'\n'
                    +"出版社:"+tempbook.press+'\n'
                    +"出版日期:"+QString::number(tempbook.publishDate)+'\n'
                    +"价格:"+QString::number(tempbook.price)+'\n'
                    +"入收藏夹日期:"+QString::number(tempbook.inSCJDate);
            QMessageBox msgBox;
            msgBox.setText("查询成功");
            msgBox.setInformativeText(info);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            //运行窗口
            msgBox.exec();

        }
    }

}

void Widget::on_DFromSCJ_clicked()
{
    int flag=this->ui->SCJtableWidget->currentRow();
    qDebug()<<flag;
    //判断是否有被选中行
    if(flag!=-1)
    {
        int index=SCJbooks.at(flag).bookIndex;
        QSqlQuery query(db);
        QString deletesql = QString("DELETE FROM favor WHERE bookIndex='%1'").arg(index);
        //执行sql语句
        query.exec(deletesql);
        //同步到虚拟库
        this->SCJbooks=DataBase::SCJQuerey(db,"select * from favor");
        //显示
        Show::showSCJ(this->ui->SCJtableWidget,SCJbooks);
    }
}

void Widget::on_SCJAddToGWC_clicked()
{   //获取选中行
    int flag=this->ui->SCJtableWidget->currentRow();
    qDebug()<<flag;
    //判断是否有被选中行
    if(flag!=-1)
    {
        if(!isExist(GWCbooks,SCJbooks.at(flag).bookIndex))
        {
            QList<book> books;
            //获取当前时间
            QDateTime local(QDateTime::currentDateTime());
            QString localTime = local.toString("yyyyMMdd");
            book temp;
            temp=SCJbooks.at(flag);
            temp.inGWCDate=localTime.toInt();
            //获取收藏夹图书对象，并加入到books中
            books.append(temp);
            //插入到购物车
            DataBase::InsertGWC(db,books);
            //获取购物车书籍数据
            this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
            //显示购物车书籍信息
            Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
        }else{
            //存在时，修改数据库，并同步到虚拟库num++
            QSqlQuery query(db);
            QString sql = QString("UPDATE shoppingtrolley SET num=num+1 WHERE bookIndex='%1'").arg(SCJbooks.at(flag).bookIndex);
            //执行sql语句
            query.exec(sql);
            //同步到虚拟库
            this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
            //显示购物车书籍信息
            Show::showGWC(this->ui->GWCtableWidget,GWCbooks);



        }
    }
    this->ui->priceLB->setNum(getPrice());
}

void Widget::on_GWCSearch_clicked()
{
    //获取书号
    int flag=this->ui->GWClineEdit->text().toInt();
    book tempbook;
    //初始默认设置index为0作为标记
    tempbook.bookIndex=0;
    //遍历书库
    for(int i=0;i<GWCbooks.length();i++)
    {
        if(GWCbooks.at(i).bookIndex==flag)
        {
            tempbook=GWCbooks.at(i);
        }
    }
    //此时以遍历结束，
    if(tempbook.bookIndex==0)
    {
        QMessageBox msgBox;
        msgBox.setText("查无此书");
        msgBox.setInformativeText("您输入的书号可能有误");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QString info="书号:"+QString::number(tempbook.bookIndex)+'\n'
                +"书名:"+tempbook.bookName+'\n'
                +"作者:"+tempbook.athor+'\n'
                +"出版社:"+tempbook.press+'\n'
                +"出版日期:"+QString::number(tempbook.publishDate)+'\n'
                +"价格:"+QString::number(tempbook.price)+'\n'
                +"入购物车日期:"+QString::number(tempbook.inGWCDate)+'\n'
                +"数量:"+QString::number(tempbook.num);
        QMessageBox msgBox;
        msgBox.setText("查询成功");
        msgBox.setInformativeText(info);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        //运行窗口
        msgBox.exec();

    }
}

void Widget::on_DFromGWC_clicked()
{
    int flag=this->ui->GWCtableWidget->currentRow();
    qDebug()<<flag;
    //判断是否有被选中行
    if(flag!=-1)
    {
        int index=GWCbooks.at(flag).bookIndex;
        QSqlQuery query(db);
        QString deletesql = QString("DELETE FROM shoppingtrolley WHERE bookIndex='%1'").arg(index);
        //执行sql语句
        query.exec(deletesql);
        //同步到虚拟库
        this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
        //显示
        Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
        this->ui->priceLB->setNum(getPrice());
    }
}

void Widget::on_GWCROMtoSCJ_clicked()
{
    int flag=this->ui->GWCtableWidget->currentRow();
    qDebug()<<flag;
    //判断是否有被选中行
    if(flag!=-1)
    {
        QList<book> books;
        books.append(GWCbooks.at(flag));
        //插入收藏夹
        DataBase::InsertSCJ(db,books);
        //获取收藏夹书籍数据
        this->SCJbooks=DataBase::SCJQuerey(db,"select * from favor");
        //显示收藏夹书籍信息
        Show::showSCJ(this->ui->SCJtableWidget,SCJbooks);
        int index=GWCbooks.at(flag).bookIndex;
        QSqlQuery query(db);
        QString deletesql = QString("DELETE FROM shoppingtrolley WHERE bookIndex='%1'").arg(index);
        //执行sql语句
        query.exec(deletesql);
        //同步到虚拟库
        this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
        //显示
        Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
    }
    this->ui->priceLB->setNum(getPrice());
}

void Widget::on_SKAddToGWC_clicked()
{
    //获取选中行
    int flag=this->ui->SKtableWidget->currentRow();
    qDebug()<<flag;
    //判断是否有被选中行
    if(flag!=-1)
    {
        if(!isExist(GWCbooks,SKbooks.at(flag).bookIndex))
        {
            QList<book> books;
            //获取当前时间
            QDateTime local(QDateTime::currentDateTime());
            QString localTime = local.toString("yyyyMMdd");
            book temp;
            temp=SKbooks.at(flag);
            temp.inGWCDate=localTime.toInt();
            //获取收藏夹图书对象，并加入到books中
            books.append(temp);
            //插入到收购物车
            DataBase::InsertGWC(db,books);
            //获取购物车书籍数据
            this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
            //显示购物车书籍信息
            Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
        }else{
            //存在时，修改数据库，并同步到虚拟库num++
            QSqlQuery query(db);
            QString sql = QString("UPDATE shoppingtrolley SET num=num+1 WHERE bookIndex='%1'").arg(SKbooks.at(flag).bookIndex);
            //执行sql语句
            query.exec(sql);
            //同步到虚拟库
            this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
            //显示购物车书籍信息
            Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
        }
        this->ui->priceLB->setNum(getPrice());
    }
}

bool Widget::isExist(QList<book> ku,int bookIndex)
{
    for(int i=0;i<ku.length();i++)
    {
        if(ku.at(i).bookIndex==bookIndex)
        {
            return true;
        }
    }
    return false;
}

int Widget::getPrice()
{
    int price=0;
    for(int i=0;i<GWCbooks.length();i++)
    {
        price+=(GWCbooks.at(i).price*GWCbooks.at(i).num);
    }
    return price;
}

void Widget::on_GWCInNum_btn_clicked()
{
    //获取选中行
    int flag=this->ui->GWCtableWidget->currentRow();
    //判断是否有被选中行
    if(flag!=-1)
    {
        //获取书号
        int bookIndex=GWCbooks.at(flag).bookIndex;
        //进行sql操作
        QSqlQuery query(db);
        QString sql = QString("UPDATE shoppingtrolley SET num=num+1 WHERE bookIndex='%1'").arg(bookIndex);
        //执行sql语句
        query.exec(sql);
        //同步到虚拟库
        this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
        //显示购物车书籍信息
        Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
    }
    this->ui->priceLB->setNum(getPrice());
}

void Widget::on_GWCDeNum_btn_clicked()
{
    //获取选中行
    int flag=this->ui->GWCtableWidget->currentRow();
    //判断是否有被选中行
    if(flag!=-1)
    {
        if(GWCbooks.at(flag).num==1)
        {
            int index=GWCbooks.at(flag).bookIndex;
            QSqlQuery query(db);
            QString deletesql = QString("DELETE FROM shoppingtrolley WHERE bookIndex='%1'").arg(index);
            //执行sql语句
            query.exec(deletesql);
            //同步到虚拟库
            this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
            //显示
            Show::showGWC(this->ui->GWCtableWidget,GWCbooks);

            //删除词条数据
        }else{

            //获取书号
            int bookIndex=GWCbooks.at(flag).bookIndex;
            //进行sql操作
            QSqlQuery query(db);
            QString sql = QString("UPDATE shoppingtrolley SET num=num-1 WHERE bookIndex='%1'").arg(bookIndex);
            //执行sql语句
            query.exec(sql);
            //同步到虚拟库
            this->GWCbooks=DataBase::GWCQuerey(db,"select * from shoppingtrolley");
            //显示购物车书籍信息
            Show::showGWC(this->ui->GWCtableWidget,GWCbooks);
        }
    }
    this->ui->priceLB->setNum(getPrice());
}

void Widget::on_pushButton_clicked()
{

}
