# TrafficLight
TrafficLight is a project for learing how to structure a software assigment. It consists of arduino source code, the trafficLight library and the documentation.
With the right hardware (3 LEDs and a pushbutton) it can simulate a traffic light.


# Functionality
The user can set all LEDs and the cycle- , timeout-, and blinkdelaytime. It is also possible to get all states from all PINs via the lib.<br>

- Traffic light hardware operations inside the libraray:
	- void setTimeoutAfter(long millis);
	- void setBlinkDelay(long millis);
	- void setCycleLength(long millis);
	- long getTimeout();
	- long getBlinkDelay();
	- long getCycleLength();
	- void setLEDs(bool green, bool yellow, bool red);
	- void setGreen(bool state);
	- void setYellow(bool state);
	- void setRed(bool state);
	- bool getGreenState();
	- bool getYellowState();
	- bool getRedState();
	- bool getButtonState();
  
  
The traffic light logic is based on 4 states:<br>
- Traffic light logic inside traffic_light_arduino scetch:
	- void yellowBlink();
	- void normalCycle(unsigned long startTime);
	- void pause();
	- void rest();

The states change according to this graph:
![flowchart](/doc/addition_files/flowchart.png)


# How to use
  - Copy the library folder into the Arduino library directory to use it inside the Arduino IDE.
  - Connect the three LEDs and the pushbutton to an ardunio of your choice.

  - By constructing a trafficlight instance in a scetch you define the pins used for the LEDs and the button:<br>
[green_LED, yellow_LED, red_LED, button_pin] --> see traffic_light_arduino scetch inside src



