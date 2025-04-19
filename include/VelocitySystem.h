#pragma once

#include "IPlant.h"

class VelocitySystem : public IPlant
{
public:
    explicit VelocitySystem(double time_step = 0.1);

    double update(double controlSignal) override;
    double getOutput() const override;

private:
    double velocity_;
    double time_step_;
};
