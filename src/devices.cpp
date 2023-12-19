#include "lemlib/api.hpp"
#include "main.h"
#include "devices.hpp"
#include "drivercontrol.hpp"

// this stuff is for example autos, you should get rid of this and add your own devices here
bool wingsOut = false;
bool intOut = false;
bool gameLock = false;
bool ptoOut = true;
// this stuff is for example autos, you should get rid of this and add your own devices here

pros::ADIDigitalOut lWing('C');
pros::ADIDigitalOut rWing('D');
pros::ADIDigitalOut lInt('F');
pros::ADIDigitalOut rInt('E');
pros::ADIDigitalOut pto ('G');
pros::ADIDigitalOut lGLock ('B');
pros::ADIDigitalOut rGLock ('A');

// this stuff is for example autos, you should get rid of this and add your own devices here

pros::Motor intake (7, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor shootmotor (10, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
// this stuff is for example autos, you should get rid of this and add your own devices here


// set up your motors here but try not to change the names
// DO NOT CHANGE NAMES
pros::Motor leftFront(12, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor leftBack(13, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor leftTop(11, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor rightFront(19, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor rightBack(20, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor rightTop(17, pros::E_MOTOR_GEARSET_06, true); 
// DO NOT CHANGE NAMES

pros::MotorGroup left_side_motors({leftFront, leftBack, leftTop});
pros::MotorGroup right_side_motors({rightFront, rightFront, rightTop});

pros::Imu inertial_sensor(14); 
pros::Rotation rotation_sensor(2);

pros::Controller master(pros::E_CONTROLLER_MASTER);

lemlib::Drivetrain_t drivetrain {
    &left_side_motors, 
    &right_side_motors, 
    11.75, 
    3.25,
    450,
    2 // chase power
};

lemlib::OdomSensors_t sensors {
    nullptr, 
    nullptr, 
    nullptr, 
    nullptr,
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    0.45, // kP
    5, // kD
    1, // smallErrorRange
    80, // smallErrorTimeout
    3, // largeErrorRange
    300, // largeErrorTimeout
    7 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    5, // kP
    35, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
