#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//our L298N control pins
const int enablePinA = 5;
const int LeftMotorForward = 10;
const int LeftMotorBackward = 11;
const int RightMotorForward = 9;
const int RightMotorBackward = 8;
const int enablePinB = 6;

//sensor pins
#define trig_pin A5 //analog input 5
#define echo_pin A4 //analog input 4

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){
  
  pinMode(enablePinA, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(enablePinB, OUTPUT);
  
  servo_motor.attach(3); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int speed = 150;     //varying the motor by this value(0-255)

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 40){
    moveStop();
    delay(100);
    moveBackward();
    delay(200);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(400);
    distanceLeft = lookLeft();
    delay(400);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
      
    }
    else{
      turnLeft();
      moveStop();
      
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){
  int speed = 150;

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    
    analogWrite(enablePinA, speed);
    analogWrite(enablePinB, speed); 
  }
}

void moveBackward(){
  int speed = 180;

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  analogWrite(enablePinA, speed);
  analogWrite(enablePinB, speed);
  
}

void turnRight(){
  int speed = 150;

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  delay(5);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  analogWrite(enablePinA, speed);
  analogWrite(enablePinB, speed);
  
  delay(250);  //By varying this delay value rotate the robot
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  delay(5);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  analogWrite(enablePinA, speed);
  analogWrite(enablePinB, speed);
 
  
  
}

void turnLeft(){
  int speed = 150;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  delay(5);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  analogWrite(enablePinA, speed);
  analogWrite(enablePinB, speed);

  delay(250);   //By varying this delay value rotate the robot
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  delay(5);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  analogWrite(enablePinA, speed);
  analogWrite(enablePinB, speed);
}
