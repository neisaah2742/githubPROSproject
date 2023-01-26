
#ifndef _CHASSIS_H_
#define _CHASSIS_H_

//sets speeds of motors
void chassisSet(int left, int right) {
    motorSet(2, left); //frontLeft
    motorSet(3, left); //backLeft
    motorSet(4, right); //backRight
    motorSet(5, right); //frontRight
    printf("right speed %d left speed %d \n", right, left);
}


#endif // _CHASSIS_H_
