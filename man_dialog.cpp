#include "man_dialog.h"
#include "ui_man_dialog.h"
#include "check_del_dialog.h"
#include "add_book.h"
#include "add_cd.h"
#include "add_picture.h"
#include <QSqlQuery>
#include<QDebug>
#include<map>
#include<vector>
#include<QSqlError>

man_Dialog::man_Dialog(QWidget *parent,QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::man_Dialog),db(db)
{
    ui->setupUi(this);
    this->setWindowTitle("物品管理");
    qDebug()<<"man begin";
    setFixedSize(this->width(),this->height());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列填充
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中只能选中行
    //ui->tableView->setSelectionMode (QAbstractItemView::SingleSelection);//一次只能选择一行不能多行
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑 ;
    //ui->tableView->verticalHeader()->hide();//隐藏行号
    ui->tableView->setAlternatingRowColors(true);//颜色交替
    ui->tableView->horizontalHeader()
            ->setStyleSheet("QHeaderView::section {""color: black; background-color:rgb(216,216,216);}");//设置表头背景
    str = QString("select *from summary ");
    QSqlQuery query;
    query.exec(str);
    model= new QMySQlQueryModel(this);
    model->setQuery(query);
    ui->tableView->setModel(model);
}

man_Dialog::~man_Dialog()
{
    delete ui;
}

void man_Dialog::on_btn_quit_clicked()
{
    this->close();
}

void man_Dialog::on_btn_search_clicked()
{
    qDebug()<<"search begin";
    QSqlQuery query(db);
    model = new QMySQlQueryModel(this);
    QString type=ui->comboBox->currentText();
    if(type=="图书") type="book";
    else if(type=="视频光盘") type="cdv";
    else if(type=="图画") type="picture";
    std::map<QString,QString> ma;
    ma["book"] ="ISBN号,页数,出版商";
    ma["cdv"] ="出品者,出品年份,视频长度";
    ma["picture"] ="国籍,长度,宽度";
    ma["summary"] = "summary.编号,标题,作者,评级,类型";
    ui->as_update->setText(nullptr);
    QString title=ui->line_title->text();
    QString id=ui->line_no->text();
    if(!db.open()) qDebug()<<"no";
    str = QString("select *from summary ");
    if(type!="所有信息"){
        str=(QString("select %1 , %2 from summary JOIN %3 ON summary.编号 = %4.编号 ").arg(ma["summary"]).arg(ma[type]).arg(type).arg(type));
    }
    if(title!=""&&id!=""){
        str+=QString("WHERE summary.标题='%1' AND summary.编号=%2").arg(title).arg(id);
    }else if(title!=""){
        str+=QString("WHERE summary.标题='%1'").arg(title);
    }else if(id!=""){
        str+=QString("WHERE summary.编号=%1").arg(id);
    }
    qDebug()<<str;
    query.exec(str);
    if(query.lastError().text()!=""){
        qDebug()<<"ok";
    }else{
        qDebug()<<"no";
    }
    if(!query.next()){
        qDebug()<<"not find";
        ui->tableView->setModel(nullptr);
        QDialog *asd= new QDialog(this);
        asd->setModal(true);
        asd->setWindowTitle("Not find");
        asd->setFixedSize(400,100);
        QLabel *mes = new QLabel(asd);
        QFont mes_font;
        mes_font.setPointSize(11);
        mes->setFont(mes_font);
        mes->setGeometry(0,20,400,30);
        mes->setAlignment(Qt::AlignCenter);
        QPushButton *btn= new QPushButton(asd);
        btn->setText("cancel");
        btn->setGeometry(150,60,100,30);
        mes->setText("未找到对应信息");
        QObject::connect(btn,SIGNAL(clicked(bool)),asd,SLOT(close()));
        asd->show();
    }else{
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->show();
    }
    qDebug()<<"search end";
}

void man_Dialog::on_btn_del_clicked()
{

    indexList = ui->tableView->selectionModel()->selectedIndexes();
    QStringList strs;
    for(int i=0;i<ui->tableView->model()->columnCount();i++){
        strs.push_back( ui->tableView->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());//获取表头信息
    }
    check_del_Dialog *asd = new check_del_Dialog(this,indexList,db,strs);
    asd->show();
    connect(asd,SIGNAL(ok()),this,SLOT(Delete()));//确认删除窗口关闭时执行删除操作
}

void man_Dialog::on_btn_update_clicked()
{
    indexList = ui->tableView->selectionModel()->selectedIndexes();
    QString id,type;
    int t=0;
    if(indexList.size()!=5&&indexList.size()!=8){
        ui->as_update->setText("只能选中一行");
        return;
    }
    ui->as_update->setText(nullptr);
    for(auto i:indexList){
        qDebug()<<i.data().toString();
        if(t==0) id=i.data().toString();
        else if(t==4) {
            type=i.data().toString();
        }
        t++;
    }
    if(type=="图书"){
        add_book *asd = new add_book(this,db,id.toInt());
        connect(asd,SIGNAL(ok()),this,SLOT(research()));//确认更新后更新表
        asd->show();
    }else if(type=="视频光盘"){
        add_cd *asd = new add_cd(this,db,id.toInt());
        connect(asd,SIGNAL(ok()),this,SLOT(research()));
        asd->show();
    }else if(type=="图画"){
        add_picture *asd = new add_picture(this,db,id.toInt());
        QObject::connect(asd,SIGNAL(ok()),this,SLOT(research()));
        asd->show();
    }
}

void man_Dialog::research()
{
    QSqlQuery query(db);
    qDebug()<<"research begin";
    query.exec(str);
    qDebug()<<str;
    model->setQuery(query);
    qDebug()<<"research end";
}

void man_Dialog::Delete()
{
    QSqlQuery query(db);
    qDebug()<<"Delete begin";
    for(auto index:indexList){
        QString str=QString("DELETE FROM summary WHERE 编号=%1").arg(index.data().toString());
        qDebug()<<str;
        query.exec(str);
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
    }
    qDebug()<<"Delete end";
    research();
}
