#ifndef CONFIG_H
#define CONFIG_H

// Window info / Game frames
char* const TITLE = "Nerual Network Simulation";

const int HEIGHT = 600;
const int WIDTH = 600;
const int FRAMES_PER_SEC = 20;

// Robot info (standard size): 5
// Num of objects able to be detected by the radar: 5
//    Note: I can see n objects however I push back an x and a y
//    so 5 * 2 = 10
const int ROBOT_INFO_NUM = 7;
const int NUM_RADAR_CAN_SEE = 5;
const int LAYER_ZERO_SIZE = ROBOT_INFO_NUM + NUM_RADAR_CAN_SEE * 2;

const int NUM_ROBOTS = 6;
const int NUMBER_ROBOT_ACTIONS = 7;
const int ROBOT_ENERGY = 350;
const int NUM_ROBOT_BULLETS = 5;

// Math const
const double PI = 3.1415926535;
const double TAU = 2 * PI;

// other
const int RESTART_TIMER = 50;
const int POINT_BOOSTER = 100;

#endif
