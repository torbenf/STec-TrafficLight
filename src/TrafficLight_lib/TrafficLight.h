/*
	Traffic.h - Library for operating a traffic light
	Created by Torben Fritsch, Januaray 1, 2020.
*/
#ifndef TrafficLight_h
#define TrafficLight_h

#include "Arduino.h"


class TrafficLight
{
	public:
	  TrafficLight(int green, int yellow, int red, int buttonPin);
	  int getButtonState();
	  void setTimeout(int millis);
	  void setBlinkDelay(int millis);
	  void setCycleLength(int millis);
	  long getTimeout();
	  long getBlinkDelay();
	  long getCycleLength();
	  
	  void activateLEDs(bool green, bool yellow, bool red);
	  void setGreen(bool state);
	  void setYellow(bool state);
	  void setRed(bool state);
	  bool getGreenState();
	  bool getYellowState();
	  bool getRedState();
	  bool getButtonState();

	private:
		int _led_green_pin;
		int _led_yellow_pin;
		int _led_red_pin;
		int _button_pin;
}

#endif