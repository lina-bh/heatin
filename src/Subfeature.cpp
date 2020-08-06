#include "Subfeature.hpp"

#include <sensors-c++/error.h>

#include <QStandardItem>
#include <utility>

#include "SensorsController.hpp"
#include "SensorsUtil.hpp"

Subfeature::Subfeature(sensors::subfeature subfeature) : source_(std::move(subfeature)) {
    value_col_ = new QStandardItem();
    min_col_ = new QStandardItem();
    max_col_ = new QStandardItem();
    min_ = max_ = 0.0f;
}

void Subfeature::update() {
    const auto* unit = SensorsUtil::unit(source_.feature().type());
    try {
        auto value = source_.read();
        value_col_->setText(QString("%1%2").arg(value).arg(unit));
        if (value < min_ || min_col_->text().isEmpty()) {
            min_ = value;
            min_col_->setText(QString("%1%2").arg(value).arg(unit));
        }
        if (value > max_ || max_col_->text().isEmpty()) {
            max_ = value;
            max_col_->setText(QString("%1%2").arg(value).arg(unit));
        }
    } catch (sensors::io_error& ex) {
        value_col_->setText(SensorsController::tr("cannot be read %1").arg(ex.what()));
    }
}