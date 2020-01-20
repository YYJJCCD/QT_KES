#include "check_dialog.h"
#include "ui_check_dialog.h"

check_Dialog::check_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::check_Dialog)
{
    ui->setupUi(this);
}

check_Dialog::~check_Dialog()
{
    delete ui;
}

void check_Dialog::on_pushButton_clicked()
{
    this->close();
}
