#include <ros.h>
#include <RC/pwmout.h>
#include <Servo.h>

ros::NodeHandle nh;
Servo servo;

//msg: [-1.0, 1.0]
void callback(const RC::pwmout& msg){
  servo.writeMicroseconds(percentToMicroSeconds(msg.steer));
}

//duty cycle [1000, 2000], 1500 = neutral
int percentToMicroSeconds(double percent){
  return percent*500+1500;
}

ros::Subscriber<RC::pwmout> sub("pwmout", &callback);

void setup() {  
  servo.attach(10);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(10);
}
