typedef unsigned int Set;
typedef enum {STATE_NO_STATE = 0, STATE_YELLOW_BLINK = 1, STATE_NORMALCYCLE = 2, STATE_PAUSE = 4, STATE_REST = 8} State;
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

//boolean for first run
boolean first = true;

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

//normal traffic light cycle:
//red, red/yellow, green, yellow, red
void normal_cycle(){  
  digitalWrite(led_red_pin, LOW);
  digitalWrite(led_yellow_pin, LOW);
  digitalWrite(led_green_pin, LOW);
  
  digitalWrite(led_red_pin, HIGH);
  delay(1000);
  
  digitalWrite(led_yellow_pin, HIGH);
  delay(1000);
  
  digitalWrite(led_red_pin, LOW);
  digitalWrite(led_yellow_pin, LOW);
  digitalWrite(led_green_pin, HIGH);
  delay(1000);
  
  digitalWrite(led_green_pin, LOW);
  digitalWrite(led_yellow_pin, HIGH);
  delay(1000);
  
  digitalWrite(led_yellow_pin, LOW);
  
  state = STATE_NO_STATE;
  state |= STATE_YELLOW_BLINK;
  Serial.println("Done");

}

void yellow_blink(int interval){
  button_state = digitalRead(button_pin);
  while(button_state == 1){
    button_state = digitalRead(button_pin);
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
  state = STATE_NO_STATE;
  state |= STATE_NORMALCYCLE;
  led_yellow_state = LOW;  
  Serial.println("Done");
}

void setup() {
  // set the digital pin as output:
  pinMode(led_green_pin, OUTPUT);
  pinMode(led_yellow_pin, OUTPUT);
  pinMode(led_red_pin, OUTPUT);

  //set button_pin as input
  pinMode(button_pin, INPUT);
  //set internal pull up resistor
  digitalWrite(button_pin, HIGH);

  Serial.begin(9600);
}

void loop() {

  Serial.println("Choosing state");
  if(state & STATE_YELLOW_BLINK){
    Serial.println("state YELLOW BLINK");
    yellow_blink(1000);
  }else if(state & STATE_NORMALCYCLE){
    Serial.println("state NORMAL_CYLCE");
    normal_cycle();
  }
}
