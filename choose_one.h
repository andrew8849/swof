#ifndef CHOOSE_ONE_H
#define CHOOSE_ONE_H

#include <QDialog>
#include <QListWidget>
#include <QString>
#include <string>
#include <sstream>



namespace Ui {
class Choose_one;
}

class Choose_one : public QDialog
{
    Q_OBJECT

public:
    explicit Choose_one(QWidget *parent = nullptr);
    ~Choose_one();
private:
    Ui::Choose_one *ui;
private slots:
    void Rev_Value(std::string value);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

signals:
    void Send_Value(std::string value);
};

#endif // CHOOSE_ONE_H
