/*
	Traffic.h - Library for operating a traffic light
	Created by Torben Fritsch, Januaray 1, 2020.
*/

#include "Arduino.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight(int green, int yellow, int red, int buttonPin)
{
	pinMode(green, OUTPUT);
	pinMode(yellow, OUTPUT);
	pinMode(red, OUTPUT);
	pinMode(button_pin, INPUT_PULLUP);
	_led_green_pin = green;
	_led_yellow_pin = yellow;
	_led_red_pin = red;
	_button_pin = buttonPin;
}

void TrafficLight::setLEDs(bool green, bool yellow, bool red){
	digitalWrite(_led_green_pin, green);
	digitalWrite(_led_yellow_pin, yellow);
	digitalWrite(_led_red_pin, red);
}

void TrafficLight::setGreen(bool state){
	digitalWrite(_led_green_pin, state);
}

void TrafficLight::setYellow(bool state){
	digitalWrite(_led_yellow_pin, state);
}

void TrafficLight::setRed(bool state){
	digitalWrite(_led_red_pin, state);
}

bool TrafficLight::getGreenState(){
	return digitalRead(_led_green_pin);
}

bool TrafficLight::getYellowState(){
	return digitalRead(_led_yellow_pin);
}

bool TrafficLight::getRedState(){
	return digitalRead(_led_red_pin);
}

bool TrafficLight::getButtonState(){
	return digitalRead(_button_pin);
}