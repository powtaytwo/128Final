#include "login.h"
#include "parking.h"
#include "ui_parking.h"
#include "reservation.h"
#include "login.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QtSql>
#include <QtDebug>
#include <QSqlQuery>

int stat = 0;
int num = 100;

parking::parking(QWidget *parent):
    QDialog(parent),
    ui(new Ui::parking)
{
    QSqlQuery qry;

    ui->setupUi(this);

    QPushButton *buttons[25];
    //CODE HERE
    for(int i=0;i<25;++i,++num){
        QString butName = "ParkSpace" + QString::number(num);
        buttons[i] = parking::findChild<QPushButton *>(butName);
        connect(buttons[i],SIGNAL(clicked()),this,SLOT(ButtonPressed()));
    }



}

parking::~parking()
{
    delete ui;
}

void parking::ButtonPressed(){

QPushButton *button = (QPushButton *)sender();

QSqlQuery qry, qry1;
int n=0;
QString but = button->text();
QString user;
    QMessageBox::StandardButton reply = QMessageBox::question(this, "SPOT "+ but,
                    "Do you want to reserve this spot?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        //check

        qry.prepare("select user_ID from User where user_status = 1");
        qry.exec();
        qry.next();
        user = qry.value(0).toString();

        qry.prepare("select spot_status from Spot where spot_ID ='"+but+"' ");
        qry.exec();
        qry.next();
        n = qry.value(0).toInt();

        if(n == 0)//true : then someone is on the spot
        {

            qry.exec("INSERT INTO Orderr (order_ID, user_ID, spot_ID, date) "
                       "VALUES (null, '"+user+"','"+but+"', null)");

            qry.exec("update Spot set spot_status = 3 where spot_ID = '"+but+"'");

            QMessageBox::information(this, "SUCCESS", "You've successfully claimed a spot.");


            hide();
            Reservation b;
            b.setModal(true);
            b.setWindowTitle("Reservation Page");
            b.exec();

        }

        else//no one is using the spot
        {
            QMessageBox::warning(this, "Error", "Someone's already in the spot");
        }


    }
}


