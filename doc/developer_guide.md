The sketch in /src/ is a fully working example that can easily be edited.

The user can set all LEDs and the cycle- , timeout-, and blinkdelaytime. It is also possible to get all states from all PINs via the lib.

The Library supports the folowing functions:

| Function                                          | Description   | 
| --------------------------------------------------|:-------------:|
| void setTimeoutAfter(long millis)                 | Sets the time in millis after which the traffic light turns off without interaction. |
| void setBlinkDelay(long millis)                   | Sets the delay when blinking yellow in millis    |
| void setCycleLength(long millis)                  | Sets the length of one whole cycle red-red/yellow-green-yellow-red in millis   |
| long getTimeout()                                 | Gets the time after which the light timeouts              |
| long getBlinkDelay()                              | Gets the blink delay              |
| long getCycleLength()                             | Gets the cycle length              |
| void setLEDs(bool green, bool yellow, bool red)   | Sets the LEDs when the corresponding value is true              |
| void setGreen(bool state)                         | Sets the green LED              |
| void setYellow(bool state)                        | Sets the yellow LED              |
| void setRed(bool state)                           | Sets the red LED              |
| bool getGreenState()                              | Gets the state of the green LED              |
| bool getYellowState()                             | Gets the state of the yellow LED              |
| bool getRedState()                                | Gets the state of the red LED              |
| bool getButtonState()                             | Gets the state of the button              |


