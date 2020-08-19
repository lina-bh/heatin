#include "Frequency.hpp"

#include <QDebug>
#include <filesystem>
#include <fstream>

Frequency::Frequency(const char* input_path) : input_(input_path) {}

std::string Frequency::name() const {
    auto label_path = input_;
    label_path.replace(input_.find("input"), label_path.length(), "label");
    std::ifstream f(label_path.c_str());
    std::string label;
    f >> label;
    return label;
}

double Frequency::update() {
    std::ifstream f(input_.c_str());
    double val = 0.0;
    f >> val;
    return val / 1000000;
}