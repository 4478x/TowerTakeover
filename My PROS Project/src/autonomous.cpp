/*
* @author Ryan Nicholas
* This is the autonomous code
*/

#include "main.h"
#include "AutonCode/Auton1.cpp"
#include "AutonCode/Auton2.cpp"
#include "AutonCode/Auton3.cpp"
#include "AutonCode/Auton4.cpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

  if (AutoMode == 1)
  {
    //Auotnomous 1
    Auton1();
  }
  else if (AutoMode == 2)
  {
    //Autonomous 2
    Auton2();
  }
  else if (AutoMode == 3)
  {
    //Autonomous 3
    Auton3();
  }
  else {
    //Autonomous 4
    Auton4();
  }

}
