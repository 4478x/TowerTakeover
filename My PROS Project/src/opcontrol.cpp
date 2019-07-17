/*
* @author Ryan Nicholas
* This is the user control mode
*/

#include "main.h"

using namespace pros;

//Initialize Master Controller
Controller master(pros::E_CONTROLLER_MASTER);

//Initialize Motors
Motor frontLeftWheel(frontLeftPort, true); //left wheels
Motor backLeftWheel(backLeftPort, true);
Motor midLeftWheel(midLeftPort, true);
Motor frontRightWheel(frontRightPort, false); //right wheels
Motor backRightWheel(backRightPort, false);
Motor midRightWheel(midRightPort, false);
Motor leftLift(leftLiftPort, false); //lift
Motor rightLift(rightLiftPort, false);
Motor leftCubeIntake(leftCubeIntakePort, false); //cube intake
Motor rightCubeIntake(rightCubeIntakePort, false);
Motor rightOutake(rightCubeTransferPort, false); //Transfer cubes into zone
Motor leftOutake(leftCubeTransferPort, false);

//Initialize Senosrs and Pneumatics
ADIPort Pneumatics(PneumaticsPort, E_ADI_DIGITAL_OUT);


/*
* Left Drive
*/
void LeftDrive(int power)
{
	if (abs(power) > 7)
	{
		frontLeftWheel.move(power);
		midLeftWheel.move(power);
		backLeftWheel.move(power);
	}
	else {
		frontLeftWheel.move_velocity(0);
		midLeftWheel.move_velocity(0);
		backLeftWheel.move_velocity(0);
	}
}

/*
* Right Drive
*/
void RightDrive(int power)
{
	if (abs(power) > 7)
	{
		frontRightWheel.move(power);
		midRightWheel.move(power);
		backRightWheel.move(power);
	}
	else {
		frontRightWheel.move_velocity(0);
		midRightWheel.move_velocity(0);
		backRightWheel.move_velocity(0);
	}
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
			leftLift.move(100);
			rightLift.move(-100);
		}
		else if (master.get_digital(DIGITAL_R2))
		{
			leftLift.move(-100);
			rightLift.move(100);
		}
		else {
			leftLift.set_brake_mode(MOTOR_BRAKE_HOLD);
			rightLift.set_brake_mode(MOTOR_BRAKE_HOLD);

			leftLift.move_velocity(0);
			rightLift.move_velocity(0);
		}

		//controls cube intake
		if (master.get_digital(DIGITAL_L1))
		{
			leftCubeIntake.move(100);
			rightCubeIntake.move(-100);
		}
		else if (master.get_digital(DIGITAL_L2))
		{
			leftCubeIntake.move(-100);
			rightCubeIntake.move(100);
		}
		else {
			leftCubeIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
			leftCubeIntake.move_velocity(0);

			rightCubeIntake.set_brake_mode(MOTOR_BRAKE_HOLD);
			rightCubeIntake.move_voltage(0);
		}

		//Gave ability to move Pneumatics
		if (master.get_digital(DIGITAL_X))
		{
			Pneumatics.set_value(HIGH);
		}
		else {
			Pneumatics.set_value(LOW);
		}

		if (master.get_digital(DIGITAL_DOWN))
		{
			rightOutake.move(-100);
			leftOutake.move(100);
		}
		else if (master.get_digital(DIGITAL_UP))
		{
			rightOutake.move(100);
			leftOutake.move(-100);
		}
		else {
			rightOutake.move_velocity(0);
			leftOutake.move_velocity(0);
		}

		pros::delay(20);
	}
}
