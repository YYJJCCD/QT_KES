#ifndef ADD_BOOK_H
#define ADD_BOOK_H

#include <QDialog>
#include <QtDebug>
#include <QSqlDatabase>
#include "success.h"
namespace Ui {
class add_book;
}

class add_book : public QDialog
{
    Q_OBJECT

public:
    explicit add_book(QWidget *parent,QSqlDatabase db,int num);
    ~add_book();
private slots:

    void on_line_title_editingFinished();


    void on_line_pages_editingFinished();

    void on_btn_ok_clicked();

    void on_btn_can_clicked();



    void on_line_author_editingFinished();

    void on_line_press_editingFinished();

    void on_line_isbn_editingFinished();

    bool can_submit();

private:
    Ui::add_book *ui;
    QSqlDatabase db;
    int num;
    int flag[6];//检查能否插入值
signals:
    void ok();
};

#endif // ADD_BOOK_H
