#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <dirent.h>
#include <QListWidget>
#include "Choose_one.h"

#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    char buffer[255];
signals:
    void Send_Value(std::string value);
private slots:
    void on_list_select_cook_itemDoubleClicked(QListWidgetItem *item);
    void Rev_Value(std::string value);


    void on_dial_meet_sliderMoved(int position);

    void on_dial_vegetable_sliderMoved(int position);

    void on_dial_mushroom_sliderMoved(int position);

    void on_pushButton_meet_clicked();

    void on_pushButton_vegetable_clicked();

    void on_pushButton_mushroom_clicked();

    void on_list_meet_2_itemDoubleClicked(QListWidgetItem *item);

    void on_list_vegetable_2_itemDoubleClicked(QListWidgetItem *item);

    void on_list_mushroom_2_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_registor_clicked();

    void on_lineEdit_meet_returnPressed();

    void on_lineEdit_vegetable_returnPressed();

    void on_lineEdit_mushroom_returnPressed();

private:
    Ui::MainWindow *ui;
    QString PATH;
    Choose_one *choose;
    void Read_Cook();
    //void Choose_one();
};
#endif // MAINWINDOW_H
