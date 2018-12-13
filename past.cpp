#include "past.h"
#include "ui_past.h"
#include "main_interface.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QtSql>
#include <QtDebug>
#include <QSqlQuery>

Past::Past(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Past)
{
    ui->setupUi(this);

    QSqlQueryModel *modal = new QSqlQueryModel();

    //conn.connOpen();
    QSqlQuery qry;
    QString user;

    qry.prepare("select user_ID from User where user_status = 1");
    qry.exec();
    qry.next();
    user = qry.value(0).toString();

    qry.prepare("select spot_ID, date, time, total_time, total_payment from Orderr where user_ID ='"+user+"' ");
    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
}

Past::~Past()
{
    delete ui;
}

void Past::on_pushButton_clicked()
{
    hide();
    main_interface one;
    one.setModal(true);
    one.setWindowTitle("PROFILE PAGE");
    one.exec();
}
