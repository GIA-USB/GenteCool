#include <AcceleroMMA7361.h>
#include <math.h>
const int ok_led = 2;

int motord=11; /*motor derecha hacia atras*/
int motori=5;/*motor izquierda hacia atras*/
int motorda=3;/*motor derecha hacia delante*/
int motoria=2;/*motor izquierda hacia delante*/

AcceleroMMA7361 accelero;
int x, y ,z;

int pos = 0;
int dir = 1;

double last_proportional;
double integral;

void adelante()
{
digitalWrite(motord,LOW);
digitalWrite(motori,LOW);
delay(5);
digitalWrite(motorda,HIGH);
digitalWrite(motoria,HIGH);

}
void atras()
{
analogWrite(motorda,0);
analogWrite(motoria,0);
delay(5);
analogWrite(motord,255);
analogWrite(motori,255); 

}

void derecha()
{
analogWrite(motori,255);
analogWrite(motorda,255);
delay(5);
analogWrite(motord,0);
analogWrite(motoria,0);

}

void izquierda()
{
analogWrite(motoria,255);
analogWrite(motord,255);
delay(5);
analogWrite(motori,0);
analogWrite(motorda,0);

}

void parar()
{
analogWrite(motoria,0);
analogWrite(motord,0);
analogWrite(motori,0);
analogWrite(motorda,0);

}

int offSet = 0;

int get_angulo()
{
//    x = accelero.getXAccel();
//    y = accelero.getYAccel();
//    z = accelero.getZAccel();
//    x = analogRead(A2);
//    y = analogRead(A1);
//    z = analogRead(A0);
//    x = (30 * (analogRead(A2) -75  -512)) / 128 * 5 / 4;
//    y = (30 * (analogRead(A1) -78  -512)) / 128 * 5 / 4;
//    z = (30 * (analogRead(A0) +126  -512)) / 128 * 5 / 4;
//    Serial.print("\nx: ");
 //   Serial.print(x);
   y = (accelero.getYRaw()-offSet) / 2 * 7;
    Serial.print(" \ny: ");
    Serial.print(y);
//    Serial.print(" \tz: ");
//    Serial.print(z);
//    Serial.print("\tG*10^-2");
    
//    double angulo = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
//    angulo = angulo / z;
//    angulo = 1 / cos(angulo);
    
//    Serial.print("\tangulo ");
//    Serial.print(angulo, 8);

    return y;
}

void setup() {
    pinMode(motord,OUTPUT);
    pinMode(motorda,OUTPUT);
    pinMode(motori,OUTPUT);
    pinMode(motoria,OUTPUT);

    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    
    Serial.begin(9600);
    Serial.println("Initiating...");
    // "OK" Led:
    pinMode(ok_led, OUTPUT);

    // sleepPin = 13, selfTestPin = 12, zeroGPin = 9, gSelectPin = 8
    // xPin = A2, yPin = A1, zPin = A0
    accelero.begin(13, 12, 9, 8, A2, A1, A0);
    accelero.calibrate();
    offSet = accelero.getYRaw();
    Serial.println("Initiated");
    

}

void loop()
{
 /*   int angulo = get_angulo();
    Serial.print("\tAngulo: ");
    Serial.println(angulo);

//    double proportional = angulo - 1.209;
    double proportional = angulo;
    
    double derivative = proportional - last_proportional;
    integral += proportional;
    
    last_proportional = proportional;
    
    double kp = 1; //1/10
    double ki = 0; //1/10000
    double kd = 1; //3/2
    double power_difference = proportional*kp + integral*ki + derivative*kd;
    
    if(power_difference>1){
       atras();
    }else{
        adelante();
    }
    
    Serial.println(power_difference);
*/
adelante();
}



