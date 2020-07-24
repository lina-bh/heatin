#pragma once

#include <map>
#include <unordered_map>
#include <QObject>
#include <QStandardItemModel>
#include <QTimer>
#include <sensors-c++/sensors.h>

class SensorsController final : public QObject
{
    Q_OBJECT

public:
    explicit SensorsController(QObject* = nullptr);
    ~SensorsController();

    QStandardItemModel* model() const noexcept;

private:
    QStandardItemModel* model_;
    QStandardItem* root_;
    QTimer* timer_;

    std::vector<std::pair<sensors::subfeature, QStandardItem*>> subfeatures_;

    void add_chip(sensors::chip_name&);
    QStandardItem* add_feature(sensors::feature&);
    const QList<QStandardItem*> add_subfeature(sensors::subfeature&);

    void start();
    void stop();
    void update();

    static bool can_read(sensors::subfeature&);
};
