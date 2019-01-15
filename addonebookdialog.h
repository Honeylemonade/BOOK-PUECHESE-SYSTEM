#ifndef ADDONEBOOKDIALOG_H
#define ADDONEBOOKDIALOG_H
#include<book.h>
#include <QDialog>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QVariantList>
#include<book.h>
#include<database.h>
#include<show.h>
#include<sort.h>
namespace Ui {
class AddOneBookDialog;
}

class AddOneBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOneBookDialog(QWidget *parent = nullptr);
    ~AddOneBookDialog();
    Ui::AddOneBookDialog *ui;
    QSqlDatabase db2=QSqlDatabase::addDatabase("QMYSQL");
private slots:
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
};

#endif // ADDONEBOOKDIALOG_H
