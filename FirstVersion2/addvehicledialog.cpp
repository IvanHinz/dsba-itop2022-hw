#include "addvehicledialog.h"
#include "ui_addvehicledialog.h"

addVehicleDialog::addVehicleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVehicleDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

addVehicleDialog::~addVehicleDialog()
{
    delete ui;
}

//public function to set current_id, so which number of rows we have already inserted + 1
void addVehicleDialog::setId(uint& _id){
    current_id = _id;
}

void addVehicleDialog::saveAddedRow(){
    QString converted = QString::number(current_id);
    newRow.push_back(converted);

    newRow.push_back(ui->colorEdit->text());
    newRow.push_back(ui->modelEdit->text());
    newRow.push_back(ui->descEdit->text());
    newRow.push_back(ui->yearEdit->text());
    newRow.push_back(ui->typeEdit->text());
    //setting minimum and maximum possible dates for calender

    //QDate::currentDate()
    ui->calender->setMinimumDate(QDate(1990, 1, 1));
    //if user enters date in future the system will set the current date to stolen bisycle
    ui->calender->setMaximumDate(QDate::currentDate());
    newRow.push_back(ui->calender->selectedDate().toString("d/MM/yyyy"));

    //adding location
    newRow.push_back(ui->locationEdit->text());

    accept();
}

//public function to get the row which we are inserting to table
const QList<QString>& addVehicleDialog::getNewRow(){
    return newRow;
}
