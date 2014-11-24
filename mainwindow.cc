#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <functional>
#include <thread>

#include <QString>
#include <QRegExp>
#include <QPainter>
#include <QAbstractItemModel>
#include <QItemSelectionModel>


#include "datamodel.h"
#include "sortdrawdelegate.h"
#include "sortingalgorithms.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<int> test = {1,2,3,4,5,6,7,8,9};

    model = nullptr;
    sorting_thread = nullptr;
    ui->sortingView->setItemDelegate(new Drawing::SortDrawDelegate(this));
    ui->sortingView->setUpdatesEnabled(true);
}

MainWindow::~MainWindow()
{

    if(sorting_thread != nullptr) {
        if(sorting_thread->joinable()) {
            sorting_thread->join();
        }
        delete sorting_thread;
    }

    delete ui;
    delete model;
}

void MainWindow::on_sortButton_clicked() {
    QString input_data = ui->unsortedData->text();
    unsigned num;
    bool ok;
    parsed_data.clear();
    for(QString i : input_data.split(' ', QString::SplitBehavior::SkipEmptyParts)) {
        num = i.toUInt(&ok);
        if(ok) {
            parsed_data.push_back(num);
        } else {
            ui->statusBar->showMessage("Invalid input. Input must be non negative integer numbers separeted with spaces.", 10000);
            parsed_data.clear();
            return;
        }
    }

    if(model != nullptr) {
        delete model;
    }

    model = new Model::DataModel(&parsed_data, this);
    ui->sortingView->setModel(model);
    if(sorting_thread != nullptr) {
        if(sorting_thread->joinable()) {
            sorting_thread->join();
        }
        delete sorting_thread;
    }
    sorting_thread = new std::thread(&MainWindow::sort_data, this);


//    ui->sortingView->selectionModel()->select(model->index(2,0, QModelIndex()), QItemSelectionModel::SelectionFlag::Select);

}

void MainWindow::sort_data()
{
      model->BubbleSort(std::less<int>());
}




