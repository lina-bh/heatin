#pragma once

class Measurement {
public:
    Measurement() = delete;

    virtual void update() const;
};