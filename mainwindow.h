#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>

#include <QMainWindow>
#include <QStandardItemModel>
#include "datamodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_sortButton_clicked();


private:
    Ui::MainWindow *ui;
    Model::DataModel* model;

    std::vector<unsigned> parsed_data;
    std::thread* sorting_thread;

    void sort_data();
};



#endif // MAINWINDOW_H
