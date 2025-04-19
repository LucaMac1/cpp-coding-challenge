#include "TemperatureSystem.h"

TemperatureSystem::TemperatureSystem(double time_step)
    : temperature_(20.0), time_step_(time_step) {} // Assume ambient start temp

double TemperatureSystem::update(double controlSignal)
{
    temperature_ += controlSignal * time_step_;
    return temperature_;
}

double TemperatureSystem::getOutput() const
{
    return temperature_;
}
