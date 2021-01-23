#ifndef SPINDELEGATE_H
#define SPINDELEGATE_H

#include <QStyledItemDelegate>

class SpinDelegate : public QStyledItemDelegate
{
public:
    SpinDelegate(QObject *parent = NULL);

protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // SPINDELEGATE_H
