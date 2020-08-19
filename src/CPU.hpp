#pragma once

#include <limits>

#include "Updateable.hpp"

class CPU final : public Updateable {
public:
    explicit CPU(int idx);

    double update() override;
    std::string name() const override;
    const char* unit() const override { return "MHz"; }

    static const char* get_name();

private:
    const int idx_;
};