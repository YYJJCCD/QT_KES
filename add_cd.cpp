#include "add_cd.h"
#include "success.h"
#include "ui_add_cd.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
add_cd::add_cd(QWidget *parent,QSqlDatabase db,int num) :
    QDialog(parent),
    ui(new Ui::add_cd),db(db),num(num)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    if(num==-1){
        qDebug()<<"add cd begin";
        this->setWindowTitle("添加视频光盘");
        ui->as_title->setText("请输入标题");
        ui->as_author->setText("请输入作者");
        ui->as_cname->setText("请输入出品者");
    }
    else {
        qDebug()<<"update cd begin";
        this->setWindowTitle("修改信息");
    }
    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(0));  // +365天
    ui->dateEdit->setCalendarPopup(true);
    QDateTime dateTime(QDateTime::currentDateTime());
    QString time_Str = dateTime.toString("yyyy年MM月dd日");
    ui->la_time->setText(time_Str);
    memset(flag,0,sizeof(flag));
    if(num!=-1){
        QSqlQuery query(db);
        QString str0=QString("SELECT *FROM summary WHERE 编号=%1").arg(num);
        query.exec(str0);
        query.next();
        ui->line_title->setText(query.value(1).toString());
        ui->line_author->setText(query.value(2).toString());
        QString clev=query.value(3).toString();
        for(int i=0;i<4;i++){
            if(ui->box_lev->itemText(i)==clev){
                ui->box_lev->setCurrentIndex(i);
                break;
            }
        }
        str0=QString("SELECT *FROM cdv WHERE 编号=%1").arg(num);
        query.exec(str0);
        query.next();
        ui->dateEdit->setDate(query.value(1).toDate());
        ui->line_cname->setText(query.value(2).toString());
        qDebug()<<("2000/1/1 "+query.value(3).toString());
        memset(flag,1,sizeof(flag));
        qDebug()<<QDateTime::fromString("2000-01-01 "+query.value(3).toString(),"yyyy-MM-dd hh:mm:ss").toString();
        ui->timeEdit->setDateTime(QDateTime::fromString("2000-01-01 "+query.value(3).toString(),"yyyy-MM-dd hh:mm:ss"));
    }
}

add_cd::~add_cd()
{
    delete ui;
}


void add_cd::on_btn_ok_clicked()
{
    if(!can_submit()){
        ui->as_check->setText("输入有误");
        return;
    }
    ui->as_check->setText(nullptr);
    QString title = ui->line_title->text().trimmed();//去空格
    QString author = ui->line_author->text().trimmed();
    QString lev = ui->box_lev->currentText().trimmed();
    QString cname = ui->line_cname->text().trimmed();
    QString date = ui->dateEdit->text();
    QString time = ui->timeEdit->text();

    QSqlQuery query(db);
    if(num==-1){//添加
        QString str = QString("insert into summary(标题,作者,评级,类型) values('%1', '%2', '%3','%4')")
                .arg(title).arg(author).arg(lev).arg(QString("视频光盘"));
        qDebug()<<str;
        query.exec(str);//插入summary表
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        int id=query.lastInsertId().toInt();//最后一次自动增长的值id
        QString str1= QString("insert into cdv values(%1, '%2', '%3','%4')")
                .arg(id).arg(date).arg(cname).arg(time);
        query.exec(str1);//插入cdv表
        qDebug()<<str1;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        QString strj = QString("SELECT cdv.`编号`,`标题`,`作者`,`评级`,`出品年份`,`出品者`,`视频长度`FROM summary JOIN cdv ON summary.`编号` = cdv.`编号`WHERE summary.`编号`=%1")
                .arg(id);
        success *add= new success(this,db,strj,1);
        add->setModal(true);
        this->close();
        add->show();
    }else{//修改

        QString str1= QString("UPDATE summary SET `标题`='%1',`作者`='%2',`评级`='%3' WHERE `编号`=%4")
                .arg(title).arg(author).arg(lev).arg(num);
        query.exec(str1);//修改summary
        qDebug()<<str1;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        QString str = QString("UPDATE cdv SET `出品年份`='%1',`出品者`='%2',`视频长度`='%3' WHERE `编号`=%4")
                .arg(date).arg(cname).arg(time).arg(num);
        query.exec(str);//修改cdv
        qDebug()<<str;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        QString strj = QString("SELECT cdv.`编号`,`标题`,`作者`,`评级`,`出品年份`,`出品者`,`视频长度`FROM summary JOIN cdv ON summary.`编号` = cdv.`编号`WHERE summary.`编号`=%1")
                .arg(num);
        success *add= new success(this,db,strj,0);
        add->setModal(true);
        this->close();
        add->show();
    }
    emit ok();
}
void add_cd::on_btn_can_clicked()
{
    if(num==-1){
        qDebug()<<"add cd end";
    }else{
        qDebug()<<"update cd end";
    }
    this->close();
}

void add_cd::on_line_title_editingFinished()
{
    QString str=ui->line_title->text().trimmed();
    if(ui->line_title->text().trimmed()==""){
        ui->as_title->setText("请输入标题");
        flag[0]=0;
    }else{
        flag[0]=1;
        ui->as_title->setText(nullptr);
    }
}

void add_cd::on_line_author_editingFinished()
{
    if(ui->line_author->text().trimmed()==""){
        ui->as_author->setText("请输入作者");
        flag[1]=0;
    }else{
        flag[1]=1;
        ui->as_author->setText(nullptr);
    }
}

void add_cd::on_line_cname_editingFinished()
{
    if(ui->line_cname->text().trimmed()==""){
        ui->as_cname->setText("请输入出品者");
        flag[2]=0;
    }else{
        flag[2]=1;
        ui->as_cname->setText(nullptr);
    }
}

bool add_cd::can_submit()
{
    for(int i=0;i<3;i++){
        if(!flag[i]) return false;
    }
    return true;
}


