#include "sortdrawdelegate.h"
#include <QPainter>
namespace Drawing {
SortDrawDelegate::SortDrawDelegate(QObject* parent)
    : QAbstractItemDelegate(parent){

}

void SortDrawDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
//    if(option.state & QStyle::State_Selected) {
//        painter->fillRect(option.rect, option.palette.highlight());
//    }
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QColor(0,255,0,100));
    if (option.state & QStyle::State_Selected) {
        painter->setBrush(QBrush(QColor(255, 255, 0, 100)));
    } else {
        painter->setBrush(QBrush(QColor(255, 0, 0, 100), Qt::SolidPattern));
    }
    int size = index.data().toInt();
    int width = size;
    painter->drawRect(option.rect.x(), option.rect.y(),
                      width, option.rect.height());
    painter->drawText(option.rect, QString::fromStdString(std::to_string(size)));
    painter->restore();
}

QSize SortDrawDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int size = index.data().toInt();
    int width = size;
    return QSize(width, option.rect.height());
}

}

