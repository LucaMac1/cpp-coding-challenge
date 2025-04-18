#pragma once

class IPID
{
public:
    virtual ~IPID() = default;
    virtual double control(double error) = 0;
    virtual void setKp(double kp) = 0;
    virtual void setKi(double ki) = 0;
    virtual void setKd(double kd) = 0;
    virtual void reset() = 0;
    virtual void setAntiWindupGain(double gain) = 0;
};