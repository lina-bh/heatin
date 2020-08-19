#pragma once

#include <QMainWindow>
class QTreeView;
class SensorsController;

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();

    // void create_toolbar();
    // QToolBar* toolbar;
    QTreeView* view_;
    SensorsController* controller_;
};
