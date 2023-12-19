#include "main.h"
#include "lemlib/api.hpp"
#include "drivercontrol.hpp"
#include "devices.hpp"
#include "autons.hpp"
#include "gif-pros/gifclass.hpp"
#include "screen.hpp"
#include "display/lvgl.h" 

/**
     ____  _  _  ____         _                       
    |___ \| || ||___ \       | |                      
     __) | || |_ __) |_  __ | |_ ___ _ __ ___  _ __  
    |__ <|__   _|__ <\ \/ / | __/ _ \ '_ ` _ \| '_ \ 
    ___) |  | | ___) |>  <  | ||  __/ | | | | | |_) |
    |____/   |_||____//_/\_\  \__\___|_| |_| |_| .__/ 
                                                | |    
                                                |_|    


    for SETUP:
        go to devices.cpp and set up your drivetrain and other motors
    
    for autons:
        go to autons.cpp
 */


// Enter your autons here!
AutonFunction autonFunctions[] = {
    {"Left Quals", leftSideQual},
    {"Left Elims", leftSideElims},
    {"Skills", skills}
};
// this is needed for LVGL displaying! Do not touch!
size_t autonCount = sizeof(autonFunctions) / sizeof(autonFunctions[0]);

// these are the gifs that will display randomly for the calibration screen
std::string calibrationGifs[] = {
                "/usd/jq-griddy.gif", 
                "/usd/dog-angry.gif", 
                "/usd/did-you-pray-today.gif", 
                "/usd/beast-boy.gif", 
            };

// these are the gifs that will display randomly during the match
std::string matchGifs[] = {
                "/usd/getreal.gif", 
                "/usd/minecraft-sky-parkour.gif", 
            };

void initialize() {
    calibrationScreenInit();

    chassis.calibrate();

    // auton selector
    autonSelectorScreenInit(
        // your auton funcitons
        autonFunctions, 
        // auton count needed for LVGL displaying
        autonCount, 
        // customizable color scheme, play around with it! (default is red)
        LV_COLOR_MAKE(0xFF, 0x00, 0x00)
    );
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {} 

/**
 * Runs after initialize(), and before autonomous when connected to the Field

 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 */
void autonomous() {
    set_drive_to_coast(); // Drive motors MUST be on coast for lem lib autons to work, this is because they use voltage

    runSelectedAuton(autonFunctions, autonCount);
}

/**
 * Runs the operator control code. This function will be started in its own task
 */

bool shooterToggle = false;
 bool shooterHold = false;
 bool shooterTaskEnabled = false;
 bool shootToggle = false;
 bool endToggle = false;
 bool halfToggle = false;
 bool auto_shoot = false;
 bool tranToggle = false;
 bool toggleb = false;
 bool togglea = false;
 bool toggleR2 = false;
 bool toggleD = true;
 bool toggleB = false;
 bool toggleLock = false;
void resetsensor(){
   rotation_sensor.reset_position();
 }

void shootT() { shootToggle = !shootToggle; }
void toggleShooter() { shooterHold = !shooterHold; }
void endT() {endToggle = !endToggle; }
void halfT() { halfToggle = !halfToggle; }
void togglePTO() { tranToggle = !tranToggle;}
void togglebuttonb() {toggleb = !toggleb;}
void togglebuttona() {togglea = !togglea;}
void togglebuttonR2() {toggleR2 = !toggleR2;}
void downT() {toggleD = !toggleD;}
void togB() {toggleB = ! toggleB;}
void togL() {toggleLock = !toggleLock;}



int cata_task() {
  while(!halfToggle){
    if((rotation_sensor.get_angle() >=288) || (rotation_sensor.get_angle()<=275)){
      shootmotor.move_velocity(80);
    }
    else if(auto_shoot){
      shootmotor.move_velocity(100);
      pros::Task::delay(1000);
      shootToggle = false;
    }
    else{
      shootmotor.move(0);
      shooterHold = true;
    }
    pros::Task::delay(20);
  }
  return 1;
}

int half_task() {
  while(halfToggle){
    if((rotation_sensor.get_angle()>=300) || (rotation_sensor.get_angle()<=290)){
      shootmotor.move_velocity(80);
    }
    else if(auto_shoot){
      shootmotor.move_velocity(100);
      pros::Task::delay(1000);
      shootToggle = false;
    }
    else{
      shootmotor.move(0);
      shooterHold = true;
    }
    pros::Task::delay(20);
  }
  return 1;
}


void opcontrol() {
    set_drive_to_coast();
pros::Task shoot_task(cata_task);
pros::Task h_task(half_task);
	while (true) {
        tank_drive(  
            // OPTIONAL: // adjust curve (DEFAULT IS 4.0):// <curve_value_here>
        );
        
if(master.get_digital(DIGITAL_L2)){
  intake.move_voltage(12000); // 12 volts
  
    }
    else if(master.get_digital(DIGITAL_L1)){
        intake.move_voltage(-12000); // -12 volts
        pros::Task::delay(20);
    }
    else{
        intake.move_voltage(0); // stop the motor
        pros::Task::delay(20);
    }

    if (master.get_digital(DIGITAL_R2)) {

            lWing.set_value(true);
            rWing.set_value(true);
            lInt.set_value(false);
            rInt.set_value(false);
        } 
        else if (toggleB){
            lInt.set_value(false);
            rInt.set_value(false);
        }
         else if (master.get_digital(DIGITAL_RIGHT)){
            lWing.set_value(true);
            rWing.set_value(true);
         }
        else {
            lWing.set_value(false);
            rWing.set_value(false);
            lInt.set_value(true);
            rInt.set_value(true);
        }
if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
  shooterToggle = true;
  shootmotor.move_velocity(-100);
  pros::Task::delay(200);
  shootmotor.move_velocity(0);
}
if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
(halfT);
}
if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
(downT);
}


