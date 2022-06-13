#ifndef MAINTABLE_H
#define MAINTABLE_H

#include <QAbstractTableModel>

class MainTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MainTable(QObject *parent = nullptr);

    //Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    //Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    //Fetch data dynamically:
        //bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
       //bool canFetchMore(const QModelIndex &parent) const override;
      //void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    //Add data:
        //bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
       // bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    //Remove data:
      //bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
     //bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    void fillDataTableFromFile(QString path, uint& elem_id);
    bool deleteRows(const uint& start_ind,const uint& last_ind, const bool& accepted);

    const uint& getId();

    void appendRow(const QList<QString> &row);

    bool removeRow(int idx);
    void setTable();
    void setIndicesToHold();

private:
    QList<QList<QString>> dataTable;
    QList<QString> headerList;
    uint id = 0;

    QList<QList<QString>> TableAfterDeleting;
    QVector<int>  IndicesToHold;
};

#endif // MAINTABLE_H
