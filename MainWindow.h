#pragma once

#include <QMainWindow>
#include <QToolBar>
#include <QTreeView>
#include <QStandardItemModel>

#include "SensorsController.h"

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    // void create_toolbar();
    // QToolBar* toolbar;
    QTreeView* view_;
    SensorsController* controller_;
};
