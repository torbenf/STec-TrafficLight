typedef unsigned int Set;
typedef enum {STATE_NO_STATE = 0, STATE_YELLOW_BLINK = 1, STATE_NORMAL_CYCLE = 2, STATE_PAUSE = 4, STATE_REST = 8} State;
Set state = STATE_YELLOW_BLINK;

// constants won't change. Used here to set the pin numbers:
const int led_green_pin = 7;
const int led_yellow_pin = 8;
const int led_red_pin = 9;

const int button_pin = 2;

// Variables will change:
//led states to set the LEDs
int led_green_state = LOW;
int led_yellow_state = LOW;
int led_red_state = LOW;

int  button_state = HIGH;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

volatile boolean interrupted = false;
volatile long last_interrupt = 0;
const int interrupt_delay = 200;

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

void set_interrupt() {
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt >= interrupt_delay) {
    last_interrupt = interrupt_time;
    interrupted = true;
    if(state & STATE_PAUSE){
      interrupted = false;
    }
  }
}


  //sets the global state variable to the desired state
  Set change_state(State new_state) {
    Serial.print("Old State was: ");
    Serial.println(state, BIN);
    Set my_state = new_state;
    Serial.print("New State is: ");
    Serial.println(new_state, BIN);
    return my_state;
  }

  //pauses the normal cycle until button is pressed again
  void pause() {
    Serial.println("PAUSE");
    state = change_state(STATE_PAUSE);
    while (interrupted) {
    }
    interrupted = false;
    state = change_state(STATE_NORMAL_CYCLE);
  }

  //normal traffic light cycle:
  //red, red/yellow, green, yellow, red
  void normal_cycle() {
    if (!interrupted) {
      digitalWrite(led_red_pin, LOW);
      digitalWrite(led_yellow_pin, LOW);
      digitalWrite(led_green_pin, LOW);

      digitalWrite(led_red_pin, HIGH);
      delay(1000);
      pause();
      digitalWrite(led_yellow_pin, HIGH);
      delay(1000);
      pause();
      digitalWrite(led_red_pin, LOW);
      digitalWrite(led_yellow_pin, LOW);
      digitalWrite(led_green_pin, HIGH);
      delay(1000);
      pause();
      digitalWrite(led_green_pin, LOW);
      digitalWrite(led_yellow_pin, HIGH);
      delay(1000);
      pause();
      digitalWrite(led_yellow_pin, LOW);
      pause();
      digitalWrite(led_red_pin, HIGH);
      delay(1000);
    } else {
      interrupted = false;
    }
    Serial.println("Done");

  }

  void yellow_blink(int interval) {
    while (!interrupted) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        if (led_yellow_state == LOW) {
          led_yellow_state = HIGH;
        } else {
          led_yellow_state = LOW;
        }
        digitalWrite(led_yellow_pin, led_yellow_state);
      }
    }
    interrupted = false;
    led_yellow_state = LOW;
    state = change_state(STATE_NORMAL_CYCLE);
    Serial.println("Done");
  }

  void setup() {
    // set the digital pin as output:
    pinMode(led_green_pin, OUTPUT);
    pinMode(led_yellow_pin, OUTPUT);
    pinMode(led_red_pin, OUTPUT);

    //set button_pin as input and sets internal pullup resisitor
    pinMode(button_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(button_pin), set_interrupt, FALLING);
    Serial.begin(9600);
  }

  void loop() {

    Serial.println("Choosing state");
    if (state & STATE_YELLOW_BLINK) {
      Serial.println("state YELLOW BLINK");
      yellow_blink(1000);
    } else if (state & STATE_NORMAL_CYCLE) {
      Serial.println("state NORMAL_CYLCE");
      normal_cycle();
    } else if (state & STATE_PAUSE) {
      Serial.println("state PAUSE");
      pause();
    }
  }
