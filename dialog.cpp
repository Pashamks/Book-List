#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setScaledContents(true);
    ui->label->setMaximumSize(200, 200);
    this->setWindowTitle("About");
}

Dialog::~Dialog()
{
    delete ui;
}

