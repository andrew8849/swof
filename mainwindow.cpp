#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::PATH = QApplication::applicationDirPath()+"/cook/";
    mkdir(MainWindow::PATH.toLocal8Bit());
    MainWindow::Read_Cook();

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Read_Cook(){

    QListWidgetItem *item;
    DIR *dir;
    struct dirent *cook;

    if((dir = opendir(MainWindow::PATH.toLocal8Bit())) != nullptr){
        while((cook = readdir(dir)) != nullptr){
            if(cook->d_name != std::string(".") && cook->d_name != std::string("..")){
                item = new QListWidgetItem(QString::fromLocal8Bit(cook->d_name));
                ui->list_select_cook->addItem(item);
            }
        }
        closedir(dir);
    }
}

void MainWindow::Rev_Value(std::string value){
    strcpy(buffer,value.c_str());
}

void MainWindow::on_list_select_cook_itemDoubleClicked(QListWidgetItem *item)
{
    FILE *file = NULL;
    QListWidgetItem *ingredient;
    std::string path;
    std::string meet;
    std::string vegetable;
    std::string mushroom;
    std::string str;
    std::string amount;
    std::string tmp;

    path = std::string(MainWindow::PATH.toLocal8Bit()) + std::string(item->text().toLocal8Bit()) + std::string("/");

    meet = path + std::string("meet.txt");
    vegetable = path + std::string("vegetable.txt");
    mushroom = path + std::string("mushroom.txt");

    // 고기류
    file = fopen(meet.c_str(),"r");
    if(file != NULL ){   
         while( !feof( file ) && fgets(buffer, sizeof(buffer), file) != NULL){
             if(buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1] = '\0'; // 파일에 저장된 재료는 공백으로 구분함으로 그 공백을 제거하기 위함
             str = buffer;  // 파일내에 저장된 재료를 std::string문자열 작업을 하기 위함
             amount= str.substr(str.find(":")+1,str.size()); // 재료의 갯수 추출
             str = str.substr(0,str.find(":"));              // 재료의 이름을 str에 저장
             strcpy(buffer,str.c_str());
             if(str.find(",") != std::string::npos){
                 choose = new Choose_one(this);
                 connect(this,SIGNAL(Send_Value(std::string)),choose,SLOT(Rev_Value(std::string)));
                 connect(choose,SIGNAL(Send_Value(std::string)),this,SLOT(Rev_Value(std::string)));
                 emit Send_Value(str);
                 choose->exec();
             }
             QList <QListWidgetItem *> test;
             test = ui->list_meet->findItems(buffer, Qt::MatchStartsWith);
             if(test.size()>0){
                 ingredient = test.takeLast();
                 tmp = ingredient->text().toStdString();
                 tmp = tmp.substr(tmp.find(" ",0)+1,tmp.size()-1);
                 int value = std::stoi(tmp) + std::stoi(amount);
                 amount = " " + std::to_string(value);
                 delete ingredient;
             }
             amount += "g";
             strcat(buffer,amount.c_str());
             ingredient = new QListWidgetItem(buffer);
             ui->list_meet->addItem(ingredient);
             ingredient-> setTextAlignment(Qt::AlignCenter);
         }
         fclose(file);
    }

    // 야채류
    file = fopen(vegetable.c_str(),"r");
    if(file != NULL ){
         while( !feof( file ) && fgets(buffer, sizeof(buffer), file) != NULL){
             if(buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1] = '\0';
             str = buffer;  // 파일내에 저장된 재료를 std::string문자열 작업을 하기 위함
             amount= str.substr(str.find(":")+1,str.size()); // 재료의 갯수 추출
             str = str.substr(0,str.find(":"));              // 재료의 이름을 str에 저장
             strcpy(buffer,str.c_str());
             if(str.find(",") != std::string::npos){
                 choose = new Choose_one(this);
                 connect(this,SIGNAL(Send_Value(std::string)),choose,SLOT(Rev_Value(std::string)));
                 connect(choose,SIGNAL(Send_Value(std::string)),this,SLOT(Rev_Value(std::string)));
                 emit Send_Value(str);
                 choose->exec();
             }
             QList <QListWidgetItem *> test;
             test = ui->list_vegetable->findItems(buffer, Qt::MatchStartsWith);
             if(test.size()>0){
                 ingredient = test.takeLast();
                 tmp = ingredient->text().toStdString();
                 tmp = tmp.substr(tmp.find(" ",0)+1,tmp.size()-1);
                 float value = std::atof(tmp.c_str()) + std::atof(amount.c_str());
                 amount = " " + std::to_string(value);
                 amount.erase(amount.find_last_not_of("0")+1,std::string::npos);
                 amount.erase (amount.find_last_not_of('.') + 1, std::string::npos );
                 delete ingredient;
             }
             amount += "개";
             strcat(buffer,amount.c_str());
             ingredient = new QListWidgetItem(buffer);
             ui->list_vegetable->addItem(ingredient);
             ingredient-> setTextAlignment(Qt::AlignCenter);
         }
         fclose(file);
    }
    file = fopen(mushroom.c_str(),"r");
    if(file != NULL ){
         while( !feof( file ) && fgets(buffer, sizeof(buffer), file) != NULL){

             if(buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1] = '\0';
             str = buffer;  // 파일내에 저장된 재료를 std::string문자열 작업을 하기 위함
             amount= str.substr(str.find(":")+1,str.size()); // 재료의 갯수 추출
             str = str.substr(0,str.find(":"));              // 재료의 이름을 str에 저장
             strcpy(buffer,str.c_str());
             if(str.find(",") != std::string::npos){
                 choose = new Choose_one(this);
                 connect(this,SIGNAL(Send_Value(std::string)),choose,SLOT(Rev_Value(std::string)));
                 connect(choose,SIGNAL(Send_Value(std::string)),this,SLOT(Rev_Value(std::string)));
                 emit Send_Value(str);
                 choose->exec();
             }
             QList <QListWidgetItem *> test;
             test = ui->list_mushroom->findItems(buffer, Qt::MatchStartsWith);
             if(test.size()>0){
                 ingredient = test.takeLast();
                 tmp = ingredient->text().toStdString();
                 tmp = tmp.substr(tmp.find(" ",0)+1,tmp.size()-1);
                 float value = std::stof(tmp) + std::stof(amount);
                 amount = " " + std::to_string(value);
                 amount.erase(amount.find_last_not_of("0")+1,std::string::npos);
                 amount.erase (amount.find_last_not_of('.') + 1, std::string::npos );
                 delete ingredient;
             }
             amount += "개";
             strcat(buffer,amount.c_str());
             ingredient = new QListWidgetItem(buffer);
             ui->list_mushroom->addItem(ingredient);
             ingredient-> setTextAlignment(Qt::AlignCenter);

         }
         fclose(file);
    }
}

