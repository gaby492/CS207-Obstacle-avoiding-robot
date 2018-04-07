#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <Servo.h>          //Servo motor library. This is standard library
     
Servo servo_motor; //our servo name

//our L298N control pins
const int  ENA = 5;
const int ENB = 6;
const int LeftMotorForward = 8;
const int LeftMotorBackward = 7;
const int RightMotorForward = 11;
const int RightMotorBackward = 9;

//sensor pins
#define trig_pin A5 //analog input 1
#define echo_pin A4 //analog input 2
#define carSpeed 150

#define maximum_distance 400 ///200
boolean goesForward = false;
int distance = 100;
char getstr; //Defines a function that receives the Bluetooth character

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function



void setup(){
  Serial.begin(9600);
  
  pinMode(echo_pin, INPUT);    //
  pinMode(trig_pin, OUTPUT);  //
  pinMode(ENA, OUTPUT);   //
  pinMode(ENB, OUTPUT);   //
  
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(100);  //2000
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
  getstr = Serial.read();
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(5);

  Serial.println("a");
  ////Si recibe un "Forward"
  if(getstr == 'a'){
        
        if (distance <= 20){
          moveStop();
          delay(300);
          moveBackward();
          delay(400);
          moveStop();
          delay(300);
          distanceRight = lookRight();
          delay(300);
          distanceLeft = lookLeft();
          delay(300);
      
          if (distanceRight >= distanceLeft){  //if (distance >= distanceLeft){
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
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  Serial.println("Stop!");
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
    Serial.println("Forward");
  }
}

void moveBackward(){

  goesForward=false;
  
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  Serial.println("Back");
  
}

void turnRight(){

  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(500);
  
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  Serial.println("Right"); 
}

void turnLeft(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);

  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}


