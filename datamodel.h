#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QAbstractItemModel>
#include <QItemSelection>
#include <vector>
#include <memory>
#include <algorithm>
#include <QThread>
#include <thread>

namespace Model {

class DataModel: public QAbstractItemModel
{
    Q_OBJECT
private:
    std::vector<unsigned>* data_source_;
public:
    DataModel(QObject* parent = 0);
    DataModel(std::vector<unsigned>* data_source, QObject* parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    template <typename Order>
    void BubbleSort(Order order = std::less<int>()) {
        for (unsigned i = 0; i < data_source_->size(); ++i) {
            for (unsigned j = i + 1; j < data_source_->size(); ++j) {
                if (order((*data_source_)[i], (*data_source_)[j])) {
                    emit beginResetModel();

                    std::swap((*data_source_)[i], (*data_source_)[j]);

                    emit endResetModel();
                    QThread::msleep(100);
                }
            }
        }
    }

signals:
    void updateView(QModelIndex ind);

};
}
#endif // DATAMODEL_H
