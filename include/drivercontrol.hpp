#pragma once

#include "pros/rtos.hpp"
#include "lemlib/api.hpp"

// . . .
// 
//  DRIVER CONTROL
//
// . . .
void togglePto();
void setFourBarToHold();
void setIntakeToCoast();
void fourBarUp();
void fourBarDown();
void intakeOn();
void intakeReverse();

void tank_drive(double curve = 4.0);
void set_drive_to_coast();
void set_drive_to_hold();
void setIntake ();
void setIntakeMotor ();
