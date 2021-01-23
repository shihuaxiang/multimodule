#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include <delegate/delegateunittest.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QStandardItemModel>

void MainWindow::on_pushButton_clicked()
{
    QTableView * tableView = new QTableView();
    DelegateUnitTest::initTableView(tableView);

//    QStandardItemModel* model = new QStandardItemModel(tableView);
//    model->setItem(0, 0, new QStandardItem("zhang"));
//    model->setItem(0, 1, new QStandardItem("3"));
//    model->setItem(0, 2, new QStandardItem("boy"));
//    tableView->setModel(model);

    tableView->resize(500, 300);
    tableView->show();
}
