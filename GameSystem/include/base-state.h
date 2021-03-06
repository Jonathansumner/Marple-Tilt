#pragma once
#include "led-matrix.h"

// Forward Declarations
class MarpleTiltMachine;
class Marple;
class MPU6050;

//void updateMarple(Marple *marple, MPU6050 *gyro, bool debug, float bounce_loss);

// Base class for states
class BaseState
{
protected:
    rgb_matrix::Canvas *canvas;
    Marple *marple = nullptr;

public:
    BaseState(rgb_matrix::Canvas *c);
    virtual ~BaseState() {}

    virtual void OnEntry() = 0;
    virtual std::string Name() = 0;

    virtual void OnExit();
    virtual void Update(MPU6050 *g, volatile float x, volatile float y, volatile float z);
    void setMarple(Marple *m);
    Marple *getMarple();

    static MarpleTiltMachine runner;
};