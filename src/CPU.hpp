#pragma once

#include "Updateable.hpp"

class CPU final : public Updateable {
public:
    explicit CPU(int idx);
    ~CPU() override;

    double update() override;
    std::string name() const override;
    inline const char* unit() const override { return "MHz"; }

private:
    const int idx_;
    const std::string name_;
    int fd_;
};

const char* cpu_brand_string();