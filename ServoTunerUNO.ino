#include <Servo.h>
#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>

//---------BT--------------
SoftwareSerial miBT(10, 11);

// Adafruit_PWMServoDriver
Adafruit_PWMServoDriver servo_placa = Adafruit_PWMServoDriver(0x40);

char DATO = 0;

int indice = 0;
int duty1;
int contador = 0;
bool tuner = false;

String paramiter = "";

String array_paramiters[6];

Servo servo_one;
Servo servo_two;

void setup() {
  miBT.begin(38400);
  Serial.begin(9600);

  // PWMServoDriver
  servo_placa.begin();
  servo_placa.setPWMFreq(60);  // Frecuencia PWM de 60Hz o T=16,66ms
}

void SetCalibrateServo(uint8_t n_servo1, int angulo1, int pMin, int pMax) {
  //duty1 = map(angulo1, 0, 180, 140, 620);

  // Servo 17 y 18 no se incluye en modulo PWM servo driver
  if (n_servo1 == 17) {
    servo_one.attach(8, pMin, pMax);
    servo_one.write(angulo1);
  } else if (n_servo1 == 18) {  //590 6650
    servo_two.attach(9, pMin, pMax);
    servo_two.write(angulo1);
  // Servos que si cuentan con PWM servo driver
  } else {
    duty1 = map(angulo1, 0, 180, pMin, pMax);
    servo_placa.setPWM(n_servo1, 0, duty1);
  }
}

void CalibrarServoMotor() {
  tuner = (DATO == 'z') ? !tuner : tuner;
  //Serial.println(String(tuner));

  if (tuner) {      
      if (DATO != ':') {
        paramiter += String(DATO);
      }else {
        array_paramiters[indice] = paramiter;
        //Serial.println(paramiter);
        paramiter = "";
        indice++;
      }
  }

  delay(10);

  if (!tuner && indice > 0) {
    Serial.println("");
    Serial.println("[+] SERVO: " + String(array_paramiters[1]));
    Serial.println("[+] PMIN: " + String(array_paramiters[2]));
    Serial.println("[+] PMAX: " + String(array_paramiters[3]));
    Serial.println("[+] ANGULO: " + String(array_paramiters[4]));
  
    SetCalibrateServo(array_paramiters[1].toInt(), array_paramiters[2].toInt(), array_paramiters[3].toInt(), array_paramiters[4].toInt());
    delay(100);

    indice = 0;
  }
}

void loop() {
  if (miBT.available()) {
    DATO = miBT.read();

    //Serial.print(String(DATO));
    CalibrarServoMotor();
  }

  delay(30);
}
