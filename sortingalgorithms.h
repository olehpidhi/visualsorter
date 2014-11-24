#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H
#include "datamodel.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <QAbstractItemView>


namespace SortingAlgorithms {




class VisualIterator{
private:
    std::vector<int>::iterator iter_;
    QAbstractItemView* view_;
    void highlight_item();
    void fade_item();
public:
    VisualIterator():
        view_(nullptr) {

    }

    VisualIterator(const std::vector<int>::iterator to_copy)
        :iter_(to_copy) {

    }

    VisualIterator(const VisualIterator& to_copy)
        :iter_(to_copy.iter_),
          view_(to_copy.view_) {

    }

    bool operator==(const VisualIterator& to_cmp) {
        return iter_ == to_cmp.iter_;
    }
    bool operator!=(const VisualIterator& to_cmp) {
        return iter_ != to_cmp.iter_;
    }

    VisualIterator& operator++(int) {
        ++iter_;
        return *this;
    }

    VisualIterator operator++() {
        VisualIterator to_return = VisualIterator(*this);
        ++*this;
        return to_return;
    }

    VisualIterator operator--(int) {
        --iter_;
        return *this;
    }

    VisualIterator operator--() {
        VisualIterator to_return = VisualIterator(*this);
        --*this;
        return to_return;
    }

    VisualIterator operator+=(int offset) {
        iter_ += offset;
        return *this;
    }

    VisualIterator operator-=(int offset) {
        iter_ -= offset;
        return *this;
    }

    int operator*() {
        return *iter_;
    }

    int* operator->() {
        return &(*iter_);
    }

    void swap (VisualIterator& rhs) {
        std::swap(iter_, rhs.iter_);
    }

    void swap_data(VisualIterator& rhs) {
        std::iter_swap(iter_, rhs.iter_);
    }
    friend VisualIterator operator+(VisualIterator lhs, int rhs) {
        return (lhs += rhs);
    }
    friend VisualIterator operator-(VisualIterator lhs, int rhs) {
        return (lhs -= rhs);
    }
    friend int operator-(const VisualIterator& lhs, const VisualIterator& rhs) {
        return lhs.iter_ - rhs.iter_;
    }
    friend void  std::iter_swap(VisualIterator& lhs, VisualIterator& rhs);
};

//std::iter_swap(SortingAlgorithms::VisualIterator& lhs, SortingAlgorithms::VisualIterator& rhs) {
//    std::swap(*lhs,*rhs);
//}


template <typename IteratorType ,typename Order>
void BubbleSort(IteratorType begin, IteratorType end, Order order) {
    for (IteratorType i = begin; i != end; ++i) {
        for (IteratorType j = i + 1; j != end; ++j) {
            if (order(*i,*j)) {
                std::iter_swap(i,j);
            }
        }
    }
}


// QuickSort helper. Get make <= or >= from > or <.
template<typename Order> struct non_strict_op:
        public std::binary_function<typename Order::second_argument_type,
        typename Order::first_argument_type,
        bool>
{
    non_strict_op(Order o): order(o) {}
    bool operator()(typename Order::second_argument_type arg1,
                    typename Order::first_argument_type arg2) const
    {
        return !order(arg2, arg1);
    }
private:
    Order order;
};

template<typename Order> non_strict_op<Order> non_strict(Order o) {
    return non_strict_op<Order>(o);
}

template<typename T>
T median(T t1, T t2, T t3)
{
    if (t1 < t2)
    {
        if (t2 < t3)
            return t2;
        else if (t1 < t3)
            return t3;
        else
            return t1;
    }
    else
    {
        if (t1 < t3)
            return t1;
        else if (t2 < t3)
            return t3;
        else
            return t2;
    }
}

template <typename IteratorType, typename Order>
void QuickSort(IteratorType first, IteratorType last, Order order) {

    if (last - first > 2) {
        typedef typename IteratorType::value_type value_type;
        IteratorType mid = first + (last - first)/2;
        value_type pivot = median(*first, *mid, *(last-1));
        IteratorType split1 = std::partition(first, last, std::bind2nd(order, pivot));
        IteratorType split2 = std::partition(split1, last, std::bind2nd(non_strict(order), pivot));
        QuickSort(first, split1, order);
        QuickSort(split2, last, order);
    }
}


template <typename IteratorType, typename Order>
void InsertionSort(IteratorType first, IteratorType last, Order order)
{
    for (auto i = first; i != last; ++i) {
        std::rotate(std::upper_bound(first, i, *i, order), i, i + 1);
    }
}

//void MergeSort(DataModel::DataContainer& container) {

//}
//void ShellSort(DataModel::DataContainer& container);
//}
}
#endif // SORTINGALGORITHMS_H
