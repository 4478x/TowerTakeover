/*
* @author Ryan Nicholas
* This will contain the code for autonomous 2
*/
#include "main.h"

using namespace okapi;

float LiftkP = 1;
float LiftkI = .0001;
float LiftkD = 0.1;

auto drive = ChassisControllerFactory::create({frontLeftPort, backLeftPort}, {frontRightPort, backRightPort});
//auto lift = AsyncControllerFactory::posPID(liftPort, LiftkP, LiftkI, LiftkD);

auto lift = AsyncControllerFactory::posPID({leftLiftPort, -rightLiftPort}, LiftkP, LiftkI, LiftkD);

void Auton4()
{
  //Move Forward and lift at the same time
  drive.moveDistanceAsync(1000); //Moves 1000 motor degrees
  lift.setTarget(200);
  drive.waitUntilSettled(); //Waits until drive has stopped moving before moving to next task

}
