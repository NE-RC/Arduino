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

long encPos = -999;

  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(sub);
}

void loop() {
  encPos = enc.read();
  encoderMessage.data = encPos;
  pub.publish(&encoderMessage);
  
  if (nh.connected()){
    if(!servo.attached()){servo.attach(10);}
    if(!motor.attached()){motor.attach(8);}
  }
  
  nh.spinOnce();
  delay(10);
}
