#ifndef SHOW_DIALOG_H
#define SHOW_DIALOG_H

#include <QDialog>

#include <QSqlTableModel>
#include "qmysqlquerymodel.h"
namespace Ui {
class show_dialog;
}

class show_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit show_dialog(QWidget *parent,QSqlDatabase db);
    ~show_dialog();
    QString gao(QString tname);
private slots:
    void on_btn_book_clicked();

    void on_btn_sum_clicked();

    void showtable(QString name);

    void on_btn_cdv_clicked();

    void on_btn_picture_clicked();

    void on_btn_back_clicked();

private:
    Ui::show_dialog *ui;
    QMySQlQueryModel *model;
    //QMySQlQueryModel *model;
    QSqlDatabase db;
signals:
    void sendsignal();
};

#endif // SHOW_DIALOG_H
