#pragma once

// #include <qlist.h>
// #include <qobject.h>
// #include <qobjectdefs.h>
// #include <qstandarditemmodel.h>
// #include <qstring.h>
// #include <qtimer.h>
// #include <sensors-c++/sensors.h>
#include <QObject>
#include <QStandardItemModel>
#include <chrono>
// #include <vector>

#include "Measurement.hpp"
#include "PCI.hpp"
class QStandardItem;
class QStandardItemModel;
class QTimer;

using namespace std::literals::chrono_literals;  // NOLINT(google-global-names-in-headers)

class SensorsController final : public QObject {
    Q_OBJECT

public:
    explicit SensorsController(QObject* = nullptr);
    ~SensorsController() override;

    [[nodiscard]] QStandardItemModel* model() const noexcept { return model_; };

private:
    QStandardItem* root_;
    QStandardItemModel* model_;
    QTimer* timer_;
    std::vector<Measurement> measurements_;
    PCI pci_;

    QList<QStandardItem*> add_measurement(const sensors::subfeature&);
    void add_chip(const sensors::chip_name&);
    void start(std::chrono::milliseconds tick = 2000ms);
    void stop();
    void update();
};
