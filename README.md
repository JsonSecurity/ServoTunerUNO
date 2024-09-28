# ServoTunerUNO
This is a C++ (Arduino) script to calibrate servo motors by sending various parameters, for example the Minimum Pulse, and Maximum Pulse.

### Aplication (Flutter)
- Link: not yet available

### Reception format
The data is sent all in a row but only the char variable enters the function so it goes one by one as shown below.
```
z
:
...
:
z
```

### Data reception
Data is received one at a time, a “key” (z) is used to indicate the start and end of the command.
<br><br>
<img src="https://github.com/JsonSecurity/Images/blob/main/all/Servo%20Tuner%20Arduino.png" width="900" >

### Servo calibration
After parcear the information is sent to the function where the servo movement is performed.<br><br>
<img src="https://github.com/JsonSecurity/Images/blob/main/all/Servo%20Tuner%20Arduino%202.png" width="900" >
<br><br>
It is important to note that the servo number is also sent, so you must initialize more servos or use a motor controller module and just change the pin number.
