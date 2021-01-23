#include "delegateunittest.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QWidget>
#include <QTableView>
#include <QTextStream>
#include <QStandardItemModel>
#include <QStandardPaths>
#include "datedelegate.h"
#include "combodelegate.h"
#include "spindelegate.h"

DelegateUnitTest::DelegateUnitTest()
{

}

int DelegateUnitTest::initTableView(QTableView* tableView)
{
    QStandardItemModel * model = new QStandardItemModel(4, 4, tableView);
    model->setHeaderData(0, Qt::Horizontal, QLatin1String("Name"));
    model->setHeaderData(1, Qt::Horizontal, QLatin1String("Birthday"));
    model->setHeaderData(2, Qt::Horizontal, QLatin1String("Job"));
    model->setHeaderData(3, Qt::Horizontal, QLatin1String("Income"));

    QString fileName = QString("%1/testdata/info.txt").arg(
                QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "open the file failed..." << fileName;
        return -1;
    }
    else
    {
        qDebug() << "open the file success..." << fileName;

    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    QString line;
    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
    int row = 0;
    do
    {
        line = in.readLine();
        if (!line.isEmpty())
        {
            model->insertRows(row, 1, QModelIndex());
            QStringList pieces = line.split(",", Qt::SkipEmptyParts);

            qDebug() << "pieces... " << pieces;

            model->setData(model->index(row, 0, QModelIndex()), pieces.value(0));
            model->setData(model->index(row, 1, QModelIndex()), pieces.value(1));
            model->setData(model->index(row, 2, QModelIndex()), pieces.value(2));
            model->setData(model->index(row, 3, QModelIndex()), pieces.value(3));
            ++row;
        }
    } while(!line.isEmpty());
    file.close();

    tableView->setModel(model);
    tableView->setWindowTitle(QLatin1String("Delegate"));

//    DateDelegate dateDelegate;
//    tableView->setItemDelegateForColumn(1, &dateDelegate);
//    ComboDelegate comboDelegate;
//    tableView->setItemDelegateForColumn(2, &comboDelegate);
    //SpinDelegate spinDelegate;
    //tableView->setItemDelegateForColumn(3, &spinDelegate);

    return 0;
}
