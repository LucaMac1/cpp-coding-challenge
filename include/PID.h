#include "IPID.h"

class PID : public IPID
{
public:
    PID();
    PID(double Kp, double Ki, double Kd);
    ~PID(){};

    double control(double error) override;
    void setKp(double kp) override;
    void setKi(double ki) override;
    void setKd(double kd) override;
    void reset() override;
    void setAntiWindupGain(double gain);
    void setOutputLimits(double min, double max);

private:
    double Kp;
    double Ki;
    double Kd;
    double cumulativeError;
    double previousError;
    double antiWindupGain;

    double outputMin = -100.0;
    double outputMax = 100.0;
};
