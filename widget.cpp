#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pbcoffee->setEnabled(false);
    ui->pbmilk->setEnabled(false);
    ui->pbtea->setEnabled(false);
    ui->pbreset->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::pb_judge(void)
{
    ui->pbreset->setEnabled(0 < money);
    ui->pbcoffee->setEnabled(100 <= money);
    ui->pbmilk->setEnabled(150 <= money);
    ui->pbtea->setEnabled(200 <= money);
}

void Widget::return_money_calc(int* num, int* arr)
{
    for(int i = 0; i < 4; i++)
    {
        arr[i] = money / num[i];
        money %= num[i];
    }
}

void Widget::increase_money(int num)
{
    money += num;
    ui->lcdNumber->display(money);
    pb_judge();
}

void Widget::on_pb10_clicked()
{
    increase_money(10);
}


void Widget::on_pb50_clicked()
{
    increase_money(50);
}


void Widget::on_pb100_clicked()
{
    increase_money(100);
}


void Widget::on_pb500_clicked()
{
    increase_money(500);
}


void Widget::on_pbcoffee_clicked()
{
    increase_money(-100);
}


void Widget::on_pbmilk_clicked()
{
    increase_money(-150);
}


void Widget::on_pbtea_clicked()
{
    increase_money(-200);
}


void Widget::on_pbreset_clicked()
{
    QMessageBox mb;
    int price_index[4] = {500, 100, 50, 10};
    int get_coin[4] = {0, };
    return_money_calc(price_index, get_coin);
    QString msg = "";
    for(int i = 0; i < 4; i++)
    {
        if(0 != get_coin[i])
        {
            msg.append(QString::number(price_index[i]));
            msg.append(": ");
            msg.append(QString::number(get_coin[i]));
            msg.append("\n");
        }
    }
    mb.information(this, "Return", msg);
    increase_money(0);
}
