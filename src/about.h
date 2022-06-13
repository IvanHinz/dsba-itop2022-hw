#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private slots:
    void getInformation();

private:
    Ui::About *ui;

protected:
    void paintEvent(QPaintEvent*) override ;
};

#endif // ABOUT_H
