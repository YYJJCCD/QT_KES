#ifndef CHECK_DIALOG_H
#define CHECK_DIALOG_H

#include <QDialog>

namespace Ui {
class check_Dialog;
}

class check_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit check_Dialog(QWidget *parent = nullptr);
    ~check_Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::check_Dialog *ui;
};

#endif // CHECK_DIALOG_H
