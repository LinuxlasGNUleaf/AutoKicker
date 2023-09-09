#include <main.h>

TM1637Display display_team1(pin_display_team1_clk, pin_display_team1_dio);
TM1637Display display_team2(pin_display_team2_clk, pin_display_team2_dio);

void setup() {
  Serial.begin(9600);
  display_team1.setBrightness(7, true);
  display_team2.setBrightness(7, true);
  display_team1.clear();
  display_team2.clear();

  pinMode(pin_goal_team1, INPUT);
  pinMode(pin_goal_team2, INPUT);
  pinMode(pin_reset, INPUT_PULLUP);

  resetGame();
  displayGoals();
  state_goal_team1 = digitalRead(pin_goal_team1);
  state_goal_team2 = digitalRead(pin_goal_team2);
}

void loop() {
  if (digitalRead(pin_reset) == LOW) {
    resetGame();
    return;
  }

  if (digitalRead(pin_goal_team1) != state_goal_team1) {
    if (state_goal_team1) {
      goals_team2++;
      update = true;
    }
    state_goal_team1 = !state_goal_team1;
  }

  if (digitalRead(pin_goal_team2) != state_goal_team2) {
    if (state_goal_team2) {
      goals_team1++;
      update = true;
    }
    state_goal_team2 = !state_goal_team2;
  }

  if (update) {
    displayGoals();
    update = false;
  }
}

// put function definitions here:
void displayGoals() {
  uint8_t dot_mask = 0b01000000;

  int goals1_offset = goals_team1 < 10;
  int goals2_offset = goals_team2 < 10;

  uint8_t emptySegments[2] = {0, 0};
  uint8_t emptySegmentsWithColon[2] = {0, SEG_DP};

  if (state_goal_team1) {
    display_team1.setSegments(emptySegmentsWithColon, 2, 0);
    display_team2.setSegments(emptySegments, 2, 2);
  }

  if (state_goal_team2) {
    display_team2.setSegments(emptySegmentsWithColon, 2, 0);
    display_team1.setSegments(emptySegments, 2, 2);
  }

  if (state_goal_team1 || state_goal_team2)
  {
    delay(20);
  }

  display_team1.showNumberDecEx(goals_team1, dot_mask, false, 2, 0);
  display_team2.showNumberDec(goals_team1, false, (2 - goals1_offset), 2);

  display_team2.showNumberDecEx(goals_team2, dot_mask, false, 2, 0);
  display_team1.showNumberDec(goals_team2, false, (2 - goals2_offset), 2);
}

void resetGame() {
  update = true;
  goals_team1 = 0;
  goals_team2 = 0;
  display_team1.clear();
  display_team2.clear();
}