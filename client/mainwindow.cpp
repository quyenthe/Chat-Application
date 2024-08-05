#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_socket=new QTcpSocket();
    m_socket->connectToHost(QHostAddress::LocalHost,4500);
    ui->setupUi(this);
    ui->centralwidget->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionconnect_triggered()
{
    client=new clientManager();
    connect(client,&clientManager::connected,[this]{
        ui->centralwidget->setEnabled(true);
    });

    connect(client,&clientManager::disconnected,[this]{
        ui->centralwidget->setEnabled(false);
    });
    connect(client,&clientManager::messageReceive,this,&MainWindow::messageReceive);
    connect(client,&clientManager::textReceive,this,&MainWindow::textReceive);
    connect(client,&clientManager::newclientName,this,&MainWindow::newclientName);

    client->connectToServer();




}
void MainWindow::messageReceive(QString message){

    auto chatwidget=new ChatWidget();
    chatwidget->setMessage(message);
    auto listWidget=new QListWidgetItem();
    listWidget->setSizeHint(QSize(0,65));
    ui->listWidget->addItem(listWidget);
    listWidget->setBackground(QColor(167,255,137));
    ui->listWidget->setItemWidget(listWidget,chatwidget);
}


void MainWindow::on_pushButton_clicked()
{

    auto message=ui->lineEdit->text().trimmed();
    client->sendMessage(message);
    auto chatwidget=new ChatWidget();
    chatwidget->setMessage1(message);
    auto listWidget=new QListWidgetItem();
    listWidget->setSizeHint(QSize(0,65));
    ui->listWidget->addItem(listWidget);
    listWidget->setBackground(QColor(167,255,137));
    ui->listWidget->setItemWidget(listWidget,chatwidget);
    ui->lineEdit->setText("");

}


void MainWindow::on_lineEdit_2_editingFinished()
{
    auto name=ui->lineEdit_2->text().trimmed();
    client->sendName(name);

}
void MainWindow::textReceive(QString name){

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    auto status=(Chatprotocol::Status)index;
    client->sendStatus(status);
}
void MainWindow::newclientName(QVector<QString> clientName){
    ui->comboBox_2->clear();
    for(int i=0;i<clientName.size();i++){
        ui->comboBox_2->addItem(clientName[i]);
    }
}
void MainWindow::onClientACK(){

}






void MainWindow::on_lineEdit_editingFinished()
{
    m_onclientACK=ui->comboBox_2->currentText();
    client->sendClientACK(m_onclientACK);
}

