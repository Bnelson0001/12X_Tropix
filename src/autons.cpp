#include "devices.hpp"
#include "autons.hpp"
#include "drivercontrol.hpp"

void doNothing() {}

/*
┌┬┐┌─┐  ┌┬┐┌─┐┬┌─┌─┐  ┌─┐┌─┐┌┬┐┬ ┬┌─┐
 │ │ │  │││├─┤├┴┐├┤   ├─┘├─┤ │ ├─┤└─┐
 ┴ └─┘  ┴ ┴┴ ┴┴ ┴└─┘  ┴  ┴ ┴ ┴ ┴ ┴└─┘

 https://path.jerryio.com/

 1. click "file" in the top right
 2. click new file
 3. select the "static" folder in this project
 4. name the file
 5. create the path you want on the website
 6. put it as an asset below, (see line 35-40)
        example: ASSET(yourpathfile_txt)
 7. call the path using chassis.follow
        example: chassis.follow(yourpathfile_txt, 
                                timeout (do 2000), 
                                lookahead distance (do 15), 
                                isAsynchronous (should basically always be true), 
                                forwards (false makes the robot run the path backwards)
                 );
 8. call    chassis.waitUntilDist(-1);
     (this waits until the robot has finished the path)

*/

// THESE ARE THE PATH FILES, THE PATH FILES MUST BE IN THE 'static' FOLDER
// NO SD CARD REQUIRED
ASSET(leftsidequalsv3_txt)
ASSET(elimsLeftPath1_txt)
ASSET(elimsLeftPath2_txt)
ASSET(elimsLeftPath3_txt)
ASSET(elimsLeftPath4_txt)
ASSET(elimsLeftPath5_txt)
ASSET(pathjerryio_txt)


// function definitions

//       chassis.setPose(x, y, theta); 
//       chassis.turnTo(x, y, timeout);    
//       chassis.follow(path file, timeout, lookahead distance, isAsynchronous, forwards (false makes the robot run the path backwards));
//
//       chassis.waitUntilDist(inches); use this to have your bot wait until the path is finished
//       a really big number means just wait until the path has finished

//
// EXAMPLES OF 343X AUTOS BELOW:
//

// example auto for clearing matchload area and touching pole
void leftSideQual() {
    chassis.setPose(-48.428, -55.617, 135); // X: 0, Y: 0, Heading: 0

    // dropdown.set_value(true);
    chassis.turnTo(-11.918, -55.484, 500);    
    chassis.follow(leftsidequalsv3_txt, 2000, 15, true);
    chassis.waitUntilDist(3);
    // dropdown.set_value(false);
    chassis.waitUntilDist(-1);
}

// example auto for matchload elims
// for video check: https://www.youtube.com/live/bE180c_xft8?si=eTFYuLUq1aH28cv-&t=37856
void leftSideElims() {
    chassis.setPose(-42.009, -55.484, 15); // X: 0, Y: 0, Heading: 0

    chassis.follow(elimsLeftPath1_txt, 1000, 15, true);
    intakeOn();
    chassis.waitUntilDist(-1);

    pros::delay(300);

    chassis.follow(elimsLeftPath2_txt, 1000, 15, true, false);
    chassis.waitUntilDist(3);
    intake = 0;
    chassis.waitUntilDist(-1);
    pros::delay(350);

    chassis.turnTo(0, -15, 1000);  
    intakeReverse(); 
    pros::delay(500); 

    chassis.follow(elimsLeftPath3_txt, 1000, 15, true);
    chassis.waitUntilDist(-1);

    intake = 0;

    chassis.follow(elimsLeftPath4_txt, 1000, 15, true, false);
    chassis.waitUntilDist(-1);

    chassis.turnTo(0, -35, 1000);  

    chassis.follow(elimsLeftPath5_txt, 1000, 15, true, false);
    chassis.waitUntilDist(-1);
}

void skills() {
    // tee hee hidden
}