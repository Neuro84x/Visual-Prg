#include "mainwindow.h"
#include "ui_mainwindow.h"


double num_first;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Button_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->Button_Plus_Minus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->Button_Procent,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->Button_Divide,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->Button_Multiply,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->Button_Plus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->Button_Substract,SIGNAL(clicked()),this,SLOT(math_operations()));

    ui->Button_Divide->setCheckable(true);
    ui->Button_Multiply->setCheckable(true);
    ui->Button_Plus->setCheckable(true);
    ui->Button_Substract->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers(){
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label;

    if(ui->Result->text().contains(".") && button->text() == "0"){
        new_label = ui->Result->text()+button->text();
    } else {
        all_numbers = (ui->Result->text()+button->text()).toDouble();

        new_label = QString::number(all_numbers, 'g',15);
    }



    ui->Result->setText(new_label);
}

void MainWindow::on_Button_dot_clicked()
{
    if(!(ui->Result->text().contains('.'))){
        ui->Result->setText(ui->Result->text()+'.');
    }
}

void MainWindow::operations(){
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;

    if(button->text() == "+/-"){
        all_numbers = (ui->Result->text()).toDouble();
        all_numbers *= -1;
        new_label = QString::number(all_numbers, 'g',15);

        ui->Result->setText(new_label);
    } else if(button->text() == "%"){
        all_numbers = (ui->Result->text()).toDouble();
        all_numbers *= 0.01;
        new_label = QString::number(all_numbers, 'g',15);

        ui->Result->setText(new_label);
    }
}

void MainWindow::math_operations(){
    QPushButton *button = (QPushButton *)sender();

    num_first = ui->Result->text().toDouble();

    ui->Result->setText("");

    button->setChecked(true); //
}

void MainWindow::on_Clear_clicked()
{
    ui->Button_Plus->setChecked(false);
    ui->Button_Substract->setChecked(false);
    ui->Button_Divide->setChecked(false);
    ui->Button_Multiply->setChecked(false);
    ui->Result->setText("0");
    num_first = 0;
}

void MainWindow::on_Button_Equal_clicked()
{
    double label_number = 0, num_second;
    QString new_label;

    num_second = ui->Result->text().toDouble();

    if(ui->Button_Plus->isChecked()){

        label_number = num_first + num_second;
        ui->Button_Plus->setChecked(false);

    } else if(ui->Button_Substract->isChecked()){

        label_number = num_first - num_second;
        ui->Button_Substract->setChecked(false);

    } else if(ui->Button_Multiply->isChecked()){

        label_number = num_first * num_second;
        ui->Button_Multiply->setChecked(false);

    } else if(ui->Button_Divide->isChecked()){

        if(num_second == 0){
            ui->Result->setText("0");
        }
        else{
            label_number = num_first / num_second;
        }
        ui->Button_Divide->setChecked(false);
    }
    new_label = QString::number(label_number,'g',15);
    ui->Result->setText(new_label);
}
