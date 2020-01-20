#ifndef ADD_PICTURE_H
#define ADD_PICTURE_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class add_picture;
}

class add_picture : public QDialog
{
    Q_OBJECT

public:
    explicit add_picture(QWidget *parent,QSqlDatabase db,int num);
    ~add_picture();

private slots:
    void on_line_title_editingFinished();

    void on_btn_ok_clicked();

    void on_line_len_editingFinished();

    void on_line_width_editingFinished();

    void on_btn_can_clicked();

    bool can_submit();

    void on_line_author_editingFinished();

private:
    Ui::add_picture *ui;
    QSqlDatabase db;
    int num;
    int flag[3];//检查能否插入值
signals:
    void ok();
};

#endif // ADD_PICTURE_H
