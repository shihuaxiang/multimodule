#ifndef WINAPITESTFORM_H
#define WINAPITESTFORM_H

#include <QWidget>

namespace Ui {
class WinapiTestForm;
}

class WinapiTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit WinapiTestForm(QWidget *parent = nullptr);
    ~WinapiTestForm();

    static void setTouchFeedback(bool visible);
    static bool isTouchFeedback();

    static void setTabletVisual(bool visible);
    static bool isTabletVisual();

private slots:
    void on_pushButton_clicked();

    void on_EnableTabletVisibleButton_clicked();

    void on_disableTabletVisibleButton_clicked();

    void on_disableTouchFeedbackButton_clicked();

    void on_enableTouchFeedbackButton_clicked();

private:
    Ui::WinapiTestForm *ui;

    void updateStatus();
};

#endif // WINAPITESTFORM_H
