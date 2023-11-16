#pragma once

#include "main.h"
#include "lemlib/api.hpp"

extern pros::Controller master;

extern pros::Motor intake;
extern pros::Motor shootmotor;

extern pros::Motor rightFront;
extern pros::Motor rightBack;
extern pros::Motor rightTop;

extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor leftTop;


extern pros::ADIDigitalOut lWings;
extern pros::ADIDigitalOut rWings;
extern pros::ADIDigitalOut lInt;
extern pros::ADIDigitalOut rInt;
extern pros::ADIDigitalOut lGLock;
extern pros::ADIDigitalOut rGLock;
extern pros::ADIDigitalOut pto;

extern pros::Rotation rotation_sensor;
extern pros::IMU inertial_sensor;

extern bool wingsOut;
extern bool IntOut;
extern bool ptoOut;
extern bool gameLock;

extern lemlib::Chassis chassis;
