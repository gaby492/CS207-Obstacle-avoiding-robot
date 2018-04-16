/* 
Obstacle Avoiding Robot
Gabriela Dominguez
Date: April 16, 2018

This code allows the Smart Robot Car V 3.0 by Elegoo to move forward, backward and stopping when the user enters the assigned chars
for those movements which are 'f', 's' and 'b'. Those chars can be received as input via Bluetooth using the application provided by 
ELEGOO or any other Bluetooth BLE terminal. Plus, the robot can detect obstacles at a distance of 25cm and avoid them by changing 
its path.

The original code was included in the Elegoo's CD Tutorial. Some modifications were applied to it.

www.elegoo.com
*/


#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo
char getstr;


//For sending and receiving data from the ultrasonic sensor
int Echo = A4;  
int Trig = A5; 

#define ENA 5  //Controls speed of left motor
#define ENB 6  //Controls speed of right motor

//For controlling the left motor
#define IN1 7
#define IN2 8

//For controlling the right motor
#define IN3 9
#define IN4 11

#define carSpeed 150
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

/*
The functions back, forward, right and left control the speed of the motors and indicate which motor should be "LOW" or "HIGH"
*/

void forward(){ 
  analogWrite(ENA, carSpeed); 
  analogWrite(ENB, carSpeed); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} 

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  

void setup() { 
  //Initializing all the pins and the serial communication
  
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
}

void loop() { 
    getstr = Serial.read();    //To read the chars from the Bluetooth terminal
    
    myservo.write(90);  //set servo position according to scaled value
    delay(500); 
    middleDistance = Distance_test();  // Before moving it needs to obtain the distance to the object in the front

    if(middleDistance <= 20) {    //If the distance between the robot and the object in the front is less or equals to 20cm...
      Serial.println("Obstacle");    
      stop();
      
      //Turns to the right and obtains the distance 
      delay(500);                         
      myservo.write(10);          
      delay(1000);      
      rightDistance = Distance_test();
      
      //Goes back to its original position
      delay(500);
      myservo.write(90); 
      
      //Turns to the left and obtains the distance 
      delay(1000);                                                  
      myservo.write(180);              
      delay(1000); 
      leftDistance = Distance_test();
      
      //Goes back to its original position
      delay(500);
      myservo.write(90);              
      delay(1000);
      
      //If the distance to the right is bigger than the distance to the left, the robot will turn to the right
      if(rightDistance > leftDistance) {
        right();
        delay(360);
      }
      //If the distance to the left is bigger than the distance to the right, the robot will turn to the left
      else if(rightDistance < leftDistance) {
        left();
        delay(360);
      }
      //If the distance between the robot and an object is less than 20 cm to the left or to the right the car will go back.
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        back();
        delay(180);
      }
      //In any other case, if the input was a 'f', the car will go forward
      else if(getstr=='f'){ 
          forward();
      }
    }  
    //If there is no obstacle in the front and any of these characters were received, the car will go forward, backward or it will just stop.
    else if(getstr=='f'){
          forward();
    }else if(getstr=='b'){
          back();
    }else if(getstr=='s'){
          stop();
    }    
}

