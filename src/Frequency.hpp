#pragma once

#include <string>

#include "Updateable.hpp"

class Frequency final : public Updateable {
public:
    explicit Frequency(const char* input_path);

    double update() override;
    const char* unit() const override { return "MHz"; }
    std::string name() const override;

private:
    std::string input_;
};