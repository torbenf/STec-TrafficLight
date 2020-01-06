#include <TrafficLight.h>

typedef unsigned int State;
typedef enum {STATE_NO_STATE = 0, STATE_YELLOW_BLINK = 1, STATE_NORMAL_CYCLE = 2, STATE_PAUSE = 3, STATE_REST = 4} States;
State state = STATE_YELLOW_BLINK;
int numOfStates = 5;

TrafficLight trafficlight(7,8,9,2);

int led_green_pin = 7;
int led_yellow_pin = 8;
int led_red_pin = 9;

int YELLOW_BLINK_DELAY; 
int NORMAL_CYCLE_TIME;
unsigned long REST_AFTER;

int button_pin = 2;
int button_state_current = 1;
unsigned long last_button_press = 0;
unsigned long buttonTimer = 0;
unsigned long longPressTime = 1000;
unsigned long sysTime;
unsigned long pauseTime = 0;
unsigned long resumeTime = 0;

boolean buttonActive = false;
boolean longPressActive = false;

unsigned long yellow_blink_on = 0;
unsigned long yellow_blink_off = 0;

void yellowBlink(){
  trafficlight.setGreen(0);
  trafficlight.setRed(0);
  if (!trafficlight.getYellowState()) {
    if (sysTime - yellow_blink_off > YELLOW_BLINK_DELAY) {
      trafficlight.setYellow(1);
      yellow_blink_on = millis();
    }
  } else {
    if (sysTime - yellow_blink_on > YELLOW_BLINK_DELAY) {
      trafficlight.setYellow(0);
      yellow_blink_off = millis();
    }
  }
}

void normalCycle(unsigned long startTime){
  unsigned long time_frame = startTime % NORMAL_CYCLE_TIME;
  if (0 <= time_frame && time_frame <= (NORMAL_CYCLE_TIME / 10) * 3) { //red phase
    trafficlight.setLEDs(0,0,1);
  } else if ((NORMAL_CYCLE_TIME / 10) * 3 < time_frame && time_frame <= (NORMAL_CYCLE_TIME / 10) * 4) { // red yellow phase
    trafficlight.setLEDs(0,1,1);

  } else if ((NORMAL_CYCLE_TIME / 10) * 4 < time_frame && time_frame <= (NORMAL_CYCLE_TIME / 10) * 7) { //green phase
    trafficlight.setLEDs(1,0,0);

  } else if ((NORMAL_CYCLE_TIME / 10) * 7 < time_frame && time_frame <= NORMAL_CYCLE_TIME) { // yellow
    trafficlight.setLEDs(0,1,0);
  }
}

void pause(){
  trafficlight.setLEDs(trafficlight.getGreenState(), trafficlight.getYellowState(), trafficlight.getRedState());
}

void rest(){
  trafficlight.setLEDs(0,0,0);
}

void doSomething(int _state) {
  sysTime = millis();
  switch (_state) {
    case STATE_REST:
      rest();
      break;
    case STATE_YELLOW_BLINK:
      yellowBlink();
      break;
    case STATE_NORMAL_CYCLE:
      sysTime = millis() - (resumeTime - pauseTime); // to adjust the normal cycle for the time that passed in pause mode
      normalCycle(sysTime);
      break;
    case STATE_PAUSE:
      pause();
      break;
    default:
      trafficlight.setYellow(0);
  }
}

void setup() {
  // put your setup code here, to run once:
  last_button_press = millis();  
  YELLOW_BLINK_DELAY = trafficlight.getBlinkDelay(); 
  NORMAL_CYCLE_TIME = trafficlight.getCycleLength();
  REST_AFTER = trafficlight.getTimeout();
}

void loop() {
  button_state_current = trafficlight.getButtonState(); //read button state
  if (button_state_current == LOW && ((millis() - last_button_press) > 1000)) {
    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {
      //long press detected
      longPressActive = true;
      last_button_press = millis();
      state = STATE_YELLOW_BLINK;
    }

  } else {
    if (buttonActive == true) {
      if (longPressActive == true) {
        longPressActive = false;
      } else {
        //short press detected
        switch(state){
          case STATE_YELLOW_BLINK:
            state = STATE_NORMAL_CYCLE;
            break;
          case STATE_NORMAL_CYCLE:
            pauseTime = millis();            
            state = STATE_PAUSE;
            break;
          case STATE_PAUSE:
            resumeTime = millis();
            state = STATE_NORMAL_CYCLE;
            break;
          case STATE_REST:
            state = STATE_YELLOW_BLINK;
            break;
        }
        last_button_press = millis();
      }
      buttonActive = false;
    }
  }
  if((millis() - last_button_press) > REST_AFTER){
    state = STATE_REST;
  }
  doSomething(state);
}
