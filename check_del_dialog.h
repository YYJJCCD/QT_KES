#ifndef CHECK_DEL_DIALOG_H
#define CHECK_DEL_DIALOG_H

#include "qmysqlquerymodel.h"

#include <QDialog>
#include <QItemSelectionModel>

namespace Ui {
class check_del_Dialog;
}

class check_del_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit check_del_Dialog(QWidget *parent,QModelIndexList indexList,QSqlDatabase db,QStringList str);
    ~check_del_Dialog();

private:
    Ui::check_del_Dialog *ui;
    QModelIndexList indexList;
    QStringList strs;
    QSqlDatabase db;

signals:
    void ok();
private slots:
    void on_btn_ok_clicked();
    void on_btn_no_clicked();
};

#endif // CHECK_DEL_DIALOG_H
