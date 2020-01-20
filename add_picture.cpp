#include "add_picture.h"
#include "success.h"
#include "ui_add_picture.h"

#include <QSqlQuery>
#include <QDebug>
#include<QSqlError>
add_picture::add_picture(QWidget *parent,QSqlDatabase db,int num) :
    QDialog(parent),ui(new Ui::add_picture),db(db),num(num)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    QSqlQuery query(db);
    query.exec("select show_cn from `tm_const_country`");
    while (query.next()){
        ui->box_con->addItem(query.value(0).toString());
    }
    if(num==-1){
        qDebug()<<"add picture begin";
        this->setWindowTitle("添加图书");
        ui->as_title->setText("请输入标题");
        ui->as_title->setText("请输入标题");
        ui->as_author->setText("请输入作者");
        ui->as_size->setText("请输入长和宽");
        memset(flag,0,sizeof(flag));
    }else{
        qDebug()<<"update picture begin";
        this->setWindowTitle("修改信息");
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
        str0=QString("SELECT *FROM picture WHERE 编号=%1").arg(num);
        query.exec(str0);
        query.next();
        ui->line_len->setText(query.value(2).toString());
        ui->line_width->setText(query.value(3).toString());
        QString con = query.value(1).toString();
        for(int i=0;i<ui->box_con->count();i++){
            if(ui->box_con->itemText(i)==query.value(1).toString()){
                ui->box_con->setCurrentIndex(i);
                break;
            }
        }
        memset(flag,1,sizeof(flag));
    }
}

add_picture::~add_picture()
{
    delete ui;
}



void add_picture::on_btn_ok_clicked()
{
    if(!can_submit()){
        ui->as_check->setText("输入有误");
        return;
    }
    ui->as_check->setText(nullptr);
    QString title = ui->line_title->text().trimmed();//去空格
    QString author = ui->line_author->text().trimmed();
    QString lev = ui->box_lev->currentText().trimmed();
    QString con = ui->box_con->currentText().trimmed();
    double len = ui->line_len->text().toDouble();
    double width = ui->line_width->text().toDouble();
    QSqlQuery query(db);
    if(num==-1){
        QString str = QString("insert into summary(标题,作者,评级,类型) values('%1', '%2', '%3','%4')")
                .arg(title).arg(author).arg(lev).arg(QString("图画"));
        query.exec(str);//插入summary表
        qDebug()<<str;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        int id=query.lastInsertId().toInt();
        QString str1= QString("insert into picture values(%1, '%2', %3,%4)")
                .arg(id).arg(con).arg(len).arg(width);
        query.exec(str1);
        qDebug()<<str1;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        QString strj = QString("SELECT picture.`编号`,`标题`,`作者`,`评级`,`国籍`,`长度`,`宽度`FROM summary JOIN picture ON summary.`编号` = picture.`编号`WHERE summary.`编号`=%1")
                .arg(id);
        success *add= new success(this,db,strj,1);//this->deleteLater();
        add->setModal(true);
        this->close();
        add->show();
    }else{
        QString str1= QString("UPDATE summary SET `标题`='%1',`作者`='%2',`评级`='%3' WHERE `编号`=%4")
                .arg(title).arg(author).arg(lev).arg(num);
        query.exec(str1);//修改summary
        qDebug()<<str1;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        QString str = QString("UPDATE picture SET `国籍`='%1',`长度`=%2,`宽度`=%3 WHERE `编号`=%4")
                .arg(con).arg(len).arg(width).arg(num);
        qDebug()<<str;
        query.exec(str);//修改picture
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        QString strj = QString("SELECT picture.`编号`,`标题`,`作者`,`评级`,`国籍`,`长度`,`宽度`FROM summary JOIN picture ON summary.`编号` = picture.`编号`WHERE summary.`编号`=%1")
                .arg(num);
        success *add= new success(this,db,strj,0);
        add->setModal(true);
        this->close();
        add->show();
    }
    emit ok();
}
void add_picture::on_btn_can_clicked()
{
    if(num==-1){
        qDebug()<<"add picture begin";
    }else{
        qDebug()<<"update picture end";
    }
    this->close();
}

bool add_picture::can_submit()
{
    for(int i=0;i<3;i++){
        if(!flag[i]) return false;
    }
    return true;
}

void add_picture::on_line_title_editingFinished()
{

    if(ui->line_title->text().trimmed()==""){
        ui->as_title->setText("请输入标题");
        flag[0]=0;
    }else{
        flag[0]=1;
        ui->as_title->setText(nullptr);
    }
}

void add_picture::on_line_author_editingFinished()
{
    if(ui->line_author->text().trimmed()==""){
        ui->as_author->setText("请输入作者");
        flag[1]=0;
    }else{
        flag[1]=1;
        ui->as_author->setText(nullptr);
    }
}

void add_picture::on_line_len_editingFinished()
{
    QString s1=ui->line_len->text().trimmed();
    QString s2=ui->line_width->text().trimmed();
    if(s1==""||s2==""){
        ui->as_size->setText("请输入长和宽");
        flag[2]=0;
    }else{
        int cflag=0;
        int point[2]={0};
        for(auto i:s1){
            if(!i.isDigit()){
                if(i=='.'&&i!=s1.back())
                    point[0]++;
                else
                    cflag=1;
            }
        }
        for(auto i:s2){
            if(!i.isDigit()){
                if(i=='.'&&i!=s2.back())
                    point[1]++;
                else
                    cflag=1;
            }
        }
        if(point[0]>1||point[1]>1) cflag=1;
        if(cflag){
            ui->as_size->setText("长宽应该为小数");
            flag[2]=0;
        }else{
            if(s1.toDouble()==0.0||s2.toDouble()==0.0){
                ui->as_size->setText("长宽不能为0");
                flag[2]=0;
            }
            else{
                flag[2]=1;
                ui->as_size->setText(nullptr);
            }
        }
    }
}

void add_picture::on_line_width_editingFinished()
{
    on_line_len_editingFinished();
}


