#include "show_dialog.h"
#include "ui_show_dialog.h"
#include <QDebug>
#include <QSqlQuery>
#include "qmysqlquerymodel.h"
show_dialog::show_dialog(QWidget *parent,QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::show_dialog),db(db)
{

    if(db.open())qDebug()<<"yes1";
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("显示物品库");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列填充
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   // ui->tableView->verticalHeader()->hide();//隐藏行号
    ui->tableView->setAlternatingRowColors(true);//颜色交替
    ui->tableView->horizontalHeader()
            ->setStyleSheet("QHeaderView::section {""color: black; background-color:rgb(216,216,216);}");//设置表头背景
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑 ;


    ui->label->setText("所有信息");
    showtable("summary");//初始化
    ui->la_picture->setText(gao("picture"));
    ui->la_sum->setText(gao("summary"));
    ui->la_book->setText(gao("book"));
    ui->la_cdv->setText(gao("cdv"));

}

show_dialog::~show_dialog()
{
    delete ui;
}

QString show_dialog::gao(QString tname)
{
    QSqlQuery query(db);
    qDebug()<<"solve"<<tname<<" count begin";
    if(!db.open()) qDebug()<<"no";
    QString str = QString("select count(*) from %1").arg(tname);
    query.exec(str);
    QString ans;
    while(query.next()){
        ans = query.value(0).toString();
    }
    //qDebug()<<ans;
    return QString(ans);
}



void show_dialog::showtable(QString name)
{

    QSqlQuery query(db);
    QString str = QString("select * from %1").arg(name);
    model = new QMySQlQueryModel(this);
    query.exec(str);
    model->setQuery(query);

    ui->tableView->setModel(model);
    ui->tableView->show();

}
void show_dialog::on_btn_sum_clicked()
{
    ui->label->setText("所有信息");
    showtable("summary");
}
void show_dialog::on_btn_cdv_clicked()
{
    ui->label->setText("视频光盘");
    showtable("cdv");
}

void show_dialog::on_btn_book_clicked()
{
    ui->label->setText("图书");
    showtable("book");
}

void show_dialog::on_btn_picture_clicked()
{
    ui->label->setText("图画");
    showtable("picture");
}

void show_dialog::on_btn_back_clicked()
{
    this->close();
}
