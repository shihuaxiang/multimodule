#ifndef COMPRESSFORM_H
#define COMPRESSFORM_H

#include <QWidget>

namespace Ui {
class CompressForm;
}

class CompressForm : public QWidget
{
    Q_OBJECT

public:
    explicit CompressForm(QWidget *parent = nullptr);
    ~CompressForm();

private slots:
    void on_autosaveButton_clicked();

    void on_compress100Button_clicked();

    void on_compress50Button_clicked();

    void on_compressButton_clicked();

    void on_qualityButton_clicked();

    void on_qualityLineEdit_textChanged(const QString &arg1);

private:
    Ui::CompressForm *ui;

    void compress(int quality);
    int m_quality = -1;
};

#endif // COMPRESSFORM_H
