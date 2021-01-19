#include "choose_one.h"
#include "ui_choose_one.h"
#include "mainwindow.h"

#include <QDebug>

Choose_one::Choose_one(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose_one)
{
    ui->setupUi(this);

}

Choose_one::~Choose_one()
{
    delete ui;
}

void Choose_one::Rev_Value(std::string value){

    std::istringstream ss(value);
    std::string item;

    while(std::getline(ss, item, ',')){
        ui->listWidget->addItem(QString(item.c_str()));
    }

}

void Choose_one::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    emit Send_Value(item->text().toStdString());
    close();
}
