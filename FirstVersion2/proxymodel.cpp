#include "proxymodel.h"

ProxyModel::ProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const{
    //setting our QModelIndices for each filtering column
    QModelIndex index0 = sourceModel()->index(source_row, 1);
    QModelIndex index1 = sourceModel()->index(source_row, 2);
    QModelIndex index2 = sourceModel()->index(source_row, 3);
    QModelIndex index3 = sourceModel()->index(source_row, 4);
    QModelIndex index4 = sourceModel()->index(source_row, 5);
    QModelIndex index5 = sourceModel()->index(source_row, 6);
    QModelIndex index6 = sourceModel()->index(source_row, 7);

    //we need to implement this to avoid errors with data and const QVariant in maintable.cpp
    QString _c;//color
    QString _m;//model
    QString _d;//date
    QString _y;//year
    QString _t;//type
    QString _dt;//datestolen
    QString _l;//location

    /*cheking if color is setted and if it is not, we set filter column (for example Color) value for each row - equal to the value of the
    value of this row in this column*/
    if (!color_setted){
        _c = sourceModel()->data(index0).toString();
    }
    else{
        _c = color;
    }

    if (!model_setted){
        _m = sourceModel()->data(index1).toString();
    }
    else{
        _m = model;
    }

    if (!desc_setted){
        _d = sourceModel()->data(index2).toString();
    }
    else{
        _d = desc;
    }

    if (!year_setted){
        _y = sourceModel()->data(index3).toString();
    }
    else{
        _y = year;
    }

    if (!type_setted){
        _t = sourceModel()->data(index4).toString();
    }
    else{
        _t = type;
    }

    if (!date_setted){
        _dt = sourceModel()->data(index5).toString();
    }
    else{
        _dt = date;
    }

    if (!location_setted){
       _l = sourceModel()->data(index6).toString();
    }
    else{
       _l = location;
    }

    //filtering
    if (sourceModel()->data(index0).toString() != _c || sourceModel()->data(index1).toString() != _m ||
            sourceModel()->data(index2).toString() != _d || sourceModel()->data(index3).toString() != _y ||
            sourceModel()->data(index4).toString() != _t || sourceModel()->data(index5).toString() != _dt ||
            sourceModel()->data(index6).toString() != _l){
            return false;
    }

    return true;
}

//here we are setting values for columns through which we filter
void ProxyModel::setFilters(
        QString _color, bool _color_setted, QString _model, bool _model_setted, QString _desc,
        bool _desc_setted, QString _year, bool _year_setted, QString _type, bool _type_setted, QString _date, bool _date_setted,
        QString _location, bool _location_setted){
    /* we are doing this to avoid mistake with setting the same filter as before -
    when it accepts everything filterAcceptsRow*/
    invalidate();
    color = _color;
//    qDebug() << color;
    color_setted = _color_setted;
//    qDebug() << color_setted;
    model = _model;
//    qDebug() <<model;
    model_setted = _model_setted;
//    qDebug() << model_setted;
    desc = _desc;
//    qDebug() << desc;
    desc_setted = _desc_setted;
//    qDebug() << desc_setted;
    year = _year;
//    qDebug() << year;
    year_setted = _year_setted;
//    qDebug() << year_setted;
    type = _type;
//    qDebug() << type;
    type_setted = _type_setted;
//    qDebug() << type_setted;
    date = _date;
//    qDebug() << date;
    date_setted = _date_setted;
//    qDebug() << date_setted;
    location = _location;
//    qDebug() << location;
    location_setted = _location_setted;
//    qDebug() << location_setted;
}
