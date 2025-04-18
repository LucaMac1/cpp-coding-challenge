#pragma once 

class Pose2D {
    public:
        Pose2D(double x, double y, double theta);
        
        Pose2D transformBy(const Pose2D& delta) const;
    
        double x() const;
        double y() const;
        double theta() const;
    
    private:
        double m_x;
        double m_y;
        double m_theta;
};
    