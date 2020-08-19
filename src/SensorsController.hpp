#pragma once

#include <sensors-c++/sensors.h>

#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTimer>
#include <chrono>
#include <memory>
#include <vector>

#include "Updateable.hpp"

constexpr auto ROW_SOURCE_ROLE = Qt::UserRole + 1;
constexpr auto MIN_ROLE = Qt::UserRole + 2;
constexpr auto MAX_ROLE = Qt::UserRole + 2;

using namespace std::literals::chrono_literals; // NOLINT(google-global-names-in-headers)

class SensorsController final : public QObject {
    Q_OBJECT

public:
    explicit SensorsController(QObject* = nullptr);
    ~SensorsController() override;

    [[nodiscard]] QStandardItemModel* model() const noexcept { return model_; };

private:
    void start(std::chrono::milliseconds tick = 2000ms);
    void stop();
    void update();
    void add_chips();
    void add_cpus();

    QList<QStandardItem*> new_row(std::unique_ptr<Updateable>);

    QStandardItem* root_;
    QStandardItemModel* model_;
    QTimer* timer_;
    std::vector<std::unique_ptr<Updateable>> sources_;
};
