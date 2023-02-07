
#include "main.h"
#include "chassis.h"

void chassisSet(int left, int right) {
    motorSet(2, left * -1); //frontLeft
    motorSet(3, left * -1); //backLeft
    motorSet(4, right); //backRight
    motorSet(5, right * -1); //frontRight
    printf("right speed %d left speed %d \n", right, left);
}
