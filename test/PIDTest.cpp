/*
Problem: Build a PID class

TDD Focus:
- PID (Proportional-Integral-Derivative) controllers calculate control outputs based on error values
- Start with simple constructor tests to verify gain initialization (Kp, Ki, Kd)
- Test proportional control behavior first (error * Kp)
- Add integral control tests (accumulation of error over time * Ki)
- Add derivative control tests (rate of change of error * Kd)
- Test reset/initialization functionality
- Test edge cases (zero gains, large errors, etc.)
- Test with realistic scenarios (e.g., temperature control, position system)
- Consider adding saturation limits and anti-windup mechanisms

Start with the smallest test case, write a failing test, then make it pass.

Incrementally build up the logic.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cfloat>
#include "PID.h"

class PIDTest : public PID, public ::testing::Test
{
protected:
    std::unique_ptr<PID> pid;

    struct NormalisedGains
    {
        double Kp;
        double Ki;
        double Kd;
    };

    NormalisedGains gains;

    void SetUp() override
    {
        pid = std::make_unique<PID>(gains.Kp = 0.6, gains.Ki = 0.08, gains.Kd = 0.2);
    }

    void TearDown() override {}
};

TEST_F(PIDTest, ProportionalControl)
{
    pid->setKi(0.0);
    pid->setKd(0.0);

    double error = 2.0;
    double expectedOutput = error * gains.Kp;
    EXPECT_DOUBLE_EQ(pid->control(error), expectedOutput);
}

TEST_F(PIDTest, IntegralControl)
{
    pid->setKp(0.0);
    pid->setKd(0.0);
    double cumulativeError = 0;

    double error = 2.0;
    cumulativeError += error;
    double expectedOutput = cumulativeError * gains.Ki;
    EXPECT_DOUBLE_EQ(pid->control(error), expectedOutput);

    error = 3.0;
    cumulativeError += error;
    expectedOutput = cumulativeError * gains.Ki;
    EXPECT_DOUBLE_EQ(pid->control(error), expectedOutput);
}

TEST_F(PIDTest, DerivativeControl)
{
    pid->setKp(0.0);
    pid->setKi(0.0);
    double previousError = 0;

    double error = 2.0;
    previousError = error;
    pid->control(error);

    error = 5.0;
    double expectedOutput = (error - previousError) * gains.Kd;
    EXPECT_DOUBLE_EQ(pid->control(error), expectedOutput);
}

TEST_F(PIDTest, CombinedPDControl)
{
    // Test P and D components together, I=0
    pid->setKi(0.0);
    double previousError = 0;
    double error = 2.0;
    previousError = error;
    pid->control(error);
    error = 5.0;
    double expectedOutput = error * gains.Kp + (error - previousError) * gains.Kd;
    EXPECT_DOUBLE_EQ(pid->control(error), expectedOutput);
}

TEST_F(PIDTest, FullPIDControlSequence)
{
    double error = 2.0;
    double cumulativeError = 0;
    double previousError = 0;

    cumulativeError += error;
    previousError = error;
    pid->control(error);

    error = 5.0;
    cumulativeError += error;
    double expectedOutput = error * gains.Kp + cumulativeError * gains.Ki + (error - previousError) * gains.Kd;
    previousError = error;
    EXPECT_DOUBLE_EQ(pid->control(error), expectedOutput);
}

TEST_F(PIDTest, ZeroGainsProduceZeroOutput)
{
    pid->setKp(0.0);
    pid->setKi(0.0);
    pid->setKd(0.0);

    double error = 100.0;
    EXPECT_DOUBLE_EQ(pid->control(error), 0.0);
}

TEST_F(PIDTest, ResetControllerToEnsureCleanState)
{

    EXPECT_DOUBLE_EQ(pid->control(1.0), 1.0 * gains.Kp + 1.0 * gains.Ki + 1.0 * gains.Kd);
    EXPECT_DOUBLE_EQ(pid->control(2.0), 2.0 * gains.Kp + (1.0 + 2.0) * gains.Ki + (2.0 - 1.0) * gains.Kd);
    EXPECT_DOUBLE_EQ(pid->control(0.0), 0.0 * gains.Kp + (1.0 + 2.0 + 0.0) * gains.Ki + (0.0 - 2.0) * gains.Kd);

    pid->reset();

    EXPECT_DOUBLE_EQ(pid->control(1.0), 1.0 * gains.Kp + 1.0 * gains.Ki + 1.0 * gains.Kd);
    EXPECT_DOUBLE_EQ(pid->control(2.0), 2.0 * gains.Kp + (1.0 + 2.0) * gains.Ki + (2.0 - 1.0) * gains.Kd);
    EXPECT_DOUBLE_EQ(pid->control(0.0), 0.0 * gains.Kp + (1.0 + 2.0 + 0.0) * gains.Ki + (0.0 - 2.0) * gains.Kd);
}

TEST_F(PIDTest, ErrorDecreasingToZero)
{
    std::vector<double> errors = {5.0, 3.0, 1.0, 0.5, 0.0};
    for (double e : errors)
    {
        double output = pid->control(e);
        EXPECT_GE(output, 0.0); // Output should be positive but trending down
    }
}

TEST_F(PIDTest, HandlesNegativeError)
{
    double error = -4.0;
    double output = pid->control(error);

    EXPECT_LT(output, 0.0); // Should be negative output
}

TEST_F(PIDTest, AntiWindupWithGainBacksOffCumulativeError)
{
    pid->setKp(0.0);
    pid->setKi(100.0);
    pid->setKd(0.0);
    pid->setAntiWindupGain(1.0);

    for (int i = 0; i < 10; ++i)
    {
        pid->control(1.0);
    }

    double clampedOutput = pid->control(1.0);
    EXPECT_LE(clampedOutput, 100.0);
}

TEST_F(PIDTest, AntiWindupDoesNotOverCorrect)
{
    pid->setKp(0.0);
    pid->setKi(50.0);
    pid->setKd(0.0);
    pid->setAntiWindupGain(0.5);
    pid->setOutputLimits(-10.0, 10.0);

    for (int i = 0; i < 10; ++i)
    {
        pid->control(1.0); // should hit clamp and back off slowly
    }

    double output = pid->control(1.0);
    EXPECT_LE(output, 10.0);
}

TEST_F(PIDTest, ReachesSetpointInSimulatedLoop)
{
    double setpoint = 10.0;
    double current = 0.0;
    double error = 0.0;

    pid->setKp(0.5);
    pid->setKi(0.1);
    pid->setKd(0.05);

    for (int i = 0; i < 50; ++i)
    {
        error = setpoint - current;
        double controlOutput = pid->control(error);

        // Assume plant reacts linearly to control output
        current += controlOutput * gains.Ki;
    }

    EXPECT_NEAR(current, setpoint, 0.5);
}
