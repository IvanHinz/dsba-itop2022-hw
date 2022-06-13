#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "maintable.h"
#include <QSortFilterProxyModel>
#include "proxymodel.h"

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);
    ~FilterDialog();

    void setProxyModel(QAbstractTableModel* mainTable);
    void FillTheTable();

    QVector<int> IndecesToDelete;

private slots:
    void saveParameters();

    void acceptSlot();

private:
    QString Color;
    QString VehicleModel;
    QString VehicleDesc;
    QString ModelYear;
    QString Type;
    QString DateStolen;
    QString Location;

    bool color_setting = false;
    bool model_setting = false;
    bool desc_setting = false;
    bool year_setting = false;
    bool type_setting = false;
    bool date_setting = true;
    bool location_setting = false;

    Ui::FilterDialog *ui;

    ProxyModel* proxyModel;
};

#endif // FILTERDIALOG_H
