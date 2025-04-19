#include "IPID.h"
#include "PID.h"
#include "PositionSystem.h"
#include "TemperatureSystem.h"
#include "VelocitySystem.h"
#include "InvertedPendulumSystem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

void simulateVisual(IPlant &system, IPID &pid, double setpoint, int steps, const std::string &title)
{
    const double controlToVelocityGain = 1.0;
    const double samplingPeriod = 0.05;

    std::vector<double> outputs;
    std::vector<double> setpoints;

    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), title);

    double yMin = setpoint - 1.0;
    double yMax = setpoint + 1.0;

    for (int step = 0; step < steps && window.isOpen(); ++step)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        double output = system.getOutput();
        double error = setpoint - output;
        double controlSignal = pid.control(error);
        system.update(controlSignal * controlToVelocityGain);

        outputs.push_back(output);
        setpoints.push_back(setpoint);

        if (output < yMin)
            yMin = output - 0.1;
        if (output > yMax)
            yMax = output + 0.1;

        window.clear(sf::Color::Black);

        // Draw output (yellow)
        sf::VertexArray outputLine(sf::LineStrip, outputs.size());
        for (size_t i = 0; i < outputs.size(); ++i)
        {
            float x = static_cast<float>(i) / steps * windowWidth;
            float y = static_cast<float>(windowHeight - ((outputs[i] - yMin) / (yMax - yMin)) * windowHeight);
            outputLine[i].position = sf::Vector2f(x, y);
            outputLine[i].color = sf::Color::Yellow;
        }

        // Draw setpoint (red)
        sf::VertexArray setpointLine(sf::LineStrip, setpoints.size());
        for (size_t i = 0; i < setpoints.size(); ++i)
        {
            float x = static_cast<float>(i) / steps * windowWidth;
            float y = static_cast<float>(windowHeight - ((setpoints[i] - yMin) / (yMax - yMin)) * windowHeight);
            setpointLine[i].position = sf::Vector2f(x, y);
            setpointLine[i].color = sf::Color::Red;
        }

        window.draw(setpointLine);
        window.draw(outputLine);
        window.display();

        std::this_thread::sleep_for(std::chrono::duration<double>(samplingPeriod));
    }
}

int main()
{
    const int steps = 200;

    PID standardPid(1.0, 0.1, 0.05);

    std::cout << "\n--- Simulating Position System ---\n";
    PositionSystem posSystem;
    simulateVisual(posSystem, standardPid, 1.0, steps, "Position System");

    std::cout << "\n--- Simulating Velocity System ---\n";
    VelocitySystem velSystem;
    simulateVisual(velSystem, standardPid, 1.0, steps, "Velocity System");

    std::cout << "\n--- Simulating Temperature System ---\n";
    TemperatureSystem tempSystem;
    simulateVisual(tempSystem, standardPid, 100.0, steps, "Temperature System");

    std::cout << "\n--- Simulating Inverted Pendulum ---\n";
    InvertedPendulumSystem pendulum;
    PID pendulumPid(30.0, 1.0, 5.0);
    simulateVisual(pendulum, pendulumPid, 0.0, steps, "Inverted Pendulum");

    return 0;
}
