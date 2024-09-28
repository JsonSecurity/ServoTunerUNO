# ServoTunerUNO
This is a C++ (Arduino) script to calibrate servo motors by sending various parameters, for example the Minimum Pulse, and Maximum Pulse.

### Aplication (Flutter)
- Link: not yet available

### Data reception
Data is received one at a time, a “key” (z) is used to indicate the start and end of the command.
<br>
<img src="https://github.com/JsonSecurity/Images/blob/main/all/Servo%20Tuner%20Arduino.png" width="700" >

### Servo calibration
Luego de parcear la informacion se envia a la funcion donde se realiza el movimiento de servo.
<br><br>
<img src="https://github.com/JsonSecurity/Images/blob/main/all/Servo%20Tuner%20Arduino.png" width="700" >
<br><br>
Es importante tener en cuenta que tambien se envia el numero de servo, asi que se debe inicializar mas servos o usar un modulo controlador de motores y solo cambiar el numero de pin.
