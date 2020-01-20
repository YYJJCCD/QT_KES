#ifndef MAN_DIALOG_H
#define MAN_DIALOG_H

#include "qmysqlquerymodel.h"

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class man_Dialog;
}

class man_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit man_Dialog(QWidget *parent ,QSqlDatabase db);
    ~man_Dialog();

private slots:
    void on_btn_quit_clicked();

    void on_btn_search_clicked();

    void on_btn_del_clicked();

    void on_btn_update_clicked();

    void research();

    void Delete();

private:
    Ui::man_Dialog *ui;
    QSqlDatabase db;
    //QMySQlQueryModel *model;
    QMySQlQueryModel *model;
    QString str;
    QModelIndexList indexList;

};

#endif // MAN_DIALOG_H
