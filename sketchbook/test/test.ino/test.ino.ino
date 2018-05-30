#include <Servo.h>
Servo servo;

//2000 = max, 1000 min, 1500 neutral

void setup() {

  // put your setup code here, to run once:
  servo.attach(10);
  /*
  servo.writeMicroseconds(2000);
  delay(100);
  servo.writeMicroseconds(1000);
  delay(100);
  servo.writeMicroseconds(1500);
  */
}

void loop() {
  servo.writeMicroseconds(1000);
}
