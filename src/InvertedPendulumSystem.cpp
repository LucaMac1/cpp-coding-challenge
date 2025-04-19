#include "InvertedPendulumSystem.h"

InvertedPendulumSystem::InvertedPendulumSystem(double time_step)
    : angle_(0.1), angularVel_(0.0), time_step_(time_step) {}

double InvertedPendulumSystem::update(double controlSignal)
{
    // Simplified dynamics: torque = controlSignal
    double inertia = 1.0;
    double gravity = 9.81;
    double length = 1.0;

    double torque = controlSignal;
    double angularAcc = (torque - gravity * std::sin(angle_) * length) / inertia;

    angularVel_ += angularAcc * time_step_;
    angle_ += angularVel_ * time_step_;

    return angle_;
}

double InvertedPendulumSystem::getOutput() const
{
    return angle_;
}
