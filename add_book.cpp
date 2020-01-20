#include "add_book.h"
#include "ui_add_book.h"
#include <QSqlQuery>
#include<QLineEdit>
#include<algorithm>
#include <regex>
#include<QSqlError>
add_book::add_book(QWidget *parent,QSqlDatabase db,int num) :
    QDialog(parent),ui(new Ui::add_book),db(db),num(num)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    if(num==-1){
        qDebug()<<"add book begin";
        this->setWindowTitle("添加图书");
        ui->as_title->setText("请输入标题");
        ui->as_author->setText("请输入作者");
        ui->as_pre->setText("请输入出版社");
        ui->as_isbn->setText("请输入ISBN号");
        ui->as_page->setText("请输入页数");
        memset(flag,0,sizeof(flag));
    }else{
        qDebug()<<"update book begin";

        this->setWindowTitle("修改信息");
        QSqlQuery query(db);
        QString str0=QString("SELECT *FROM summary WHERE 编号=%1").arg(num);
        qDebug()<<str0;
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
        str0=QString("SELECT *FROM book WHERE 编号=%1").arg(num);
        qDebug()<<str0;
        query.exec(str0);
        query.next();
        ui->line_isbn->setText(query.value(1).toString());
        ui->line_pages->setText(query.value(2).toString());
        ui->line_press->setText(query.value(3).toString());

        memset(flag,1,sizeof(flag));
    }

}
add_book::~add_book()
{
    delete ui;
}

void add_book::on_btn_ok_clicked()
{

    if(!can_submit()){
        ui->as_check->setText("输入有误");
        return;
    }
    ui->as_check->setText(nullptr);
    QString title = ui->line_title->text().trimmed();//去空格
    QString author = ui->line_author->text().trimmed();
    QString lev = ui->box_lev->currentText().trimmed();
    QString press = ui->line_press->text().trimmed();
    QString isbn = ui->line_isbn->text().trimmed();
    int pages = (ui->line_pages->text()).trimmed().toInt();
    QSqlQuery query(db);
    if(num==-1){
        QString str = QString("insert into summary(标题,作者,评级,类型) values('%1', '%2', '%3','%4')")
                .arg(title).arg(author).arg(lev).arg(QString("图书"));
        query.exec(str);//插入summary表
        qDebug()<<str;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }

        int id=query.lastInsertId().toInt();//最后一次自动增长的值id
        QString str1= QString("insert into book values(%1, '%2', %3,'%4')")
                .arg(id).arg(isbn).arg(pages).arg(press);
        query.exec(str1);//插入book表
        qDebug()<<str1;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }
        QString strj = QString("SELECT book.`编号`,`标题`,`作者`,`评级`,`ISBN号`,`出版商`,`页数`FROM summary JOIN book ON summary.`编号` = book.`编号`WHERE summary.`编号`=%1")
                .arg(id);
        success *add= new success(this,db,strj,1);
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

        QString str = QString("UPDATE book SET `ISBN号`='%1',`页数`=%2,`出版商`='%3' WHERE `编号`=%4")
                .arg(isbn).arg(pages).arg(press).arg(num);
        query.exec(str);//修改book
        qDebug()<<str;
        if(query.lastError().text()!=""){
            qDebug()<<"ok";
        }else{
            qDebug()<<"no";
        }

        QString strj = QString("SELECT book.`编号`,`标题`,`作者`,`评级`,`ISBN号`,`出版商`,`页数`FROM summary JOIN book ON summary.`编号` = book.`编号`WHERE summary.`编号`=%1")
                .arg(num);
        success *add= new success(this,db,strj,0);
        add->setModal(true);
        this->close();
        add->show();
    }
    emit ok();//发出添加成功信号，让添加菜单的当前量重新计算
}

void add_book::on_btn_can_clicked()
{
    if(num==-1){
        qDebug()<<"add book end";
    }else{
        qDebug()<<"update book end";
    }
    this->close();
}

bool add_book::can_submit()
{
    for(int i=0;i<5;i++){
        if(!flag[i]) return false;
    }
    return true;
}


void add_book::on_line_title_editingFinished()
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

void add_book::on_line_author_editingFinished()
{
    if(ui->line_author->text().trimmed()==""){
        ui->as_author->setText("请输入作者");
        flag[1]=0;
    }else{
        flag[1]=1;
        ui->as_author->setText(nullptr);
    }
}

void add_book::on_line_press_editingFinished()
{
    if(ui->line_press->text().trimmed()==""){
        ui->as_pre->setText("请输入出版社");
        flag[2]=0;
    }else{
        flag[2]=1;
        ui->as_pre->setText(nullptr);
    }
}
using namespace  std;
void add_book::on_line_isbn_editingFinished()
{

    QRegExp qt_pattern("^[0-9]{2,6}-[0-9]{2,6}-[0-9]{2,6}-[0-9X]{1}");


    if(ui->line_isbn->text().trimmed()==""){
        ui->as_isbn->setText("请输入ISBN号");
        flag[3]=0;
    }else{
        if(qt_pattern.exactMatch(ui->line_isbn->text().trimmed())){
            flag[3]=1;
            ui->as_isbn->setText(nullptr);
        }else{
            flag[3]=0;
            ui->as_isbn->setText("ISBN号格式不正确");
        }

    }
}
void add_book::on_line_pages_editingFinished()//判断页数是否为整数
{
    if(ui->line_pages->text().trimmed()==""){
        ui->as_page->setText("请输入页数");
        flag[4]=0;
    }else{
        const char *s=ui->line_pages->text().trimmed().toLatin1().data();
        while(*s && *s>='0' && *s<='9') s++;
        if(*s||ui->line_pages->text().trimmed()=="0"){
            flag[4]=0;
            ui->as_page->setText("页数应为正整数");
        }else{
            flag[4]=1;
            ui->as_page->setText(nullptr);
        }
    }
}
