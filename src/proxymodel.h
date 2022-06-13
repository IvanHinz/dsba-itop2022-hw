#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ProxyModel(QObject *parent = nullptr);

    //setting all the filters
    void setFilters(
            QString _color, bool _color_setted, QString _model, bool _model_setted, QString _desc,
            bool _desc_setted, QString _year, bool _year_setted, QString _type, bool _type_setted, QString _date, bool _date_setted,
            QString _location, bool _location_setted);

    //virtual function that accepts rows through different parameters
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    QString color;
    QString model;
    QString desc;
    QString year;
    QString type;
    QString date;
    QString location;

    bool color_setted = false;
    bool model_setted = false;
    bool desc_setted = false;
    bool year_setted = false;
    bool type_setted = false;
    bool date_setted = false;
    bool location_setted = false;
};

#endif // PROXYMODEL_H
