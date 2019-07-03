/*
* @author Ryan Nicholas
* This is the user control mode
*/

#include "main.h"

using namespace pros;

//Initialize Master Controller
Controller master(pros::E_CONTROLLER_MASTER);

// Motor Ports
const int frontLeftPort = 1;
const int backLeftPort = 2;
const int frontRightPort = 3;
const int backRightPort = 4;
const int liftPort = 5;
const int cubeIntakePort = 6;

//Sensor and Pnuematic Ports
const int PneumaticsPort = 1;

//Initialize Motors
Motor frontLeftWheel(frontLeftPort, true);
Motor backLeftWheel(backLeftPort, true);
Motor frontRightWheel(frontRightPort, false);
Motor backRightWheel(backRightPort, false);
Motor lift(liftPort, false);
Motor cubeIntake(cubeIntakePort, false);

//Initialize Senosrs and Pneumatics
ADIPort Pneumatics(PneumaticsPort, E_ADI_DIGITAL_OUT);


/*
* Left Drive
*/
void LeftDrive(int power)
{
	frontLeftWheel.move(power);
	backLeftWheel.move(power);
}

/*
* Right Drive
*/
void RightDrive(int power)
{
	frontRightWheel.move(power);
	backRightWheel.move(power);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {


	while (true) {

		// Left Stick and Right Stick
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		// Left side of drive chain
		if (abs(left) > 10)
		{
			LeftDrive(left);
		}
		else {
			LeftDrive(0);
		}

		// Right side of drive chain
		if (abs(right) > 10)
		{
			RightDrive(right);
		}
		else {
			RightDrive(0);
		}

		// Controls the lift
		if (master.get_digital(DIGITAL_R1))
		{
			lift.move(100);
		}
		else if (master.get_digital(DIGITAL_R2))
		{
			lift.move(-100);
		}
		else {
			lift.set_brake_mode(MOTOR_BRAKE_HOLD);
			lift.move_velocity(0);
		}

		//controls cube intake
		if (master.get_digital(DIGITAL_L1))
		{
			cubeIntake.move(100);
		}
		else if (master.get_digital(DIGITAL_L2))
		{
			cubeIntake.move(-100);
		}
		else {
			cubeIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
			cubeIntake.move_velocity(0);
		}

		//Gave ability to move Pneumatics
		if (master.get_digital(DIGITAL_X))
		{
			Pneumatics.set_value(HIGH);
		}
		else {
			Pneumatics.set_value(LOW);
		}

		pros::delay(20);
	}
}
