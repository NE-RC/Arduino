#include <ros.h>
#include <RC/pwmout.h>
#include <Servo.h>

ros::NodeHandle nh;
Servo servo;
Servo motor;

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

void setup() {
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(10);
  if (nh.connected()){
    if(!servo.attached()){servo.attach(10);}
    if(!motor.attached()){motor.attach(8);}
  }

}
