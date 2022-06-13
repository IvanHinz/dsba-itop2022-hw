#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maintable.h"
#include <QSortFilterProxyModel>
#include "deletedialog.h"
#include "addvehicledialog.h"
#include "filterdialog.h"
#include "about.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     uint elem_id;

private slots:
    void Help();
    void Quit();
    void loadFile();
    void deleteRowsSlot();
    void addRowSlot();
    void filterRowsSlot();
    void saveFile();

private:
    Ui::MainWindow *ui;
    MainTable *mainTable;

    QAction *aboutAction;
};
#endif // MAINWINDOW_H
