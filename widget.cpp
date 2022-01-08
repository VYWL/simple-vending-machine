#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setControl();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeMoney(int coin)
{
    money += coin;
    ui->lcdNumber->display(money);
    setControl();
}

void Widget::setControl()
{
    ui->pbCoffee->setEnabled(money >= 200);
    ui->pbMilk->setEnabled(money >= 100);
    ui->pbTea->setEnabled(money >= 150);
    ui->pbReset->setEnabled(money > 0);
}

void Widget::on_pbCoin500_clicked()
{
    changeMoney(500);
}


void Widget::on_pbCoin100_clicked()
{
    changeMoney(100);
}


void Widget::on_pbCoin50_clicked()
{
    changeMoney(50);
}


void Widget::on_pbCoin10_clicked()
{
    changeMoney(10);
}


void Widget::on_pbCoffee_clicked()
{
    changeMoney(-200);
}


void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
}



void Widget::on_pbMilk_clicked()
{
    changeMoney(-100);
}


void Widget::on_pbReset_clicked()
{
    // Count change by units

    int nowMoney     = money;
    int chargeUnit[] = { 500, 100, 50, 10 };
    int changeCnt [] = {   0,   0,  0,  0 };

    int idx = 0;
    for(auto unit : chargeUnit)
    {
        int q = nowMoney / unit;

        changeCnt[idx++] = q;
        nowMoney -= unit * q;
    }

    // Print Results

    std::stringstream result;
    result << ":: Change Count Result ::" << "\n\n";

    for(int idx = 0; idx < 4; ++idx)
    {
        result << chargeUnit[idx] << " : " << changeCnt[idx] << '\n';
    }

    result << "\n";

    QMessageBox msgBox;
    msgBox.setText(result.str().c_str());
    msgBox.exec();


    // Reset Money

    changeMoney(-money);
}

