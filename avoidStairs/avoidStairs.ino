/* 
Obstacle Avoiding Robot. "Line tracking"
Gabriela Dominguez
Date: April 16, 2018
This code allows the Smart Robot Car V 3.0 by Elegoo to move forward, backward and stopping when the user enters the assigned chars
for those movements which are 'f', 's' and 'b'. Those chars can be received as input via Bluetooth using the application provided by 
ELEGOO or any other Bluetooth BLE terminal. Plus, the robot can detect black lines in the front of it by using its line tracker module.
The original code was included in the Elegoo's CD Tutorial. Some modifications were applied to it.
www.elegoo.com
*/


//Line Tracking IO define
#define LT_R !digitalRead(10)  
#define LT_M !digitalRead(4)   
#define LT_L !digitalRead(2)   

char getstr;

#define ENA 5  //Controls speed of left motor
#define ENB 6  //Controls speed of right motor

//For controlling the left motor
#define IN1 7
#define IN2 8

//For controlling the right motor
#define IN3 9
#define IN4 11

#define carSpeed 150

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
  Serial.println("go forward!");
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 

void setup(){
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
}


////cON UNO DE ELLOS   QUE DETECTE QUE HAY PELIGRO, VA RETROCEDER.
//eN EL PROGRAMA PRINCIPAL, CADA QUE AVANCE HACIA ENFRENTE, IZQUIERADA, O DERECHA, TIENE QUE VERIFICAR QUE TODAS LAS LUCES ESTEN apagadas. dE LO CONTRARIO, RETROCEDER

/*
The line tracker module has 3 channels, if any of them detect a black line, then the robot will go back. While there is a black line 
detected by the right channel, the robot is going to turn to the left. While there is a black line detected by the left channel, 
the robot is going to turn to the right. After that, is going to check the value of the char received via Bluetooth. If it is 'f', 
then the robot is going to go forward.
If there is no black line in the front is, the robot is going to move according to the values received via BLuetooth.

*/

void loop() {
  getstr = Serial.read();
  Serial.println(getstr);
  delay(100);
  
  Serial.println("Nuevo Loop");
  if(LT_M || LT_R || LT_L){
    Serial.print(!digitalRead(4));
    Serial.print(!digitalRead(10));
    Serial.print(!digitalRead(2));
    //forward();
    back();
    
    //Let's check which path should take next
    while(LT_R){left(); delay(360); };
    while(LT_L){right(); delay(360);}; 
    //left(); 
    if(getstr=='f')
      forward(); 
  }else if(getstr=='f'){
      forward(); 
      
  }else if(getstr=='b'){
      back(); 
  }
 
  
  if(getstr=='s'){stop();}
  Serial.println(" ");
  //delay(1000);
}





