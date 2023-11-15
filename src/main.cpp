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
 void resetsensor(){
   rotation_sensor.setPosition(0, degree);
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

void opcontrol() {
    set_drive_to_coast();

	while (true) {
        tank_drive( 
            // OPTIONAL: // adjust curve (DEFAULT IS 4.0):// <curve_value_here>
        );
        setIntake ();
        setIntakeMotor();
    if (master.get_digital(DIGITAL_R2)) {
            lWings.set_value(true);
            rWings.set_value(true);
            lInt.set_value(false);
            rInt.set_value(false);
        } 
        else if (master.get_digital(DIGITAL_UP)){
            lInt.set_value(false);
            rInt.set_value(false);
        }
         else if (master.get_digital(DIGITAL_RIGHT)){
            lWings.set_value(true);
            rWings.set_value(true);
         }
        else {
            lWings.set_value(false);
            rWings.set_value(false);
            lInt.set_value(true);
            rInt.set_value(true);
        }

		pros::delay(10);
	}

}




// this is needed for LVGL displaying! Do not touch!
int matchGifsSize = sizeof(matchGifs) / sizeof(matchGifs[0]);
// this is needed for LVGL displaying! Do not touch!
int calibrationGifsSize = sizeof(calibrationGifs) / sizeof(calibrationGifs[0]);