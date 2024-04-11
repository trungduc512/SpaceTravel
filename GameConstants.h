#ifndef GAMECONSTANTS_H_INCLUDED
#define GAMECONSTANTS_H_INCLUDED

#include <SDL.h>

const int ACTUAL_WINDOW_WIDTH = 1280;
const int ACTUAL_WINDOW_HEIGHT = 720;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float MOUSE_Y_CONVERT_RATE = (float)SCREEN_HEIGHT / (float)ACTUAL_WINDOW_HEIGHT;
const float MOUSE_X_CONVERT_RATE = (float)SCREEN_WIDTH / (float)ACTUAL_WINDOW_WIDTH;
const int SPACESHIP_MOVE_SPEED = 15;
const int COIN_POINT = 100;
const int OBSTACLE_BREAK_POINT = 50;
const int BOSS_DEFEAT_POINT = 1000;
const int SHOOT_COOLDOWN = 100;
const int TIME_TO_NEXT_LEVEL = 10;
const int SCORE_TO_SPEED_UP = 1500;
const int MAX_OBSTACLE_SPEED = 15;
const int BOSS_BULLET_SPEED = 15;
const int MIN_OBSTACLE_SPAWN_RATE = 8;
const int INIT_OBSTACLE_SPAWN_RATE = 25;
const int INIT_OBSTACLE_MOVE_SPEED = 10;
const int LASER_SPAWN_RATE = 900; //900
const int BOSS_SPAWN_TIME = 30;//30
const int BOSS_SHOOT_RATE = 45;
const int LASER_DURATION = 500;
const int WARNING_TIME = 2000;
const int SCORE_BOARD_X_POS = 10;
const int SCORE_BOARD_Y_POS = 10;
const int FPS = 60;
const int DELAY_TIME = 1000/FPS;
const unsigned int COIN_SPAWN_RATE = 100;
const unsigned int STAR_SPAWN_RATE = 2;
const unsigned int LARGE_STAR_SPAWN_RATE = 3;
const unsigned int BACKGROUND_SPAWN_RATE = 150;
const unsigned int POWERUPS_SPAWN_RATE = 5;
const unsigned int BOSS_BASE_HEALTH = 20;
const unsigned int BOSS_SCALE_HEALTH = 8;
const float BOSS_MIN_Y_POS = 200;

#endif // GAMECONSTANTS_H_INCLUDED
