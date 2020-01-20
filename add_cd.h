#ifndef ADD_CD_H
#define ADD_CD_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class add_cd;
}

class add_cd : public QDialog
{
    Q_OBJECT

public:
    explicit add_cd(QWidget *parent,QSqlDatabase db,int num);

    ~add_cd();

private slots:
    void on_line_title_editingFinished();

    void on_btn_ok_clicked();

    void on_btn_can_clicked();

    void on_line_author_editingFinished();

    void on_line_cname_editingFinished();

    bool can_submit();

private:
    Ui::add_cd *ui;
    QSqlDatabase db;
    int num;//num为-1用于插入，否则用于修改对应编号的信息
    int flag[3];//检查能否插入值
signals:
    void ok();
};

#endif // ADD_CD_H
