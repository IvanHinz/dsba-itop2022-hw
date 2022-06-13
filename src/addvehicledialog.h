#ifndef ADDVEHICLEDIALOG_H
#define ADDVEHICLEDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class addVehicleDialog;
}

class addVehicleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addVehicleDialog(QWidget *parent = nullptr);
    ~addVehicleDialog();

    const QList<QString>& getNewRow();
    void setId(uint& _id);

private slots:
    void saveAddedRow();

private:
    QList<QString> newRow;
    uint current_id;

    Ui::addVehicleDialog *ui;
};

#endif // ADDVEHICLEDIALOG_H
