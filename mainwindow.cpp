#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   QString Operand1 = ui->plainTextEdit->toPlainText() + ui->plainTextEdit_2->toPlainText() + ui->plainTextEdit_3->toPlainText();
   ui->plainTextEdit_4->setPlainText(Operand1);

   QSqlDatabase db = QSqlDatabase::addDatabase(DATABASEDRIVER);
   db.setHostName(DATABASEURL);
   db.setDatabaseName(DATABASENAME);
   db.setUserName(DATABASEUSER);
   db.setPassword(DATABASEPASSWORD);

   if (!db.open())
       {
            ui->label_4->setText("Unable to connect to database !!!");
           return;
       }
        ui->label_4->setText("Connected to database again....");


   QSqlQuery query1;
   query1.exec("SELECT MD5('" + Operand1 + "')" );
   //qDebug() << pin_number;
   query1.next();
   QString MD5_Hash_from_db = query1.value(0).toString();

   ui->plainTextEdit_4->setPlainText(MD5_Hash_from_db);

}
