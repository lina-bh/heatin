#pragma once

#include <QList>
#include <optional>
#include <vector>

#include "Subfeature.hpp"
namespace sensors {
class chip_name;
}
class QStandardItem;

class Chip final {
public:
    static std::optional<Chip> create_chip(const sensors::chip_name&);

    QStandardItem* row() const { return root_; }

    void update();

private:
    explicit Chip(const sensors::chip_name&);
    QList<QStandardItem*> add_subfeature(const sensors::subfeature&);

    QStandardItem* root_;
    std::vector<Subfeature> subfeatures_;
};