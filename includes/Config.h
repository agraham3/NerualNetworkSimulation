#ifndef CONFIG_H
#define CONFIG_H

// Math const
const double PI = 3.1415926535;
const double TAU = 2 * PI;

// Window info / Game frames
char* const TITLE = "Nerual Network Simulation";

const int HEIGHT = 600;
const int WIDTH = 600;
const int FRAMES_PER_SEC = 30;

// Robot info (standard size): 5
// Num of objects able to be detected by the radar: 5
//    Note: I can see n objects however I push back an x and a y
//    so 5 * 2 = 10
const int ROBOT_INFO_NUM = 6;
const int NUM_RADAR_CAN_SEE = 5;
const int LAYER_ZERO_SIZE = ROBOT_INFO_NUM + NUM_RADAR_CAN_SEE * 5;

const int NUMBER_ROBOT_ACTIONS = 7;
const int ROBOT_ENERGY = 1500;
const double SEE_GAP = PI/16;

const int BULLET_TIMER = 15;
const int NUM_ROBOT_BULLETS = 20;
const int BULLET_COST = 8;

// Robot score/energy gain
const int ENERGY_GAIN = 200;
const int RADAR_SEE_OBJECTS = 10;
const int KILL_ROBOT = 300;
const int LOOKING_NEAR_ROBOT = 20;
const int SHOOT_NEAR_ROBOT = 200;
const int NEAR_CENTER = 20;

// Robot socre/energy loss
const int STANDARD_ENERGY_LOSS = 1;
const int MOVE_ENERGY_LOSS = 6;
const int ROTATE_ENERGY_LOSS = 3;
const int SHOOTING_POINT_LOSS = 40;
const int RADAR_SHOOT_NO_ROBOT = 100;
const int ROBOT_DID_NOT_MOVE = 100;
const int SAME_DIRECTION = 50;
const int ROBOT_HIT_WALL = 60000;
const int DIED_BY_BULLET = 800;

// other
const int RESTART_TIMER = 50;

#endif
