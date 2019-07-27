#include <Encoder.h>

Encoder enc(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

long pos = -999;

void loop() {
  // put your main code here, to run repeatedly:
  pos = enc.read();
  Serial.println(pos);
}