void MainWindow::on_dial_meet_sliderMoved(int position)
{
    static int tmp = 0;
    QString amount;
    QStringList unit;

    amount = ui->label_meet->text();
    unit = amount.split(" ");
    amount = unit[0];
    int num = amount.toInt();
    if(position - tmp == 1 && num < 1200){
        num += 100;
        amount = QString::number(num);
    }
    else if(position - tmp == -1 && num > 0){
        num -= 100;
        amount = QString::number(num);
    }
    tmp = position;
    amount = amount + " " + unit[1];
    ui->label_meet->setText(amount);
}

void MainWindow::on_dial_vegetable_sliderMoved(int position)
{
    static float tmp = 0;
    QString amount;
    QStringList unit;

    amount = ui->label_vegetable->text();
    unit = amount.split(" ");
    amount = unit[0];
    float num = amount.toFloat();
    if(position - tmp == 1 && num < 10){
        num += float(0.1);
        amount = QString::number(num);
    }
    else if(position - tmp == -1 && num > 0){
        num -= float(0.1);
        amount = QString::number(num);
    }
    tmp = position;
    amount = amount + " " + unit[1];
    ui->label_vegetable->setText(amount);
}

void MainWindow::on_dial_mushroom_sliderMoved(int position)
{
    static int tmp = 0;
    QString amount;
    QStringList unit;

    amount = ui->label_mushroom->text();
    unit = amount.split(" ");
    amount = unit[0];
    int num = amount.toInt();
    if(position - tmp == 1 && num < 10){
        num += 1;
        amount = QString::number(num);
    }
    else if(position - tmp == -1 && num > 0){
        num -= 1;
        amount = QString::number(num);
    }
    tmp = position;
    amount = amount + " " + unit[1];
    ui->label_mushroom->setText(amount);
}

