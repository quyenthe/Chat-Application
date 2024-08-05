#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}
void ChatWidget::setMessage(QString message){


    ui->label->setText(message);
    ui->label_2->setText(QDateTime::currentDateTime().toString("HH:mm"));
}
void ChatWidget::setMessage1(QString message){

    ui->label->setAlignment(Qt::AlignRight);
    ui->label->setText(message);
    ui->label_2->setText(QDateTime::currentDateTime().toString("HH:mm"));
}

