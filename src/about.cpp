#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QObject::connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(getInformation()));
}

About::~About()
{
    delete ui;
}

//clicking - to get information about stud.number
void About::getInformation(){
    QMessageBox::information(this, "Information", "Author Ivan Orlov 213-2");
}

void About::paintEvent(QPaintEvent*){
     //making painter to start paint
    QPainter painter;
    painter.begin(this);

    //setting the pen for creating our symbol
    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::white);
    painter.setPen(pen);

    //painting our symbol
    painter.drawLine(5, 30+5, 18+5 ,5);
    painter.drawLine(5, 30+5, 60+5, 30+5);
    painter.drawLine(30+5, 5, 30+5, 60+5);
    painter.drawLine(60+5, 30+5, 60+5-18, 5);
    painter.drawLine(30+5, 60+5, 5, 60-18+5);
    painter.drawLine(30+5, 60+5, 60+5, 60+5-18);
    painter.end();
}
