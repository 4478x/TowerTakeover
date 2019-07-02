/*
* @author Ryan Nicholas
* This is the user control mode
*/

#include "main.h"

using namespace pros;

// Motor Ports
const int frontLeftPort = 1;
const int backLeftPort = 2;
const int frontRightPort = 3;
const int backRightPort = 4;
const int liftPort = 5;
const int cubeIntakePort = 6;

Motor frontLeftWheel(frontLeftPort, false);
Motor backLeftWheel(backLeftPort, false);
Motor frontRightWheel(frontRightPort, true);
Motor backRightWheel(backRightPort, true);
Motor lift(liftPort, false);
Motor cubeIntake(cubeIntakePort, false);

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

	pros::Controller master(pros::E_CONTROLLER_MASTER);

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

		pros::delay(20);
	}
}
