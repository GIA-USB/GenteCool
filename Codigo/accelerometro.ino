#include <AcceleroMMA7361.h>
const int ok_led = 2;

AcceleroMMA7361 accelero;
int x, y ,z;

int pos = 0;
int dir = 1;

void print_accel()
{
    x = accelero.getXAccel();
    y = accelero.getYAccel();
    z = accelero.getZAccel();
    Serial.print("\nx: ");
    Serial.print(x);
    Serial.print(" \ty: ");
    Serial.print(y);
    Serial.print(" \tz: ");
    Serial.print(z);
    Serial.print("\tG*10^-2");
}

void setup() {
    Serial.begin(9600);
    Serial.println("Initiating...");
    // "OK" Led:
    pinMode(ok_led, OUTPUT);

    // sleepPin = 13, selfTestPin = 12, zeroGPin = 9, gSelectPin = 8
    // xPin = A2, yPin = A1, zPin = A0
    accelero.begin(13, 12, 9, 8, A2, A1, A0);
    accelero.calibrate();
  
    Serial.println("Initiated");
}

void loop()
{
    print_accel();
}



