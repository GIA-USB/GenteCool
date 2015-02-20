int motord=11; /*motor derecha hacia atras*/
int motori=5;/*motor izquierda hacia atras*/
int motorda=3;/*motor derecha hacia delante*/
int motoria=2;/*motor izquierda hacia delante*/
void setup()
{
  pinMode(motord,OUTPUT);
  pinMode(motorda,OUTPUT);
  pinMode(motori,OUTPUT);
  pinMode(motoria,OUTPUT);

  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  
}
void loop()
{

  delay(5);
  adelante();
  delay(10);
    
}
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
