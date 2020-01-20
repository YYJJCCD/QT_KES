#ifndef QMYSQLQUERYMODEL_H
#define QMYSQLQUERYMODEL_H

#include <QSqlQueryModel>



class QMySQlQueryModel:public QSqlQueryModel

{
public:

    explicit QMySQlQueryModel(QObject *parent=nullptr);
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
protected:
};


#endif // QMYSQLQUERYMODEL_H
