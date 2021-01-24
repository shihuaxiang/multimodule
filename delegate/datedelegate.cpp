#include "datedelegate.h"
#include <QDateTimeEdit>

DateDelegate::DateDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

// 首先创建要进行代理的窗体
QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QDateTimeEdit *pEditor = new QDateTimeEdit(parent);      // 一个日历的控件
    pEditor->setDisplayFormat("yyyy-MM-dd");   // 日期时间的显示格式
    pEditor->setCalendarPopup(true);   // 以下拉的方式显示
    pEditor->installEventFilter(const_cast<DateDelegate*>(this));  // 调用这个函数安装事件过滤器，使这个对象可以捕获QDateTimeEdit对象的事件
    return pEditor;
}

// 这个是初始化作用，初始化代理控件的数据
void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  // 先用这个index返回这个model然后用这个model得到index对应的数据
  QString strDate = index.model()->data(index).toString();
  QDate date = QDate::fromString(strDate, Qt::ISODate);     // 根据QString类型得到相应的时间类型
  QDateTimeEdit *pEditor = NULL;
  pEditor = static_cast<QDateTimeEdit*>(editor);    // 强转为QDateTimeEdit*类型
  if (pEditor != NULL)
  {
      pEditor->setDate(date);      // 设置代理控件的显示数据
  }
}

// 将代理控件里面的数据更新到视图控件中
void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QDateTimeEdit *pEditor = NULL;
  pEditor = static_cast<QDateTimeEdit*>(editor);    // 得到时间
  if (pEditor != NULL)
  {
      QDate date = pEditor->date();    // 得到时间
      model->setData(index, QVariant(date.toString(Qt::ISODate)));    // 把值放到相应的index里面
  }
}

// 代理中数据的改变放到model中
void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
