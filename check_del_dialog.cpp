#include "check_del_dialog.h"
#include "ui_check_del_dialog.h"
#include "qmysqlquerymodel.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QStandardItem>
#include <qmessagebox.h>
#include <QDebug>
#include<QSqlQuery>
check_del_Dialog::check_del_Dialog(QWidget *parent,QModelIndexList indexList,QSqlDatabase db,QStringList strs) :
    QDialog(parent),
    ui(new Ui::check_del_Dialog),indexList(indexList),strs(strs),db(db)
{
    ui->setupUi(this);
    int le=strs.size();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列填充
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setAlternatingRowColors(true);//颜色交替
    ui->tableWidget->horizontalHeader()
            ->setStyleSheet("QHeaderView::section {""color: black; background-color:rgb(216,216,216);}");//设置表头背景
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑 ;
    ui->tableWidget->setColumnCount(le);
    ui->tableWidget->setRowCount(indexList.size()/le);
    ui->tableWidget->setHorizontalHeaderLabels(strs);
    int t=0;
    for(auto index:indexList){
        ui->tableWidget->setItem(t/le,t%le,new QTableWidgetItem(index.data().toString()));
        t++;
    }

}

check_del_Dialog::~check_del_Dialog()
{
    delete ui;
}

void check_del_Dialog::on_btn_ok_clicked()
{
    emit ok();

    this->close();
}

void check_del_Dialog::on_btn_no_clicked()
{
    this->close();
}
