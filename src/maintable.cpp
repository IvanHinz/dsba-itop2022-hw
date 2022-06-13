#include "maintable.h"
#include <QFile>
#include <QMessageBox>

MainTable::MainTable(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void MainTable::fillDataTableFromFile(QString path, uint& elem_id)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    //add the extended column ID by myself to control how many rows i have already inserted when i run application
    headerList.append("ID");
    ++id;

    QString firstline = inputStream.readLine();
    for (QString& item : firstline.split(",")) {
        headerList.append(item);
    }

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        QList<QString> dataRow;

        QString converted = QString::number(elem_id);
        dataRow.append(converted);

        for (QString& item : line.split(",")) {
            dataRow.append(item);
        }
        dataTable.append(dataRow);

        ++id;
        ++elem_id;
    }
    inputFile.close();
}

QVariant MainTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        {
            return headerList[section];
        }
        return QVariant();
}

//bool MainTable::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}


int MainTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return 0;

        return dataTable.size();
}

void MainTable::setIndicesToHold(){
    for (int i = 0; i < rowCount(); ++i){
        IndicesToHold.append(i);
    }
}

int MainTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return 0;

        if (dataTable.empty())
        {
            return 0;
        }

        return dataTable[0].size();
}

//bool MainTable::hasChildren(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//}

//bool MainTable::canFetchMore(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//    return false;
//}

//void MainTable::fetchMore(const QModelIndex &parent)
//{
//    // FIXME: Implement me!
//}

QVariant MainTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            int row = index.row();
            int col = index.column();
            return dataTable[row][col];
        }
        return QVariant();
}

bool MainTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
            int row = index.row();
            int col = index.column();
            dataTable[row][col] = value.toString();
            emit dataChanged(index, index, {role});
            return true;
        }
        return false;
}

Qt::ItemFlags MainTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::NoItemFlags;

        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

//bool MainTable::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(parent, row, row + count - 1);
//    // FIXME: Implement me!
//    endInsertRows();
//    return true;
//}

//bool MainTable::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//    return true;
//}

//function to delete rows from index to index + number (here last_ind)
bool MainTable::deleteRows(const uint& start_ind,const uint& last_ind, const bool& accepted){
    if (accepted && start_ind <= rowCount() + 1 && start_ind + last_ind <= rowCount() + 1 && start_ind >=1 && last_ind >= 1){
        beginRemoveRows(QModelIndex(), start_ind - 1, start_ind -1 + last_ind - 1);

        // +1 because of inclusion of the last element
        for (int i = 0; i < last_ind - 1 + 1; ++i){
            dataTable.removeAt(start_ind-1);
        }

        endRemoveRows();
    }
    else{
        check_for_intervals = false;
    }
    return true;
}

//bool MainTable::removeColumns(int column, int count, const QModelIndex &parent)
//{
//    beginRemoveColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endRemoveColumns();
//    return true;
//}

//function to return id - so the number of rows already entered
const uint& MainTable::getId(){
    return id;
}

//function to append rows in MainTable object
void MainTable::appendRow(const QList<QString> &row)
{
    size_t newRowNumber = rowCount();
    beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
    dataTable.append(row);
    endInsertRows();
}

//removing rows from initially acceptable rows
bool MainTable::removeRow(int idx)
{
    setIndicesToHold();
    //holding only numbers which are not in our IndicesToDelete (see filterdialog.cpp)
    if (IndicesToHold.contains(idx)){
        IndicesToHold.removeOne(idx);
    }
    return true;
}

//setting new rows
void MainTable::setTable(){
   /*holding only such rows in TableAfterDeleting which are in
    IndicesToHold*/
    for(int i = 0; i < IndicesToHold.size(); ++i){
        TableAfterDeleting.append(dataTable[IndicesToHold[i]]);
    }
    dataTable = TableAfterDeleting;
}

//for copying datatable to another file
void MainTable::saveDataTableToFile(QString path)
{
    QFile outputFile(path);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream outputStream(&outputFile);

    bool first = true;
    for (QString& item : headerList){
        if (first)
        {
            outputStream << item;
            first = false;
        }
        else
        {
            outputStream << ",";
            outputStream << item;
        }
    }
    outputStream << "\n";

    for (QList<QString>& row: dataTable)
    {
        bool first = true;
        for (QString&row : row){
            if (first)
            {
                outputStream <<  row;
                first = false;
            }
            else
            {
                outputStream << ",";
                outputStream <<  row;
            }
        }
        outputStream << "\n";
     }

     outputFile.close();
}
