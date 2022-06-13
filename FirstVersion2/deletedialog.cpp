#include "deletedialog.h"
#include "ui_deletedialog.h"


DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->acceptButton, SIGNAL(clicked()), this, SLOT(saveIndices()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::saveIndices(){
    /// tried to use QRegularExpressionValidator but met QTBUG-9304
    ///- https://forum.qt.io/topic/131330/virtualkeyboard-program-crash-when-input-out-of-range-char-to-a-qlineedit-with-validator/13
    /*QRegularExpressionValidator validate(QRegularExpression("[0-9]\\d{0,3}"));

    qDebug() << "Numbers entered!";

    int pos = 0;
    QString first_ind = ui->startEdit->text();
    QString last_ind = ui->lastEdit->text();
    if (validate.validate(first_ind, pos) == QValidator::Acceptable&&validate.validate(last_ind, pos) == QValidator::Acceptable){
        qDebug() << "Valid character input";
        starting_index = ui->startEdit->text().toInt();
        last_index = ui->lastEdit->text().toInt();
    }
    else{
       QMessageBox::warning(this, "Title", "Looooonger Text");
    }*/

    //variables for checking if our input were integer numbers;
    bool str_check;
    bool lst_check;

    starting_index = ui->startEdit->text().toInt(&str_check);
    number = ui->lastEdit->text().toInt(&lst_check);

    if (str_check && lst_check){
        //checking numbers to be more then 1 because our id's in first column starts with 1
        qDebug() << starting_index;
        qDebug() << number;
        if (starting_index>=1 && number>=1){
            accepted = true;
        }
        else{
            QMessageBox::information(this, "Intervals", "Invalid Interval");

        }
    }
    else{
        QMessageBox::information(this, "Input problems", "Invalid input");
    }

    accept();
}

//public function to get starting index
const uint& DeleteDialog::getStartIndex(){
    return starting_index;
}

//public function to get number of rows to delete starting from inputed starting_index;
const uint& DeleteDialog::getNumber(){
    return number;
}

//public function to check if started process of deleting by indices
const bool& DeleteDialog::getAccepted(){
    return accepted;
}
