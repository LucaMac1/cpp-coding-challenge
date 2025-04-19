#pragma once

#include "IPlant.h"
#include <cmath>

class InvertedPendulumSystem : public IPlant
{
public:
    explicit InvertedPendulumSystem(double time_step = 0.01);

    double update(double controlSignal) override;
    double getOutput() const override;

private:
    double angle_;      // radians
    double angularVel_; // rad/s
    double time_step_;
};
