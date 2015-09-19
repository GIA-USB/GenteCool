#include <AcceleroMMA7361.h>
#include <math.h>
const int ok_led = 2;
const float MATH_PI = 3.14159265359;

int motori=11; /*motor derecha hacia atras*/
int motord=5;/*motor izquierda hacia atras*/
int motoria=3;/*motor derecha hacia delante*/
int motorda=2;/*motor izquierda hacia delante*/
int eD=6; /* pin enable del puente H para el motor derecho*/
int eI=10; /* pin enable para el motor izquierdo */

AcceleroMMA7361 accelero;
int x, y ,z;
double pitch, roll;
int angulo;
int minVel = 30;

int pos = 0;
int dir = 1;

double last_proportionalX;
double integralX;
double derivativeX;
double proportionalX;
double last_proportionalY;
double integralY;
double derivativeY;
double proportionalY;

void adelante(int velI, int velD){

digitalWrite(eD,LOW);
digitalWrite(eI,LOW);
analogWrite(eD,velD); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,velI);
digitalWrite(motord,LOW);
digitalWrite(motori,LOW);
delay(5);
digitalWrite(motorda,HIGH);
digitalWrite(motoria,HIGH);

}
void atras(int velI, int velD){
  
digitalWrite(eD,LOW);
digitalWrite(eI,LOW);
delay(5);
analogWrite(eD,velD); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,velI);
digitalWrite(motorda,LOW);
digitalWrite(motoria,LOW);
delay(5);
digitalWrite(motord,HIGH);
digitalWrite(motori,HIGH);


}

void derecha(int velI, int velD){
  
digitalWrite(eD,LOW);
digitalWrite(eI,LOW);
delay(5);
analogWrite(eD,velD); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,velI);
digitalWrite(motorda,LOW);
digitalWrite(motori,LOW);
delay(5);
digitalWrite(motord,LOW);
digitalWrite(motoria,HIGH);
}

void izquierda(int velI, int velD){
  
digitalWrite(eD,LOW);
digitalWrite(eI,LOW);
delay(5);
analogWrite(eD,velD); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,velI);
digitalWrite(motord,LOW);
digitalWrite(motoria,LOW);
delay(5);
digitalWrite(motorda,HIGH);
digitalWrite(motori,LOW);
}

void parar(){
  
analogWrite(eD,0);
analogWrite(eI,0);

}

int offSet = 0;

int get_angulo()
{
    x = accelero.getXAccel();
    y = accelero.getYAccel();
    z = accelero.getZAccel();
    x = analogRead(A2);
    y = analogRead(A1);
    z = analogRead(A0);
    x = (30 * (analogRead(A2) -75  -512)) / 128 * 5 / 4;
    y = (30 * (analogRead(A1) -78  -512)) / 128 * 5 / 4;
    z = (30 * (analogRead(A0) +126  -512)) / 128 * 5 / 4;
    //Serial.print("\nx: ");
    //Serial.print(x);
    y = (accelero.getYRaw()-offSet) / 2 * 7;
    //Serial.print(" \ny: ");
    //Serial.print(y);
    //Serial.print(" \tz: ");
    //Serial.print(z);
    //Serial.print("\tG*10^-2");
    
    double angulo = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    angulo = angulo / z;
    angulo = 1 / cos(angulo);
    
    //Serial.print("\tangulo ");
    //Serial.print(angulo, 8);

    return y;
}

void getAngulo2(){
    x = accelero.getXAccel();
    y = accelero.getYAccel();
    z = accelero.getZAccel();

    pitch = atan2(x,sqrt(pow(y,2))+pow(z,2));
    roll = atan2(y,sqrt(pow(x,2))+pow(z,2));

    pitch = pitch*180.0/PI;
    roll = roll*180.0/PI;
    /*Serial.println("Pitch");
    Serial.println(pitch);
    Serial.println("Roll");
    Serial.println(roll);*/
}

void setup() {
    pinMode(motord,OUTPUT);
    pinMode(motorda,OUTPUT);
    pinMode(motori,OUTPUT);
    pinMode(motoria,OUTPUT);

    pinMode(eI,OUTPUT);
    pinMode(eD,OUTPUT);
    
    Serial.begin(9600);
    Serial.println("Initiating...");
    // "OK" Led:
    pinMode(ok_led, OUTPUT);

    //sleepPin = 13, selfTestPin = 12, zeroGPin = 9, gSelectPin = 8
    //xPin = A2, yPin = A1, zPin = A0
    accelero.begin(13, 12, 9, 8, A2, A1, A0);
    accelero.calibrate();
    offSet = accelero.getYRaw();
    Serial.println("Initiated");
    

}

void loop()
{
    getAngulo2();
   
    proportionalY = roll; 
    derivativeY = proportionalY - last_proportionalY;
    integralY += proportionalY;
    last_proportionalY = proportionalY;
    
    double kp = 1; //1/10
    double ki = 0; //1/10000
    double kd = 0; //3/2
    double power_difference = proportionalY*kp + integralY*ki + derivativeY*kd;
    //double power_difference = proportional*kp + derivative*kd;
    int nuevaVel;
    if (power_difference >  255){
      nuevaVel = 255;
    } else if (power_difference < 0){
      nuevaVel = minVel;
    else {  
      nuevaVel = abs(int(power_difference)+minVel));
    }

    if(roll>-0.1){
       atras(nuevaVel,nuevaVel);
      //Serial.println("Atras");
    }else if (roll < -0.7){
      adelante(nuevaVel,nuevaVel);
      //Serial.println("Adelante");  
    } else{
      parar();  
      //Serial.println("Detenido");
    }
    Serial.println("Power difference");
    Serial.println(nuevaVel);
    //delay(1000);
    
}
