#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ///error with not showing menubar on OS X
     ui->setupUi(this);
     QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(Help()));
     QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(Quit()));
     QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
     QObject::connect(ui->deleteRowButton, SIGNAL(clicked()), this, SLOT(deleteRowsSlot()));
     QObject::connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRowSlot()));
     QObject::connect(ui->filterButton, SIGNAL(clicked()), this, SLOT(filterRowsSlot()));
     QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));

     mainTable = new MainTable(this);
     ui->tableView->setModel(mainTable);

     elem_id = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//about in menu bar to get the student (who created this application) id
void MainWindow::Help(){
    About a(this);

    if (a.exec() == QDialog::Accepted)
    {

    }
}

//to quit the application
void MainWindow::Quit(){
    ui->statusbar->showMessage("Getting out of this");
    QApplication::quit();
}

void MainWindow::loadFile()
{
    delete mainTable;

    mainTable = new MainTable(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    ".../",//your path
                                                    "Data (*.csv)");
    mainTable->fillDataTableFromFile(fileName, elem_id);

    ui->tableView->setModel(mainTable);
}

void MainWindow::deleteRowsSlot(){
    DeleteDialog d(this);
    if (d.exec() == QDialog::Accepted)
    {
        mainTable->deleteRows(d.getStartIndex(), d.getNumber(), d.getAccepted());
        if (!mainTable->check_for_intervals){
            QMessageBox::information(this, "Intervals", "Invalid Interval");
        }
    }
}

void MainWindow::addRowSlot()
{
    addVehicleDialog d(this);
    d.setId(elem_id);

    // for checking if elem_id works well
    qDebug() << elem_id;

    if (d.exec() == QDialog::Accepted)
    {
        mainTable->appendRow(d.getNewRow());
        ++elem_id;
    }
}

/*we open filterdialogwindow with filter table to make it more useful to sort
the numbers there and not to switch between windows*/
void MainWindow::filterRowsSlot(){
    FilterDialog f(this);
    f.setProxyModel(mainTable);

    if (f.exec() == QDialog::Accepted)
    {
       f.FillTheTable();
       for (uint i = 0 ; i < f.IndecesToDelete.size(); ++i){
           mainTable->removeRow(f.IndecesToDelete[i]);
       }
       /*setting newTable - in small time i did not find another more effective algorithm,
        because deleting from original table will displace indices and programm will work
       incorrectly*/
       mainTable->setTable();
    }
}

void MainWindow::saveFile()
{
    //you will save it to new .csv file
    QString fileName = QFileDialog::getSaveFileName(this, "Open File",
                                                  ".../.csv",//probably your path
                                                  "Data (*.csv)");
    mainTable->saveDataTableToFile(fileName);
}
