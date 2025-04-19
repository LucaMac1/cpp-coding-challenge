#include "IPID.h"
#include "PID.h"
#include "PositionSystem.h"
#include "TemperatureSystem.h"
#include "VelocitySystem.h"
#include "InvertedPendulumSystem.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

void simulate(IPlant &system, IPID &pid, double setpoint, int steps)
{
    // Define simulation parameters
    const double controlToVelocityGain = 1.0; // maps control signal to velocity change
    const double samplingPeriod = 0.05;       // time step in seconds

    for (int i = 0; i < steps; ++i)
    {
        double output = system.getOutput();
        double error = setpoint - output;
        double controlSignal = pid.control(error);

        // Simulate plant dynamics based on control signal
        double response = system.update(controlSignal * controlToVelocityGain);

        std::cout << "Step " << i
                  << " | Setpoint: " << setpoint
                  << " | Output: " << output
                  << " | Error: " << error
                  << " | Control: " << controlSignal
                  << " | Response: " << response << std::endl;

        std::this_thread::sleep_for(std::chrono::duration<double>(samplingPeriod));
    }
}

int main()
{
    const int steps = 100;
    double setpoint = 1.0;

    PID standardPid(1.0, 0.1, 0.05);

    std::cout << "\n--- Simulating Position System ---\n";
    PositionSystem posSystem;
    simulate(posSystem, standardPid, setpoint, steps);

    std::cout << "\n--- Simulating Velocity System ---\n";
    VelocitySystem velSystem;
    simulate(velSystem, standardPid, setpoint, steps);

    std::cout << "\n--- Simulating Temperature System ---\n";
    TemperatureSystem tempSystem;
    simulate(tempSystem, standardPid, 100.0, steps); // Adjusted setpoint

    std::cout << "\n--- Simulating Inverted Pendulum ---\n";
    InvertedPendulumSystem pendulum;
    PID pendulumPid(30.0, 1.0, 5.0);             // More aggressive
    simulate(pendulum, pendulumPid, 0.0, steps); // Target is upright

    return 0;
}