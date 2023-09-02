#include <TM1637Display.h>
#include <Arduino.h>

const int pin_goal_team1 = D6;
const int pin_goal_team2 = D7;
const int pin_reset = D7;

TM1637Display display_team1(D2, D3);
TM1637Display display_team2(D5, D0);

bool state_goal_team1 = true, state_goal_team2 = true;
int goals_team1 = 0, goals_team2 = 0;

void displayGoals();

void setup() {
  // put your setup code here, to run once:
  display_team1.setBrightness(7, true);
  display_team2.setBrightness(7, true);
  display_team1.clear();
  display_team2.clear();

  pinMode(pin_goal_team1, INPUT);
  pinMode(pin_goal_team2, INPUT);
  pinMode(pin_reset, INPUT_PULLUP);
  displayGoals();

  Serial.begin(9600);
}

bool update = false;
void loop() {
  if (digitalRead(pin_reset) == LOW)
  {
    goals_team1 = 0;
    goals_team2 = 0;
    displayGoals();
    return;
  }
  
  if (digitalRead(pin_goal_team1) != state_goal_team1)
  {
    if (state_goal_team1)
      goals_team2++;
    state_goal_team1 = !state_goal_team1;
    update = true;
  }

  if (digitalRead(pin_goal_team2) != state_goal_team2)
  {
    if (state_goal_team2)
      goals_team1++;
    state_goal_team2 = !state_goal_team2;
    update = true;
  }

  if (update)
  {
    displayGoals();
    update = false;
  }
}

// put function definitions here:
void displayGoals() {
  display_team1.showNumberDecEx(goals_team1, 0b01000000, true, 2, 0);
  display_team1.showNumberDec(goals_team2, true, 2, 2);
  display_team2.showNumberDecEx(goals_team2, 0b01000000, true, 2, 0);
  display_team2.showNumberDec(goals_team1, true, 2, 2);
}