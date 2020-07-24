#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    view_ = new QTreeView(this);

    controller_ = new SensorsController(this);

    view_->setModel(controller_->model());
    view_->expandAll();

    setCentralWidget(view_);
}

/*
auto MainWindow::create_toolbar() -> void {
    toolbar = new QToolBar();
    toolbar->setMovable(false);
    toolbar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

    auto* const add_action = toolbar->addAction("add");
    add_action->setIcon(QIcon::fromTheme("list-add"));
    add_action->setText("Add");

    auto* const remove_action = toolbar->addAction("remove");
    remove_action->setIcon(QIcon::fromTheme("list-remove"));
    remove_action->setText("Remove");

    addToolBar(toolbar);
}

    auto* root = model_.invisibleRootItem();

    auto chips = sensors::get_detected_chips();
    for (auto chip : chips) {
        auto* row = new QStandardItem(QString::fromStdString(chip.name()));
        root->appendRow(row);
    }
*/