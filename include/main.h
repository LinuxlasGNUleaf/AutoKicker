#ifndef MAIN_H
#define MAIN_H

#include <TM1637Display.h>
#include <Arduino.h>

// pin config
const int pin_goal_team1 = D6;
const int pin_goal_team2 = D5;
const int pin_reset = D7;

const int pin_display_team1_clk = D2;
const int pin_display_team1_dio = D1;
const int pin_display_team2_clk = D4;
const int pin_display_team2_dio = D3;

// other config
const unsigned long DISPLAY_UPDATE_INTERVAL = 10;
const unsigned long MIN_MS_GOAL_SEPERATION = 500;

// variables 
volatile int goals_team1, goals_team2;
volatile unsigned long last_goal1_ts, last_goal2_ts;
bool update, state_goal_team1, state_goal_team2;

void setup();
void loop();
void displayGoals();
void resetGame();

#endif