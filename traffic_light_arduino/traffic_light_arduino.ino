typedef unsigned int State;
typedef enum {STATE_NO_STATE = 0, STATE_YELLOW_BLINK = 1, STATE_NORMAL_CYCLE = 2, STATE_PAUSE = 3, STATE_REST = 4} States;
State state = STATE_YELLOW_BLINK;
int numOfStates = 5;

int led_green_pin = 7;
int led_yellow_pin = 8;
int led_red_pin = 9;

const int YELLOW_BLINK_DELAY = 500;
const int NORMAL_CYCLE_TIME = 10000; //3s green; 3s yellow; 3s red; 1s red/yellow

int button_pin = 2;
int button_state_current = 1;
unsigned long last_button_press = 0;
unsigned long buttonTimer = 0;
unsigned long longPressTime = 1000;

boolean buttonActive = false;
boolean longPressActive = false;

unsigned long yellow_blink_on = 0;
unsigned long yellow_blink_off = 0;

void activateLEDs(int green, int yellow, int red) {
  digitalWrite(led_green_pin, green);
  digitalWrite(led_yellow_pin, yellow);
  digitalWrite(led_red_pin, red);
}

void doSomething(int _state) {
  //Serial.println("Choosing");
  unsigned long theTime = millis();
  switch (_state) {
    case STATE_NO_STATE:
      ;
    case STATE_YELLOW_BLINK:
      //Serial.println("YELLOW_BLINK");
      digitalWrite(led_green_pin, LOW);
      digitalWrite(led_red_pin, LOW);
      if (!digitalRead(led_yellow_pin)) {
        if (theTime - yellow_blink_off > YELLOW_BLINK_DELAY) {
          digitalWrite(led_yellow_pin, HIGH);
          yellow_blink_on = millis();
        }
      } else {
        if (theTime - yellow_blink_on > YELLOW_BLINK_DELAY) {
          digitalWrite(led_yellow_pin, LOW);
          yellow_blink_off = millis();
        }
      }
      break;
    case STATE_NORMAL_CYCLE:
      //Serial.println("NORMAL_CYLCE");

      int time_frame = theTime % NORMAL_CYCLE_TIME;

      if (0 <= time_frame && time_frame <= (NORMAL_CYCLE_TIME / 10) * 3) { //red phase
        activateLEDs(0, 0, 1);

      } else if ((NORMAL_CYCLE_TIME / 10) * 3 < time_frame && time_frame <= (NORMAL_CYCLE_TIME / 10) * 4) { // red yellow phase
        activateLEDs(0, 1, 1);

      } else if ((NORMAL_CYCLE_TIME / 10) * 4 < time_frame && time_frame <= (NORMAL_CYCLE_TIME / 10) * 7) { //green phase
        activateLEDs(1, 0, 0);

      } else if ((NORMAL_CYCLE_TIME / 10) * 7 < time_frame && time_frame <= NORMAL_CYCLE_TIME) { // yellow
        activateLEDs(0, 1, 0);
      }
      break;
    case STATE_PAUSE:
      int green_led = digitalRead(led_green_pin);
      int yellow_led = digitalRead(led_yellow_pin);
      int red_led = digitalRead(led_red_pin);

      activateLEDs(green_led, yellow_led, red_led);

    default:
      digitalWrite(led_yellow_pin, LOW);
      //Serial.println("DEFAULT");
  }
}

void setup() {
  // set the digital pin as output:
  pinMode(led_green_pin, OUTPUT);
  pinMode(led_yellow_pin, OUTPUT);
  pinMode(led_red_pin, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);
  last_button_press = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  button_state_current = digitalRead(button_pin);
  if (button_state_current == LOW && ((millis() - last_button_press) > 1000)) {
    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {
      //long press detected
      longPressActive = true;
      last_button_press = millis();
      Serial.println("long press detected");
      state = STATE_YELLOW_BLINK;
    }

  } else {
    if (buttonActive == true) {
      if (longPressActive == true) {
        longPressActive = false;
      } else {
        //short press detected
        state++;
        state = state % numOfStates;
        last_button_press = millis();
        Serial.println("short press detected");
        Serial.println(state);
      }
      buttonActive = false;
    }
  }
  doSomething(state);
}
