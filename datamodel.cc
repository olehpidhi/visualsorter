
#include "datamodel.h"

namespace Model {
DataModel::DataModel(QObject* parent):
    QAbstractItemModel(parent) {

}

DataModel::DataModel(std::vector<unsigned>* data_source, QObject* parent):
    QAbstractItemModel(parent),
    data_source_(data_source) {

}


QModelIndex DataModel::index(int row, int column, const QModelIndex& parent) const {
Q_UNUSED (parent)
    if(data_source_ == nullptr || row > data_source_->size()) {
        return QModelIndex();
    }

    return createIndex(row, column, data_source_->at(row));
}

QModelIndex DataModel::parent(const QModelIndex& child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int DataModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED (parent)
    return data_source_->size();
}

int DataModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED (parent)
    return 1;
}

QVariant DataModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    return data_source_->at(index.row());
}



}
