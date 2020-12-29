#include <ros.h>
#include <RC/pwmout.h>
#include <std_msgs/Float32.h>
#include <Servo.h>
#include <Encoder.h>

ros::NodeHandle nh;
std_msgs::Float32 encoderMessage;

Servo servo;
Servo motor;
Encoder enc(3,2);

unsigned long prevTime = 0;
unsigned long currTime;

long prevEncPos = -999;
long encPos = -999;

float ringBuffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float runningAvg = 0;
int ptr = 0;

//msg: [-1.0, 1.0]
void callback(const RC::pwmout& msg){
  servo.writeMicroseconds(percentToMicroSeconds(msg.steer));
  motor.writeMicroseconds(percentToMicroSeconds(msg.throttle));
}

//duty cycle [1000, 2000], 1500 = neutral
int percentToMicroSeconds(double percent){
  return percent*500+1500;
}

ros::Subscriber<RC::pwmout> sub("pwmout", &callback);
ros::Publisher pub("encoder", &encoderMessage);

void setup() {
  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(sub);
}

void loop() {
  encPos = enc.read();
  currTime = millis();

  if (prevTime != 0) {
    runningAvg -= ringBuffer[ptr] / 10.0;
    runningAvg += (encPos - prevEncPos) / ((currTime - prevTime) / 1000.0) / 10.0;
    ringBuffer[ptr] = (encPos - prevEncPos) / ((currTime - prevTime) / 1000.0);
    ptr += 1;
    ptr %= 10;

    encoderMessage.data = runningAvg;
    pub.publish(&encoderMessage);
  }
  prevTime = currTime;
  prevEncPos = encPos;
  
  if (nh.connected()){
    if(!servo.attached()){servo.attach(10);}
    if(!motor.attached()){motor.attach(8);}
  }
  
  nh.spinOnce();
  delay(10);
}
