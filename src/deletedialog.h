#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();
    const uint& getStartIndex();
    const uint& getNumber();
    const bool& getAccepted();

private slots:
    void saveIndices();

private:
    Ui::DeleteDialog *ui;

    uint starting_index = 0;
    uint number = 0;
    bool accepted;
};

#endif // DELETEDIALOG_H
