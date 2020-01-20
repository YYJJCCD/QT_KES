#ifndef SUCCESS_H
#define SUCCESS_H

#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class success;
}

class success : public QDialog
{
    Q_OBJECT

public:
    explicit success(QWidget *parent ,QSqlDatabase db,QString str,int num);
    ~success();
    static QString s1,s2;
private slots:
    void on_pushButton_clicked();

private:
    Ui::success *ui;
    QSqlDatabase db;
    QString type;//类型
    int id;//最后增长的id
    int num;
//NAVK-RJJ7-PXS5-IH25
};

#endif // SUCCESS_H


















