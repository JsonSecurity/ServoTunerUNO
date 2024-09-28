#include <Servo.h>
#include <SoftwareSerial.h>

//---------BT--------------
SoftwareSerial miBT(10, 11);

//--Variables-de-control--
char DATO = 0;
//--------Calibracion------
int indice = 0;
int contador = 0;
bool tuner = false;

String paramiter = "";

String array_comandos[25];
String array_paramiters[6];

//-------Servo---------
Servo servo_one;

void setup() {
  //-----------------------------bluetooth----------------------------
  miBT.begin(38400);
  //--------------------------MonitorSerial---------------------------
  Serial.begin(9600);

  // Pin servo 
  servo_one.attach(8, 450, 6750);
  delay(100);
}

void SetCalibrateServo(uint8_t n_servo, int pMin, int pMax, int angulo) {
  // n_servo para pin (8) se debe definir los otros pines o usar el modulo controlador de motores
  servo_one.attach(8, pMin, pMax);
  servo_one.write(angulo);
}

void CalibrarServoMotor() {
  // ternario para detectar el inicio y final 'z'

  /*if (DATO == 'z') {
    tuner = !tuner;
  }*/

  tuner = (DATO == 'z') ? !tuner : tuner;

  //Serial.println(String(tuner));
  
  // formating all variables
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