// if(!tranToggle){
//   // Assuming RGameLock and LGameLock are Digital Out ADI devices
//   rGLock.set_value(false);
//   lGLock.set_value(false);
//   pros::Task::delay(50);
//   // Assuming Tran is a Digital Out ADI device
//   pto.set_value(true);
//   pros::Task::delay(20);
// }
// else if(tranToggle){
//   pto.set_value(false);
//   if(toggleD){
//     rGLock.set_value(true);
//     lGLock.set_value(true);
// pros::Task::delay(20);
//   }
  // else if(!toggleD){
  //   rGLock.set_value(false);
  //   lGLock.set_value(false);
  // }
  if(master.get_digital(DIGITAL_A)){
    pto.set_value(false);
    rGLock.set_value(true);
    lGLock.set_value(true);
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightTop.move_voltage(8000); // 8 volts
    leftTop.move_voltage(8000); // 8 volts
    pros::Task::delay(200);
  }
  else if(master.get_digital(DIGITAL_Y)){
    pto.set_value(false);
    rGLock.set_value(true);
    lGLock.set_value(true);
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightTop.move_voltage(-8000); // 8 volts
    leftTop.move_voltage(-8000); // 8 volts
    pros::Task::delay(200);
  }
  else if (toggleLock){
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightTop.move_voltage(0); // 8 volts
    leftTop.move_voltage(0); // 8 volts
     pto.set_value(false);
    rGLock.set_value(false);
    lGLock.set_value(false);
    pros::Task::delay(200);
  }
  else{
    rightTop.move_voltage(0); // stop the motor
    leftTop.move_voltage(0); // stop the motor
    pros::Task::delay(20);
     pto.set_value(true);
    rGLock.set_value(false);
    lGLock.set_value(false);
  }
  }

if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
    togL();
}

		pros::delay(10);
	}

//}




// this is needed for LVGL displaying! Do not touch!
int matchGifsSize = sizeof(matchGifs) / sizeof(matchGifs[0]);
// this is needed for LVGL displaying! Do not touch!
int calibrationGifsSize = sizeof(calibrationGifs) / sizeof(calibrationGifs[0]);