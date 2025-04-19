#pragma once

#include "IPlant.h"

class TemperatureSystem : public IPlant
{
public:
    explicit TemperatureSystem(double time_step = 0.1);

    double update(double controlSignal) override;
    double getOutput() const override;

private:
    double temperature_;
    double time_step_;
};
