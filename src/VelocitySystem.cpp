#include "VelocitySystem.h"

VelocitySystem::VelocitySystem(double time_step)
    : velocity_(0.0), time_step_(time_step) {}

double VelocitySystem::update(double controlSignal)
{
    velocity_ += controlSignal * time_step_;
    return velocity_;
}

double VelocitySystem::getOutput() const
{
    return velocity_;
}
