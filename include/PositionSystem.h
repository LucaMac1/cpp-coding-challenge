#pragma once

#include "IPlant.h"

class PositionSystem : public IPlant
{
public:
    explicit PositionSystem(double time_step = 0.1);

    double update(double controlSignal) override;
    double getOutput() const override;

private:
    double position_;
    double velocity_;
    double time_step_;
};