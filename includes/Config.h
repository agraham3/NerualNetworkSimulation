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
const int ROBOT_INFO_NUM = 8;
const int NUM_RADAR_CAN_SEE = 5;
const int LAYER_ZERO_SIZE = ROBOT_INFO_NUM + NUM_RADAR_CAN_SEE * 5;

const int NUM_ROBOTS = 2;
const int NUMBER_ROBOT_ACTIONS = 7;
const int ROBOT_ENERGY = 1500;
const double SEE_GAP = PI/32;

const int BULLET_TIMER = 15;
const int NUM_ROBOT_BULLETS = 15;
const int BULLET_COST = 10;

// Robot score/energy gain
const int ENERGY_GAIN = 200;
const int RADAR_SEE_OBJECTS = 4;
const int KILL_ROBOT = 500;
const int LOOKING_NEAR_ROBOT = 60;
const int SHOOT_NEAR_ROBOT = 120;
const int NEAR_CENTER = 40;
const int LAST_ONE_STANDING = 30;

// Robot socre/energy loss
const int STANDARD_ENERGY_LOSS = 1;
const int MOVE_ENERGY_LOSS = 5;
const int ROTATE_ENERGY_LOSS = 2;
const int SHOOTING_POINT_LOSS = 20;
const int RADAR_SHOOT_NO_ROBOT = 50;
const int ROBOT_DID_NOT_MOVE = 40;
const int ROBOT_HIT_WALL = 600;

// other
const int RESTART_TIMER = 50;
const int NUMBER_OF_ROUNDS = 5;

#endif
