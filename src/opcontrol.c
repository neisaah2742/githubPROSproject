/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "chassis.h"
Ultrasonic leftSonar;
Ultrasonic rightSonar;

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
int joystickGetAnalog (
	unsigned char joystick,
	unsigned char axis
);

void motorSet (
	unsigned char channel,
	int speed
);

void initialize() {
    rightSonar = ultrasonicInit(2, 1);
    leftSonar = ultrasonicInit(4, 3);
}

void chassisSet(int left, int right);

void operatorControl() {
	int power;
	int turn;
	//installing TWO ultrasonic sensors will allow us to determine if the object is to the right or left of the robot
	int distanceRight;
	int distanceLeft;
	while (1) {
		power = joystickGetAnalog(1, 2);
		turn = joystickGetAnalog(1, 1);
		chassisSet(power+turn, power-turn);
		if (joystickGetDigital(1, 8, JOY_RIGHT)) {
			distanceRight = ultrasonicGet(rightSonar);
			distanceLeft = ultrasonicGet(leftSonar);
			//printf("the distance to the object is %d", distanceToObject);
			//only go completely forward or completely back if the object is right in front of the robot
			if (distanceRight == distanceLeft) {
				if (distanceRight > 20) {
					chassisSet(100, 100);
				}
				else if (distanceRight < 20) {
					chassisSet(-100, -100);
				}
				else {
					chassisSet(0, 0);
				}
			}
			else if (distanceRight < distanceLeft) {
				// this means the object is to the right of the robot
				// left motors should run forward while right motors run back (not at full speed)
				chassisSet(50, -50);
			}
			else if (distanceRight < distanceLeft) {
				// object is to the left of the robot
				// right motors should run forward while left motors run back (not at full speed)
				chassisSet(-50, 50);
			}
		}
		delay(50);
	}
}
