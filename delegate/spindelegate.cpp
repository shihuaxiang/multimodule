#include "spindelegate.h"

#include <QSpinBox>

SpinDelegate::SpinDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *SpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QSpinBox *pEditor = new QSpinBox(parent);
    pEditor->setRange(0, 30000);
    pEditor->installEventFilter(const_cast<SpinDelegate*>(this));
    return pEditor;
}

void SpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index).toInt();
    QSpinBox *pSpinbox = NULL;
    pSpinbox = static_cast<QSpinBox*>(editor);
    if (pSpinbox != NULL)
    {
        pSpinbox->setValue(value);
    }
}

void SpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *pSpinbox = NULL;
    pSpinbox = static_cast<QSpinBox*>(editor);
    if (pSpinbox != NULL)
    {
        int value = pSpinbox->value();
        model->setData(index, value);
    }
}

void SpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}
