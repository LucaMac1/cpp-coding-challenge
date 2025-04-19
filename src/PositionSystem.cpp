#include "PositionSystem.h"

PositionSystem::PositionSystem(double time_step)
    : position_(0.0), velocity_(0.0), time_step_(time_step) {}

double PositionSystem::update(double controlSignal)
{
    velocity_ += controlSignal * time_step_;
    position_ += velocity_ * time_step_;
    return position_;
}

double PositionSystem::getOutput() const
{
    return position_;
}
