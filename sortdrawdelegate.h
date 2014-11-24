#ifndef SORTDRAWDELEGATE_H
#define SORTDRAWDELEGATE_H
#include <QAbstractItemDelegate>

namespace Drawing {
class SortDrawDelegate: public QAbstractItemDelegate
{
    Q_OBJECT
public:
    SortDrawDelegate(QObject* parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

}

#endif // SORTDRAWDELEGATE_H
