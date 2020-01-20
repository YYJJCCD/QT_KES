#include "add_dialog.h"
#include "ui_add_dialog.h"
#include "add_book.h"
#include "add_cd.h"
#include "add_picture.h"
#include "check_dialog.h"
add_Dialog::add_Dialog(QWidget *parent,QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::add_Dialog),db(db)
{
    qDebug()<<"add begin";
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("添加");
    ui->lab_total->setText(QString::number(Max_cap));
    solve_lab_now();
    check_size();

}

add_Dialog::~add_Dialog()
{
    delete ui;
}

void add_Dialog::on_btn_quit_clicked()
{
    qDebug()<<"add end";
    this->close();
}

void add_Dialog::on_btn_book_clicked()
{

    if(check_size()){
        add_book *Add_book = new add_book(this,db,-1);
        connect(Add_book,SIGNAL(ok()),this,SLOT(solve_lab_now()));//添加成功就就重新计数
        Add_book->setModal(true);
        Add_book->show();
    }
}
void add_Dialog::on_btn_cdv_clicked()
{
    if(check_size()){
        add_cd *Add_cd = new add_cd(this,db,-1);
        connect(Add_cd,SIGNAL(ok()),this,SLOT(solve_lab_now()));
        Add_cd->setModal(true);
        Add_cd->show();
    }
}

void add_Dialog::on_btn_picture_clicked()
{
    if(check_size()){
        add_picture *Add_picture = new add_picture(this,db,-1);
        connect(Add_picture,SIGNAL(ok()),this,SLOT(solve_lab_now()));
        Add_picture->setModal(true);
        Add_picture->show();
    }
}

void add_Dialog::solve_lab_now()
{
    QSqlQuery query(db);
    query.exec("select count(*) from summary");
    query.next();
    Now_cap=query.value(0).toInt();
    ui->lab_now->setText(QString::number(Now_cap));
}

bool add_Dialog::check_size()
{
    solve_lab_now();
    qDebug()<<"check_size begin";
    if(Now_cap>=Max_cap) {
        qDebug()<<"cap fill";
        check_Dialog *asd =new check_Dialog(this);
        asd->setModal(true);
        asd->setWindowTitle("错误");
        connect(asd,SIGNAL(rejected()),this,SLOT(close()));//弹出错误警告关闭添加窗口
        asd->show();
        return false;
    }
    qDebug()<<"ok";
    qDebug()<<"check_size end";
    return true;
}

int add_Dialog::Max_cap=11;
