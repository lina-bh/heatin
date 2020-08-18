#pragma once

#include <string>

class Updateable {
public:
    virtual ~Updateable(){};
    virtual double update() = 0;
    virtual double min() const = 0;
    virtual double max() const = 0;
    virtual const char* unit() const = 0;
    virtual std::string name() const = 0;
};