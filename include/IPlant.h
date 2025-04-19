#pragma once

class IPlant {
public:
    virtual ~IPlant() = default;
    virtual double update(double controlSignal) = 0;
    virtual double getOutput() const = 0;
};
