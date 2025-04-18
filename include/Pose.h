#pragma once 

class Pose {
    public:
        Pose(int id) : id_(id) {}
        virtual ~Pose() = default;
        
        int id() const { return id_; } // early binding
        
        virtual void transformBy(const Pose& other) = 0;
        virtual void print() const = 0;
    protected:
        int id_;
};
    