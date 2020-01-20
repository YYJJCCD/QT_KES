#include "success.h"
#include "ui_success.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include "qmysqlquerymodel.h"

success::success(QWidget *parent ,QSqlDatabase db,QString str,int num):
    QDialog(parent),
    ui(new Ui::success),db(db),num(num)
{
    ui->setupUi(this);
    QSqlQuery query(db);
    QMySQlQueryModel *model = new QMySQlQueryModel(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    if(num){
        ui->label->setText("添加成功");
        qDebug()<<"add success";
    }else{
        ui->label->setText("修改成功");
        qDebug()<<"update success";
    }
    ui->tableView->verticalHeader()->hide();//隐藏行号
    query.exec(str);
    model->setQuery(query);
    ui->tableView->setModel(model);
}

success::~success()
{
    delete ui;
}

void success::on_pushButton_clicked()
{
    this->hide();
}
