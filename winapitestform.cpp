#include "winapitestform.h"
#include "ui_winapitestform.h"

#include <QSettings>
#include <QDebug>
#include <windows.h>
#include <stdio.h>

WinapiTestForm::WinapiTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinapiTestForm)
{
    ui->setupUi(this);

    updateStatus();
}

WinapiTestForm::~WinapiTestForm()
{
    delete ui;
}

void WinapiTestForm::updateStatus()
{
    bool v = isTouchFeedback();
    this->ui->touchFeedbackCheckbox->setChecked(v);

    v = isTabletVisual();
    this->ui->tabletVisibleCheckbox->setChecked(v);
}

void WinapiTestForm::setTouchFeedback(bool visible)
{
    Q_UNUSED(visible);
#ifdef Q_OS_WIN32
    ULONG value = visible ? 1 : 0;
    BOOL returnValue = false;

    returnValue = SystemParametersInfo(SPI_SETCONTACTVISUALIZATION,
        0,                 // Not used
        (void*)value,
        SPIF_SENDCHANGE);  // Update Win.ini

    value = visible ? 0x1F : 0;

    returnValue = SystemParametersInfo(SPI_SETGESTUREVISUALIZATION,
        0,                  // Not used
        (void*)value,
        SPIF_SENDCHANGE);   // Not used
#endif
}

bool WinapiTestForm::isTouchFeedback()
{
    BOOL returnValue;
    ULONG contactVisualizationValue = -1;
    returnValue = SystemParametersInfo(SPI_GETCONTACTVISUALIZATION,
        0,         // Not used
        &contactVisualizationValue,
        0);        // Not used

    ULONG guestureVisualizationValue = -1;
    returnValue = SystemParametersInfo(SPI_GETGESTUREVISUALIZATION,
        0,         // Not used
        &guestureVisualizationValue,
        0);        // Not used

    qDebug() << "ContactVisualization" << contactVisualizationValue;
    qDebug() << "GestureVisualization" << guestureVisualizationValue;

    return (contactVisualizationValue == 1 && guestureVisualizationValue == 31);
}

void WinapiTestForm::setTabletVisual(bool visible)
{
    Q_UNUSED(visible);
#ifdef Q_OS_WIN32
    ULONG value = visible ? 0x23 : 0x20;
    BOOL returnValue = false;

    returnValue = SystemParametersInfo(0x201F,  //SPI_SETPENVISUALIZATION
        0,                     // Not used
        (void*)value,
        SPIF_UPDATEINIFILE);   // Not used
#endif
}

bool WinapiTestForm::isTabletVisual()
{
#ifdef Q_OS_WIN32
    BOOL returnValue;
    ULONG penVisualizationValue = -1;
    returnValue = SystemParametersInfo(0x201E,//SPI_GETPENVISUALIZATION,
        0,         // Not used
        &penVisualizationValue,
        0);        // Not used

    return (penVisualizationValue == 35 || penVisualizationValue == 3); //0x23 0x03
#else
    return false;
#endif
}

void WinapiTestForm::on_pushButton_clicked()
{
    updateStatus();
}

void WinapiTestForm::on_EnableTabletVisibleButton_clicked()
{
    setTabletVisual(true);
}

void WinapiTestForm::on_disableTabletVisibleButton_clicked()
{
    setTabletVisual(false);
}

void WinapiTestForm::on_disableTouchFeedbackButton_clicked()
{
    setTouchFeedback(false);
}

void WinapiTestForm::on_enableTouchFeedbackButton_clicked()
{
    setTouchFeedback(true);
}
