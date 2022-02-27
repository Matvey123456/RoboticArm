#include <MPU6050_tockn.h>
#include <Wire.h>
 
MPU6050 mpu6050(Wire);

String command;

int mA = 0;
int mB = 45;//45
int mC = 60;//60
int mD = 0;

int motordelay = 100;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);
}

void loop() {
  voice();
  choose_movement(command);
  control();
}

void voice(){
  command = "";
  while (Serial.available()) {
    char c = Serial.read();
    command = command + c;
  }
}

void choose_movement(String a){
  if(command != ""){
    if(a == "forward"){
      while(a != "stop"){
        forward();
        control();
        voice();  
      }  
    }
    if(a == "back"){
      while(a != "stop"){
        back();
        control();
        voice();  
      }
    }
    if(a == "left"){
      while(a != "stop"){
        left();
        control();
        voice(); 
      }
    }
    if(a == "right"){
      while(a != "stop"){
        right();
        control();
        voice();  
      }
    }
    if(a == "up"){
      while(a != "stop"){
        up();
        control();
        voice();  
      }
    }
    if(a == "down"){
      while(a != "stop"){
        down();
        control();
        voice();  
      }
    }
  }
}

void forward(){
  if(mB < 400 && mC > 60){
    mB += 1;
    mD -= 2;
    mC -= 1;
  }   
}

void back(){
  if(mB > 45 && mC < 440){
    mB -= 1;
    mD += 2;
    mC += 1;
  } 
}

void left(){
  mA -= 1;
}

void right(){
  mA += 1;
}

void up(){
  if(analogRead(A2) / (440 - analogRead(A3)) > 1.1){
    mB -= 1;
    mD -= 2;
    mC -= 2;  
  }
  if(analogRead(A2) / (440 - analogRead(A3)) < 1.1){
    mB += 1;
    mD -= 2;
    mC -= 2;  
  }
}

void down(){
  if(analogRead(A2) / (440 - analogRead(A3)) < 1.1){
    mB -= 1;
    mD += 2;  
    mC += 2;
  }
  if(analogRead(A2) / (440 - analogRead(A3)) > 1.1){
    mB += 1;
    mD += 2;
    mC += 1;  
  }  
}

void motorA(String a){
  if(a == "right"){
    digitalWrite(4,HIGH);
    digitalWrite(2,LOW);
    delay(motordelay);
  }
  if(a == "left"){
    digitalWrite(4,LOW);
    digitalWrite(2,HIGH);
    delay(motordelay);
  } 
  digitalWrite(4,LOW);
  digitalWrite(2,LOW);
}
void motorB(String a){
  if(a == "right"){
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
    delay(motordelay);
  }
  if(a == "left"){
    digitalWrite(8,LOW);
    digitalWrite(7,HIGH);
    delay(motordelay);
  } 
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  //Serial.println("test");
}
void motorC(String a){
  if(a == "left"){
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
    delay(motordelay);
  }
  if(a == "right"){
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
    delay(motordelay);
  } 
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  Serial.println("test");
}
void motorD(String a){
  if(a == "right"){
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    delay(motordelay);
  }
  if(a =="left"){
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    delay(motordelay);
  }
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
}
void control(){
  if(mpu6050.getAngleZ() < mA){
    while(mpu6050.getAngleZ() != mA){
      motorA("left"); 
      
    }
  }
  if(mpu6050.getAngleZ() > mA){
    while(mpu6050.getAngleZ() != mA){
      motorA("right");  
      
    }
  }
  if(analogRead(A2) < mB - 5){
    while(analogRead(A2) < mB - 5){
      motorB("left");  
    }
  }  
  if(analogRead(A2) > mB + 5){
    while(analogRead(A2) > mB + 5){
      motorB("right");  
    }
  }
  Serial.println("test");
  if(analogRead(A3) > mC + 5){
    while(analogRead(A3) > mC + 5){
      motorC("right");  
    }
  }
  if(analogRead(A3) < mC - 5){
    while(analogRead(A3) < mC - 5){
      motorC("left");  
    }
  }
  if(mpu6050.getGyroAngleX() < mD){
    while(mpu6050.getGyroAngleX() != mD){
      motorD("left"); 
    
    }
  }
  if(mpu6050.getGyroAngleX() > mD){
    while(mpu6050.getGyroAngleX() != mD){
      motorD("right"); 
    
    }
  }
}
