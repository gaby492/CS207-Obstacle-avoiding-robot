//www.elegoo.com

//Line Tracking IO define
#define LT_R !digitalRead(10)  
#define LT_M !digitalRead(4)   
#define LT_L !digitalRead(2)   

char getstr;

#define ENA 5 
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define carSpeed 150

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
  //else{stop();}
  
  if(getstr=='s'){stop();}
  Serial.println(" ");
  //delay(1000);
}