void MainWindow::on_pushButton_meet_clicked()
{
    QString ingredient;
    QString amount;
    QListWidgetItem *item;
    if(ui->label_meet->text() != "0 g"){
        ingredient = ui->lineEdit_meet->text();
        amount = ui->label_meet->text();
        item = new QListWidgetItem(ui->lineEdit_meet->text() + " " + ui->label_meet->text());
        ui->list_meet_2->addItem(item);
    }
}

void MainWindow::on_pushButton_vegetable_clicked()
{
    QString ingredient;
    QString amount;
    QListWidgetItem *item;
    if(ui->label_vegetable->text() != "0 개"){
        ingredient = ui->lineEdit_vegetable->text();
        amount = ui->label_vegetable->text();
        item = new QListWidgetItem(ui->lineEdit_vegetable->text() + " " + ui->label_vegetable->text());
        ui->list_vegetable_2->addItem(item);
    }
}

void MainWindow::on_pushButton_mushroom_clicked()
{
    QString ingredient;
    QString amount;
    QListWidgetItem *item;
    if(ui->label_mushroom->text() != "0 개"){
        ingredient = ui->lineEdit_mushroom->text();
        amount = ui->label_mushroom->text();
        item = new QListWidgetItem(ui->lineEdit_mushroom->text() + " " + ui->label_mushroom->text());
        ui->list_mushroom_2->addItem(item);
    }
}

void MainWindow::on_list_meet_2_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}

void MainWindow::on_list_vegetable_2_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}

void MainWindow::on_list_mushroom_2_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}

void MainWindow::on_pushButton_registor_clicked()
{
    QString ingredient;
    QString amount;
    QStringList unit;
    QListWidgetItem *item;

    QString cook_name;
    FILE* file;

    cook_name = MainWindow::PATH.toLocal8Bit() + ui->lineEdit_cookname->text();
    if(!mkdir(cook_name.toLocal8Bit())){
        file = fopen(cook_name.toLocal8Bit()+"/meet.txt","w");
        while((item = ui->list_meet_2->takeItem(0))){
            unit = item->text().split(" ");
            ingredient = unit[0]+ ": ";
            amount = unit[1] +"\n";
            fputs(ingredient.toUtf8(),file);
            fputs(amount.toUtf8(),file);
        }
        fclose(file);
        file = fopen(cook_name.toLocal8Bit()+"/vegetable.txt","w");
        while((item = ui->list_vegetable_2->takeItem(0))){
            unit = item->text().split(" ");
            ingredient = unit[0]+ ": ";
            amount = unit[1] + "\n";
            fputs(ingredient.toUtf8(),file);
            fputs(amount.toUtf8(),file);
        }
        fclose(file);
        file = fopen(cook_name.toLocal8Bit()+"/mushroom.txt","w");
        while((item = ui->list_mushroom_2->takeItem(0))){
            unit = item->text().split(" ");
            ingredient = unit[0]+ ": ";
            amount = unit[1] + "\n";
            fputs(ingredient.toUtf8(),file);
            fputs(amount.toUtf8(),file);
        }
        fclose(file);
        qDebug() << "success";
    }

    ui->list_select_cook->clear();
    MainWindow::Read_Cook();
}

void MainWindow::on_lineEdit_meet_returnPressed()
{
    MainWindow::on_pushButton_meet_clicked();
}

void MainWindow::on_lineEdit_vegetable_returnPressed()
{
    MainWindow::on_pushButton_vegetable_clicked();
}


void MainWindow::on_lineEdit_mushroom_returnPressed()
{
    MainWindow::on_pushButton_mushroom_clicked();
}
