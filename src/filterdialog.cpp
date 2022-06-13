#include "filterdialog.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveParameters()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(acceptSlot()));
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::setProxyModel(QAbstractTableModel* mainTable){
    proxyModel = new ProxyModel(this);

    proxyModel->setSourceModel(mainTable);
    ui->filterView->setModel(proxyModel);
}

void FilterDialog::saveParameters(){
    /*setting minimum and maximum possible dates for calender as in addvehicle.cpp
    QDate::currentDate()*/

    /*if we doesnt enter date here - the system will set the current date
    and filter through vlaue of DateStolen in each row independently*/
    ui->calender->setDateRange(QDate(1990, 1, 1), QDate::currentDate());

    /*setting all needed filters
    if lineEdits are empty we set deafult empty string and does not change _setting*/
    if (ui->colorEdit->text().isEmpty()){
        Color = "";
    }
    else{
        Color = ui->colorEdit->text();
        color_setting = true;
    }

    if (ui->modelEdit->text().isEmpty()){
        VehicleModel = "";
    }
    else{
        VehicleModel = ui->modelEdit->text();
        model_setting = true;
    }

    if (ui->descEdit->text().isEmpty()){
        VehicleDesc = "";
    }
    else{
        VehicleDesc = ui->descEdit->text();
        desc_setting = true;
    }

    if (ui->yearEdit->text().isEmpty()){
        ModelYear = "";
    }
    else{
        ModelYear = ui->yearEdit->text();
        year_setting = true;
    }

    if (ui->typeEdit->text().isEmpty()){
        Type = "";
    }
    else{
        Type = ui->typeEdit->text();
        type_setting = true;
    }

    /*if we enter current date - it sets when we doesnt click on calender -
    - then we will sort independenlty by each value of dat in each column*/
    if (ui->calender->selectedDate() == QDate::currentDate()){
        DateStolen = "";
        date_setting = false;
    }
    else{
        DateStolen = ui->calender->selectedDate().toString("d/MM/yyyy");
    }

    if (ui->locationEdit->text().isEmpty()){
        Location = "";
    }
    else{
        Location = ui->locationEdit->text();
        location_setting = true;
    }

    //setting filters
    proxyModel -> setFilters(Color, color_setting, VehicleModel, model_setting, VehicleDesc, desc_setting,
                             ModelYear, year_setting, Type, type_setting, DateStolen, date_setting, Location, location_setting);
}

void FilterDialog::FillTheTable(){
    for (int i = 0 ; i < proxyModel->rowCount(); ++i ){
        IndecesToDelete.append(proxyModel->mapToSource(proxyModel->index(i, 0)).row());
    }
    qDebug() << IndecesToDelete.size();
}

void FilterDialog::acceptSlot(){
    accept();
}
