# TrafficLight :vertical_traffic_light: 	
TrafficLight is a project for learing how to structure a software assigment. It consists of arduino source code, the trafficLight library and the documentation.
With the right hardware (3 LEDs and a pushbutton) it can simulate a traffic light.


# Functionality
The user can set all LEDs and the cycle- , timeout-, and blinkdelaytime. It is also possible to get all states from all PINs via the lib.<br>

- Traffic light hardware operations are outsourced in the librarayy  
  
The traffic light logic is based on 4 states:<br>
- Yellow blinking
- Normal cycle
- Pause
- Rest

The states change according to this graph:<br><br>
![flowchart](https://github.com/torbenf/STec-TrafficLight/blob/master/doc/additional_files/flowchart.png)


# How to use
  - Clone the repository
	```bash
	git clone https://github.com/torbenf/STec-TrafficLight.git
	```
  - Copy the library folder into the Arduino library directory to use it inside the Arduino IDE.
  - Connect the three LEDs and the pushbutton to an ardunio of your choice. This is an example wiring diagram:
  <br>
  	- The LEDs are connected to Pin 7 (green), 8 (yellow) and 9 (red) <br>
  	- The button is connected to Pin 2 with an *INTERNAL PULLUP RESISTOR*
  <br>
  
  ![wiring](https://github.com/torbenf/STec-TrafficLight/blob/master/doc/additional_files/wiring_diagram.PNG)
  
  <br>
  
  - By constructing a trafficlight instance in a scetch you define the pins used for the LEDs and the button:<br>
TrafficLight trafficlight([green_LED], [yellow_LED], [red_LED], [button_pin]) <br>--> see traffic_light_arduino scetch inside src

  ENJOY! :green_heart:



