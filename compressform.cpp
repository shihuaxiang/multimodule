#include "compressform.h"
#include "ui_compressform.h"
#include <QFileDialog>
#include <QDebug>
#include <QImageReader>

CompressForm::CompressForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompressForm)
{
    ui->setupUi(this);
}

CompressForm::~CompressForm()
{
    delete ui;
}

void CompressForm::on_autosaveButton_clicked()
{
    QString srcFileName = QFileDialog::getOpenFileName(this, "Open File", "", tr("Image File(*.png; *.jpg)"));
    QString targetFileName = srcFileName.left(srcFileName.length() - 4) + "_autosave" + srcFileName.right(4);

    QPixmap pixmap(srcFileName);
    pixmap.save(targetFileName);

    qInfo() << "srcFileName, srcFileSize, targetFileSize" << srcFileName << QFileInfo(srcFileName).size() << QFileInfo(targetFileName).size();
}

void CompressForm::on_compress100Button_clicked()
{
    compress(100);
}

void CompressForm::on_compress50Button_clicked()
{
    compress(50);
}

void CompressForm::on_compressButton_clicked()
{
    compress(m_quality);
}

void CompressForm::on_qualityButton_clicked()
{
    QString srcFileName = QFileDialog::getOpenFileName(this, "Open File", "", tr("Image File(*.png; *.jpg)"));

    QImageReader reader(srcFileName);
    //reader.setQuality(75);

    QImage image = reader.read();

    if (reader.supportsOption(QImageIOHandler::Size))
        qDebug() << "Size:" << reader.size();
    if (reader.supportsOption(QImageIOHandler::Quality))
        qDebug() << "quality:" << reader.quality();

    qInfo() << "srcFileName, quality" << srcFileName << reader.quality();
}

void CompressForm::on_qualityLineEdit_textChanged(const QString &arg1)
{
    m_quality = arg1.toInt();
}

void CompressForm::compress(int quality)
{
    QString srcFileName = QFileDialog::getOpenFileName(this, "Open File", "", tr("Image File(*.png; *.jpg)"));
    QString targetFileName = QString("%1%2%3%4").arg(srcFileName.left(srcFileName.length() - 4))
            .arg("_q")
            .arg(quality)
            .arg(srcFileName.right(4));

    QPixmap pixmap(srcFileName);
    pixmap.save(targetFileName, 0, quality);

    qInfo() << "srcFileName, srcFileSize, targetFileSize" << srcFileName << QFileInfo(srcFileName).size() << QFileInfo(targetFileName).size();
}
