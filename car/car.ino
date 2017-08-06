#include <BMI160.h>
#include <CurieIMU.h>

#include <Servo.h>

int STBY = 6; //standby
int leftPin1=10;
int rightPin1=11;
int leftPin2=2;
int rightPin2=12;
int left1=0;
int right1=0;
int left2=0;
int right2=0;
int dutycycle=0;
//Motor A
int PWMA = 9; //Speed control 
int AIN1 = 7; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 3; //Speed control
int BIN1 = 4; //Direction
int BIN2 = 5; //Direction

void setup();
void loop();
void move(int motor, int speed, int direction);
void stop();
void setup(){
  pinMode(13,INPUT);
  Serial.begin(9600); // initialize Serial communication
  pinMode(leftPin1, INPUT);
  pinMode(rightPin1, INPUT);
  pinMode(leftPin2, INPUT);
  pinMode(rightPin2, INPUT);
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(13, INPUT); 
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 
  pinMode(A4, INPUT); 
  pinMode(A5, INPUT);   
}

void loop(){
  dutycycle=(32*digitalRead(A0)+16*digitalRead(A1)+8*digitalRead(A2)+4*digitalRead(A3)+2*digitalRead(A4)+digitalRead(A5))*4;
  Serial.println(dutycycle);
  left1 = digitalRead(leftPin1);
  right1 = digitalRead(rightPin1);
  left2 = digitalRead(leftPin2);
  right2 = digitalRead(rightPin2);
  if(left1==1){
    move(1, dutycycle, 1);
  }

  if(right1==1){
    move(2, dutycycle, 1);
  }
  
  if(left2==1){
    move(1, dutycycle,0);
  }
 
  if(right2==1){
    move(2, dutycycle, 0);
  }
  if(left1==0&&left2==0){
    move(1, 0, 1);
  }
  if(right1==0&&right2==0){
    move(2, 0, 1);
  }
 

}


void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}

