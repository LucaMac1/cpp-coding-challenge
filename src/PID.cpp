#include "PID.h"
#include <algorithm>
#include <iostream>

PID::PID() : Kp(0), Ki(0), Kd(0), cumulativeError(0), previousError(0), antiWindupGain(1.0)
{
}

PID::PID(double Kp, double Ki, double Kd) : Kp(Kp), Ki(Ki), Kd(Kd), cumulativeError(0), previousError(0), antiWindupGain(1.0)
{
}

double PID::control(double error)
{
    double P = error * this->Kp;

    // Store pre-clamped cumulativeError for backup
    double proposedCumulativeError = this->cumulativeError + error;
    double I = proposedCumulativeError * this->Ki;

    double D = (error - this->previousError) * this->Kd;
    this->previousError = error;

    double output = P + I + D;
    double clampedOutput = std::clamp(output, outputMin, outputMax);

    if (output != clampedOutput)
    {
        // Only partially integrate when clamped
        this->cumulativeError += error * (1.0 - antiWindupGain);
    }
    else
    {
        // Normal integration
        this->cumulativeError = proposedCumulativeError;
    }

    return clampedOutput;
}

void PID::setKp(double kp)
{
    this->Kp = kp;
}

void PID::setKi(double ki)
{
    this->Ki = ki;
}

void PID::setKd(double kd)
{
    this->Kd = kd;
}

void PID::setAntiWindupGain(double gain)
{
    this->antiWindupGain = gain;
}

void PID::setOutputLimits(double min, double max)
{
    this->outputMin = min;
    this->outputMax = max;
}

void PID::reset()
{
    this->cumulativeError = 0;
    this->previousError = 0;
}
