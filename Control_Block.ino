#include "DCMotor.h"
#define _DCMotorPWM_Phase 1
#include  <PS2X_lib_temi.h>

#include <Servo.h>

DCMotor Motor = DCMotor(_DCMotorPWM_Phase);
PS2X ps2x; // create PS2 Controller Class
byte  ps2x_vibrate = 0;

Servo myServo3;
Servo myServo11;
Servo myServo12;

// 描述該功能...
void tailControl() {
  if (ps2x.Button(PSB_CIRCLE) && ps2x.Button(PSB_SQUARE)) {
    myServo12.write(90);
  } else if (ps2x.Button(PSB_CIRCLE)) {
    myServo12.write(180);
  } else if (ps2x.Button(PSB_SQUARE)) {
    myServo12.write(0);
  } else {
    myServo12.write(90);
  }
}


// 描述該功能...
void headControl() {
  if (ps2x.Button(PSB_TRIANGLE)) {
    myServo3.write(140);
    if ((ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) && (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2))) {
      myServo11.write(90);
    } else if (ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) {
      myServo11.write(60);
    } else if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2)) {
      myServo11.write(120);
    } else {
      myServo11.write(90);
    }
  } else if (ps2x.Button(PSB_CROSS)) {
    myServo3.write(0);
    myServo11.write(90);
  } else {
    myServo3.write(80);
    if ((ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) && (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2))) {
      myServo11.write(90);
    } else if (ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) {
      myServo11.write(60);
    } else if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2)) {
      myServo11.write(120);
    } else {
      myServo11.write(90);
    }
  }
}


// 描述該功能...
void motorControl() {
  if (ps2x.Button(PSB_PAD_UP)) {
    if ((ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) && (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2))) {
    	Motor.Forward();
    } else if (ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) {
    	Motor.RightForward();
    } else if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2)) {
    	Motor.LeftForward();
    } else {
    	Motor.Forward();
    }
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
  	Motor.Left();
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
  	Motor.Right();
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    if ((ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) && (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2))) {
    	Motor.Reverse();
    } else if (ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2)) {
    	Motor.LeftReverse();
    } else if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2)) {
    	Motor.RightReverse();
    } else {
    	Motor.Reverse();
    }
  } else {
    	Motor.Stop( _DCMotorPWM_Phase );
  }
}



void setup() {
  //Setup Motor
  Motor.setMotorL(5, 6);
  Motor.setMotorR(10, 9);

  ps2x.config_gamepad(2, 19, 18, 13, 0, 0);  //Setup PS2 Remote controller

  myServo3.attach(3);
  myServo11.attach(11);
  myServo12.attach(12);

  myServo3.write(90);
  myServo11.write(90);
  myServo12.write(90);
  Motor.Stop( _DCMotorPWM_Phase );

}

void loop() {
  ps2x.read_gamepad(0, ps2x_vibrate);  //DualShock Controller
  headControl();
  motorControl();
  tailControl();
  delay(16);

}