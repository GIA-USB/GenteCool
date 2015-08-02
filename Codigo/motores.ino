int motori=11; /*motor derecha hacia atras*/
int motord=5;/*motor izquierda hacia atras*/
int motoria=3;/*motor derecha hacia delante*/
int motorda=2;/*motor izquierda hacia delante*/
int eD=6; /* pin enable del puente H para el motor derecho*/
int eI=10; /* pin enable para el motor izquierdo */
/* el pin 7 del enable del izquierdo ahora esta en el 10 porque es PWM */
void setup()
{
  pinMode(motord,OUTPUT);
  pinMode(motorda,OUTPUT);
  pinMode(motori,OUTPUT);
  pinMode(motoria,OUTPUT);

  pinMode(eD,OUTPUT);
  pinMode(eI,OUTPUT);
  digitalWrite(eD,HIGH);
  digitalWrite(eI,HIGH);
}
void loop()
{

  delay(5);
  adelante();
  delay(2000);
  //atras();
  //delay(2000);
  //derecha();
  //delay(2000);
  //izquierda();
  //delay(2000);
  //parar();
  //delay(5000);
    
}
void adelante()
{
analogWrite(eD,25); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,250);
digitalWrite(motord,LOW);
digitalWrite(motori,LOW);
delay(5);
digitalWrite(motorda,HIGH);
digitalWrite(motoria,HIGH);

}
void atras()
{
digitalWrite(eD,LOW);
digitalWrite(eI,LOW);
delay(5);
analogWrite(eD,80); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,80);
digitalWrite(motorda,LOW);
digitalWrite(motoria,LOW);
delay(5);
digitalWrite(motord,HIGH);
digitalWrite(motori,HIGH);


}

void derecha()
{
digitalWrite(eD,LOW);
digitalWrite(eI,LOW);
delay(5);
analogWrite(eD,80); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,80);
digitalWrite(motorda,LOW);
digitalWrite(motori,LOW);
delay(5);
digitalWrite(motord,LOW);
digitalWrite(motoria,HIGH);
}

void izquierda()
{
digitalWrite(eD,LOW);
digitalWrite(eI,LOW);
delay(5);
analogWrite(eD,80); /* Menos de 20 no se mueve y suena raro */
analogWrite(eI,80);
digitalWrite(motord,LOW);
digitalWrite(motoria,LOW);
delay(5);
digitalWrite(motorda,HIGH);
digitalWrite(motori,LOW);
}

void parar()
{
analogWrite(eD,0);
analogWrite(eI,0);

}