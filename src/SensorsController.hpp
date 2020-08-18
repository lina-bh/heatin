#pragma once

#include <QObject>
#include <chrono>
#include <memory>
#include <vector>

#include "Updateable.hpp"

class QTimer;
class QStandardItem;
class QStandardItemModel;
namespace sensors {
class chip_name;
}

constexpr auto ROW_SOURCE_ROLE = Qt::UserRole + 1;

using namespace std::literals::chrono_literals; // NOLINT(google-global-names-in-headers)

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
    std::vector<std::unique_ptr<Updateable>> sources;

    void start(std::chrono::milliseconds tick = 2000ms);
    void stop();
    void update();
    void add_chips();

    static QList<QStandardItem*> new_row(const std::string& name);
};
