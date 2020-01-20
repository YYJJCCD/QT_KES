#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include <QTableView>
#include "add_book.h"
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class add_Dialog;
}

class add_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_Dialog(QWidget *parent,QSqlDatabase db);
    ~add_Dialog();

private slots:
    void on_btn_book_clicked();

    void on_btn_quit_clicked();

    void on_btn_cdv_clicked();

    void on_btn_picture_clicked();

    void solve_lab_now();

    bool check_size();


private:
    Ui::add_Dialog *ui;
    QSqlDatabase db;
    static int Max_cap;
    int Now_cap;

};

#endif // ADD_DIALOG_H
