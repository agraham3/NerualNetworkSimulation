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
const int NUM_ACTIONS = 5;
const int NUM_RADAR_CAN_SEE = 5;
const int LAYER_ZERO_SIZE = NUM_ACTIONS + NUM_RADAR_CAN_SEE * 2;

// Math const
const double PI = 3.1415926535;
const double TAU = 2 * PI;

// other
const int NUM_ROBOTS = 10;
const int RESTART_TIMER = 50;
// This is bonus points for killing a robot because frames lived is a very large number.
// My idea is that if I did not do this, the robot would learn that living longer is more important
// than killing other robots. So, I wanted to increase the point value for killing in such a way that
// the robot would find it just as "important" to kill the other robots. Or at least make killing the other
// robots a valid option.
const int POINT_BOOSTER = 100;

#endif
