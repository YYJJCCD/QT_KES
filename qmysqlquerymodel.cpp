#include "qmysqlquerymodel.h"
#include <QSqlQueryModel>
#include <QtSql>


QMySQlQueryModel::QMySQlQueryModel(QObject *parent):
    QSqlQueryModel(parent)
{
}

QVariant QMySQlQueryModel::data(const QModelIndex &item, int role) const
{
    if (role == Qt::TextAlignmentRole)//默认代理的对齐方式
    {
        QVariant value = (Qt::AlignCenter);
        return value;
    }
    else
        return QSqlQueryModel::data(item,role);
}
