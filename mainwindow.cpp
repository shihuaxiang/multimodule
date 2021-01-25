#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include <delegate/delegateunittest.h>
#include "compressform.h"
#include "winapitestform.h"

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

void MainWindow::on_pushButton_clicked()
{
    QTableView * tableView = new QTableView();
    DelegateUnitTest::initTableView(tableView);
    tableView->resize(600, 300);
    tableView->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    CompressForm * form = new CompressForm();
    form->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    WinapiTestForm * form = new WinapiTestForm();
    form->show();
}
