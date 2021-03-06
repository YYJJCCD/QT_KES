#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "man_dialog.h"
#include "success.h"
#include<QBitmap>
#include<QSqlQuery>

#include <QStyleOption>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("媒体库管理系统");
    //ui->btn_add->setStyleSheet("background-image: url(:/new/prefix1/add.png)");
    connect_Database();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_exist_clicked()
{
    this->close();
}



void MainWindow::connect_Database()
{
    if (QSqlDatabase::contains("library"))//判断testConnect连接是否存在并连接
    {
        db = QSqlDatabase::database("library");
    }
    else //未连接则新建数据库连接
    {
        db=QSqlDatabase::addDatabase("QMYSQL");//创建数据库连接
        db.setDatabaseName("library");
        db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
        db.setPort(3306);                 //连接数据库端口号，与设置一致
        db.setUserName("root");          //数据库用户名，与设置一致
        db.setPassword("123456");    //数据库密码，与设置一致
    }

    if(db.open())
    {
        qDebug()<<"database open";
        //return;
    }else{
         qDebug()<<"database not open";
    }
}
void MainWindow::on_btn_add_clicked()
{

    add_Dialog *Add_Dialog = new add_Dialog(this,db);
    this->hide();
    connect(Add_Dialog,SIGNAL(rejected()),this,SLOT(show()));
    Add_Dialog->setModal(true);
    Add_Dialog->show();
}

void MainWindow::on_btn_show_clicked()
{


    show_dialog *asd=new show_dialog(this,db);
    this->hide();
    connect(asd,SIGNAL(rejected()),this,SLOT(show()));//关闭时返回上一级菜单
    asd->setModal(true);
    asd->show();
}


void MainWindow::on_btn_manage_clicked()
{

    man_Dialog *asd=new man_Dialog(this,db);
    this->hide();
    connect(asd,SIGNAL(rejected()),this,SLOT(show()));//关闭时返回上一级菜单
    asd->setModal(true);
    asd->show();
}
